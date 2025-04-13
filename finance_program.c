#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_DESPESAS 100
#define MAX_CATEGORIAS 10
#define MAX_METAS 10

enum DespesaType
{
    FIXA,
    VARIAVEL
};

struct Despesa
{
    char titulo[100];
    float valor;
    enum DespesaType tipo;
    int categoria_idx;
};

struct Categoria
{
    char titulo[100];
};

struct Meta
{
    char titulo[100];
    float valor;
    float valor_investido; // Novo campo para rastrear o valor investido
};

void exibir_banner()
{
    printf("\n\n██████╗ ██████╗ ██╗███╗   ███╗███████╗██████╗ ██╗      █████╗ ███╗   ██╗\n");
    printf("██╔══██╗██╔══██╗██║████╗ ████║██╔════╝██╔══██╗██║     ██╔══██╗████╗  ██║\n");
    printf("██████╔╝██████╔╝██║██╔████╔██║█████╗  ██████╔╝██║     ███████║██╔██╗ ██║\n");
    printf("██╔═══╝ ██╔══██╗██║██║╚██╔╝██║██╔══╝  ██╔═══╝ ██║     ██╔══██║██║╚██╗██║\n");
    printf("██║     ██║  ██║██║██║ ╚═╝ ██║███████╗██║     ███████╗██║  ██║██║ ╚████║\n");
    printf("╚═╝     ╚═╝  ╚═╝╚═╝╚═╝     ╚═╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝\n\n");
}

void limpar_tela()
{
    system("cls || clear");
}

void configurar_renda(float *renda)
{
    printf("\nDigite sua renda mensal: R$ ");
    scanf("%f", renda);
    limpar_tela();
}

void registrar_despesa(
    struct Despesa *despesas, int *contador_despesas,
    struct Categoria *categorias, int *categorias_counter)
{
    if (*contador_despesas >= MAX_DESPESAS)
    {
        printf("Limite de despesas atingido!\n");
        return;
    }
    if (*categorias_counter == 0)
    {
        printf("Você não tem categorias cadastradas!");
        return;
    }

    limpar_tela();

    printf("Título da Despesa: ");
    scanf(" %[^\n]", despesas[*contador_despesas].titulo);

    printf("Valor: R$ ");
    scanf("%f", &despesas[*contador_despesas].valor);

    int choice;

    do
    {
        printf("Tipo da despesa:\n\n1 - Fixa\n2 - Variável\n\nDigite sua opção: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            despesas[*contador_despesas].tipo = FIXA;
            break;
        }
        else if (choice == 2)
        {
            despesas[*contador_despesas].tipo = VARIAVEL;
            break;
        }
        else
        {
            printf("Opção inválida! Escolha 1 para Fixa ou 2 para Variável.\n");
        }
    } while (choice != 1 && choice != 2);

    printf("Selecione uma das categorias abaixo:\n\n");
    for (int i = 0; i < *categorias_counter; i++)
    {
        printf("%d - %s\n", i + 1, categorias[i].titulo);
    }
    printf("\n");

    while (1)
    {
        printf("> ");
        scanf("%d", &choice);
        if (choice - 1 > *categorias_counter || choice < 1)
        {
            printf("Opção inválida!\n");
        }
        else
        {
            despesas[*contador_despesas].categoria_idx = choice - 1;
            break;
        }
    }

    (*contador_despesas)++;
    printf("Despesa registrada com sucesso!\n");
}

void registrar_categoria(struct Categoria *categorias, int *categorias_counter)
{
    if (*categorias_counter >= MAX_CATEGORIAS)
    {
        printf("Limite de categorias atingido!");
        return;
    }
    limpar_tela();

    printf("Título da Categoria: ");
    scanf(" %[^\n]", categorias[*categorias_counter].titulo);
    (*categorias_counter)++;
    printf("Categoria '%s' adicionada com sucesso!", categorias[*categorias_counter - 1].titulo);
}

void registrar_meta(struct Meta *metas, int *metas_counter)
{
    if (*metas_counter >= MAX_METAS)
    {
        printf("Limite de metas atingido!\n");
        return;
    }

    limpar_tela();

    printf("Título da Meta: ");
    scanf(" %[^\n]", metas[*metas_counter].titulo);

    printf("Valor da Meta: R$ ");
    scanf("%f", &metas[*metas_counter].valor);

    metas[*metas_counter].valor_investido = 0; // Inicializa o valor investido como 0

    (*metas_counter)++;
    printf("Meta '%s' adicionada com sucesso!\n", metas[*metas_counter - 1].titulo);
}

