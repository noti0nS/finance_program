#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_DESPESAS 100
#define MAX_CATEGORIAS 10

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

void mostrar_resumo(float meta, float renda, int contador_despesas, struct Despesa *despesas)
{
    /*

    Ao meu ver o resumo está incompleto.
    Além do Total Gasto e Saldo Disponível, também tem que ser exibido uma tabela mostrando a proporção do quanto o usuário está gastando com cada categoria.

    EX:

    Renda Mensal: R$ 150
    Categorias: Lazer e Despesas da Casa
    Meta Cadastrada: Comprar Carro

    Essas foram as suas despesas do mês até o momento:

    |     CATEGORIA     |   VALOR   |   %   |
    |       Lazer           R$ 30      20
    |  Despesas da Casa     R$ 120     80

    Com base nos gastos registrados, segue abaixo o quanto você conseguirá investir em suas metas esse mês:

    |     META     | VALOR |
    | Comprar Carro   R$ 0

    */

    limpar_tela();
    float total_gastos = 0;

    printf("\n=== RESUMO FINANCEIRO ===\n");
    printf("Renda Mensal: R$%.2f\n", renda);
    printf("Meta: R$%.2f\n\n", meta);

    printf("=== DESPESAS ===\n");
    // for (int i = 0; i < contador_despesas; i++)
    // {
    //     printf("%s: R$%.2f (%s) [%s]\n",
    //            despesas[i].titulo,
    //            despesas[i].valor,
    //            despesas[i].tipo == FIXA ? "Fixa" : "Variável",
    //            despesas[i].categoria);
    //     total_gastos += despesas[i].valor;
    // }

    printf("\nTotal de Gastos: R$%.2f\n", total_gastos);
    printf("Saldo Disponível: R$%.2f\n", renda - total_gastos);

    if (meta > 0)
    {
        float falta = meta - (renda - total_gastos);
        if (falta <= 0)
        {
            printf("\nParabéns! Você alcançou sua meta!\n");
        }
        else
        {
            printf("\nFaltam R$%.2f para alcançar sua meta\n", falta);
        }
    }

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
    // TODO: Implementar função que explica o funcionamento do menu.
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    float renda = 0, meta = 0;
    int despesas_counter, categorias_counter = 0;

    struct Despesa despesas[MAX_DESPESAS];
    struct Categoria categorias[MAX_CATEGORIAS];

    int opcao;

    limpar_tela();

    while (1)
    {
        exibir_banner();
        printf("\n1 - Configurar Renda\n");
        printf("2 - Adicionar Despesa\n");
        printf("3 - Adicionar Categoria\n");
        printf("4 - Adicionar Meta\n");
        printf("5 - Ver Resumo do Mês\n");
        printf("6 - Ajuda\n");
        printf("7 - Sair\n");
        
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
            definir_meta(&meta);
            break;
        case 5:
            mostrar_resumo(meta, renda, despesas_counter, despesas);
            break;
        case 6:
            exibir_ajuda();
            break;
        case 7:
            return 0;
        default:
            printf("Opção inválida!\n");
        }
    }
}