void adicionar_investimento_meta(struct Meta *metas, int metas_counter, float renda)
{
    if (metas_counter == 0)
    {
        printf("Nenhuma meta cadastrada!\n");
        return;
    }

    if (renda <= 0)
    {
        printf("Erro: Renda inválida! Configure sua renda antes de adicionar investimentos.\n");
        return;
    }

    limpar_tela();
    printf("Selecione uma meta para adicionar investimento:\n\n");
    for (int i = 0; i < metas_counter; i++)
    {
        printf("%d - %s (Valor: R$%.2f, Investido: R$%.2f)\n", i + 1, metas[i].titulo, metas[i].valor, metas[i].valor_investido);
    }
    printf("\n");

    int escolha;
    printf("> ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > metas_counter)
    {
        printf("Opção inválida!\n");
        return;
    }

    float valor;
    while (1)
    {
        printf("Digite o valor a ser investido na meta '%s': R$ ", metas[escolha - 1].titulo);
        scanf("%f", &valor);

        if (valor < 0)
        {
            printf("O valor deve ser maior que zero! Tente novamente.\n");
        }
        else if (valor > renda) 
        {
            printf("O valor investido não pode ser maior que a sua renda (R$ %.2f)!.\n", valor, renda);
        }
        else
        {
            break;
        }
    }

    metas[escolha - 1].valor_investido += valor;
    printf("Investimento de R$%.2f adicionado à meta '%s' com sucesso!\n", valor, metas[escolha - 1].titulo);
}

void mostrar_resumo(
    struct Meta *metas, int metas_counter,
    float renda, struct Despesa *despesas, int despesas_counter,
    struct Categoria *categorias, int categorias_counter)
{
    limpar_tela();
    float total_gastos = 0;
    float gastos_por_categoria[MAX_CATEGORIAS] = {0};

    printf("\n=== RESUMO FINANCEIRO ===\n");
    printf("Renda Mensal: R$%.2f\n\n", renda);

    // Calcula o total de gastos e os gastos por categoria
    for (int i = 0; i < despesas_counter; i++)
    {
        total_gastos += despesas[i].valor;
        gastos_por_categoria[despesas[i].categoria_idx] += despesas[i].valor;
    }

    // Exibe as despesas por categoria
    printf("=== DESPESAS POR CATEGORIA ===\n");
    printf("|     CATEGORIA     |   VALOR   |   %%   |\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < categorias_counter; i++)
    {
        float percentual = (total_gastos > 0) ? (gastos_por_categoria[i] / renda) * 100 : 0;
        printf("| %-18s | R$ %-7.2f | %-5.1f %% |\n", categorias[i].titulo, gastos_por_categoria[i], percentual);
    }

    // Exibe as metas e o progresso
    printf("\n\n=== METAS ===\n");
    printf("|     META     |   VALOR   | INVESTIDO |\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < metas_counter; i++)
    {
        total_gastos += metas[i].valor_investido;
        printf("| %-12s | R$ %-7.2f | R$ %-7.2f |\n",
               metas[i].titulo, metas[i].valor, metas[i].valor_investido);
    }
    printf("-----------------------------------------------------\n");

    // Exibe o total de gastos e o saldo disponível
    printf("\nTotal de Gastos: R$ %.2f\n", total_gastos);
    printf("Saldo Disponível: R$ %.2f\n", renda - total_gastos);

    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
    limpar_tela();
}

void definir_meta(float *meta)
{
    limpar_tela();
    printf("\nDigite o valor da meta: R$ ");
    scanf("%f", meta);
}

void exibir_ajuda()
{
    limpar_tela();
    printf("=== AJUDA ===\n\n");
    printf("Este programa ajuda você a gerenciar suas finanças pessoais.\n");
    printf("Abaixo está uma explicação de cada opção do menu:\n\n");

    printf("1 - Configurar Renda:\n");
    printf("    Permite que você insira sua renda mensal para calcular o saldo disponível.\n\n");

    printf("2 - Adicionar Despesa:\n");
    printf("    Registre uma nova despesa, informando o título, valor, tipo (Fixa ou Variável) e a categoria.\n");
    printf("    Certifique-se de cadastrar categorias antes de adicionar despesas.\n\n");

    printf("3 - Adicionar Categoria:\n");
    printf("    Adicione categorias para organizar suas despesas, como 'Alimentação', 'Lazer', etc.\n\n");

    printf("4 - Adicionar Meta:\n");
    printf("    Defina uma meta financeira, como economizar para uma viagem ou comprar algo específico.\n\n");

    printf("5 - Adicionar Investimento em Meta:\n");
    printf("    Permite adicionar um valor investido em uma meta específica.\n\n");

    printf("6 - Ver Resumo do Mês:\n");
    printf("    Exibe um resumo financeiro com o total de gastos, saldo disponível e proporção de gastos por categoria com base na sua renda.\n");
    printf("    Também mostra o progresso em relação às metas definidas.\n\n");

    printf("7 - Ajuda:\n");
    printf("    Exibe esta tela de ajuda com explicações sobre o funcionamento do programa.\n\n");

    printf("8 - Sair:\n");
    printf("    Encerra o programa.\n\n");

    printf("Pressione ENTER para voltar ao menu principal...");
    getchar();
    getchar();
    limpar_tela();
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    float renda = 0;
    int despesas_counter = 0, categorias_counter = 0, metas_counter = 0;

    struct Despesa despesas[MAX_DESPESAS];
    struct Categoria categorias[MAX_CATEGORIAS];
    struct Meta metas[MAX_METAS];

    int opcao;

    limpar_tela();

    while (1)
    {
        exibir_banner();
        printf("\n1 - Configurar Renda\n");
        printf("2 - Adicionar Despesa\n");
        printf("3 - Adicionar Categoria\n");
        printf("4 - Adicionar Meta\n");
        printf("5 - Adicionar Investimento em Meta\n");
        printf("6 - Ver Resumo do Mês\n");
        printf("7 - Ajuda\n");
        printf("8 - Sair\n");

        printf("\n> ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            configurar_renda(&renda);
            break;
        case 2:
            registrar_despesa(despesas, &despesas_counter, categorias, &categorias_counter);
            break;
        case 3:
            registrar_categoria(categorias, &categorias_counter);
            break;
        case 4:
            registrar_meta(metas, &metas_counter);
            break;
        case 5:
            adicionar_investimento_meta(metas, metas_counter, renda);
            break;
        case 6:
            mostrar_resumo(metas, metas_counter, renda, despesas, despesas_counter, categorias, categorias_counter);
            break;
        case 7:
            exibir_ajuda();
            break;
        case 8:
            return 0;
        default:
            printf("Opção inválida!\n");
        }
    }
}
