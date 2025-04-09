#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_DESPESAS 100

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
    char categoria[30];
};

void exibir_banner()
{
    printf("██████╗ ██████╗ ██╗███╗   ███╗███████╗██████╗ ██╗      █████╗ ███╗   ██╗\n");
    printf("██╔══██╗██╔══██╗██║████╗ ████║██╔════╝██╔══██╗██║     ██╔══██╗████╗  ██║\n");
    printf("██████╔╝██████╔╝██║██╔████╔██║█████╗  ██████╔╝██║     ███████║██╔██╗ ██║\n");
    printf("██╔═══╝ ██╔══██╗██║██║╚██╔╝██║██╔══╝  ██╔═══╝ ██║     ██╔══██║██║╚██╗██║\n");
    printf("██║     ██║  ██║██║██║ ╚═╝ ██║███████╗██║     ███████╗██║  ██║██║ ╚████║\n");
    printf("╚═╝     ╚═╝  ╚═╝╚═╝╚═╝     ╚═╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝\n");
}

void limpar_tela()
{
    system("cls || clear");
}

void configurar_renda(float *renda)
{
    printf("\nDigite sua renda mensal: R$ ");
    scanf("%f", renda);
}

void registrar_despesa(struct Despesa *despesas, int* contador_despesas)
{
    if (*contador_despesas >= MAX_DESPESAS)
    {
        printf("Limite de despesas atingido!\n");
        return;
    }

    printf("Título: ");
    scanf(" %[^\n]", despesas[*contador_despesas].titulo);

    printf("Valor: R$ ");
    scanf("%f", &despesas[*contador_despesas].valor);

    int tipo_opcao;

    while (1)
    {
        printf("Tipo da despesa:\n\n1 - Fixa\n2 - Variável\n\nDigite sua opção: ");
        scanf("%d", &tipo_opcao);
        if (tipo_opcao == 1)
        {
            despesas[*contador_despesas].tipo = FIXA;
            break;
        }
        else if (tipo_opcao == 2)
        {
            despesas[*contador_despesas].tipo = VARIAVEL;
            break;
        }
        else
        {
            printf("Opção inválida! Escolha 1 para Fixa ou 2 para Variável.\n");
        }
    }

    printf("Categoria: ");
    scanf(" %[^\n]", despesas[*contador_despesas].categoria);

    (*contador_despesas)++;
    printf("Despesa registrada com sucesso!\n");
}

void mostrar_resumo(float meta, float renda, int contador_despesas, struct Despesa* despesas)
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
    for (int i = 0; i < contador_despesas; i++)
    {
        printf("%s: R$%.2f (%s) [%s]\n",
               despesas[i].titulo,
               despesas[i].valor,
               despesas[i].tipo == FIXA ? "Fixa" : "Variável",
               despesas[i].categoria);
        total_gastos += despesas[i].valor;
    }

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
}

void definir_meta(float *meta)
{
    printf("\nDigite o valor da meta: R$ ");
    scanf("%f", meta);
}

void exibir_ajuda() {
    // TODO: Implementar função que explica o funcionamento do menu.
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    float renda = 0;
    float meta = 0;
    int despesas_counter = 0;
    struct Despesa despesas[MAX_DESPESAS];

    int opcao;

    while (1)
    {
        limpar_tela();

        exibir_banner();
        printf("\n1 - Configurar renda\n");
        printf("2 - Registrar despesa\n");
        printf("3 - Ver resumo\n");
        printf("4 - Definir meta\n");
        printf("5 - Ajuda\n");
        printf("6 - Sair\n");
        printf("\n> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            configurar_renda(&renda);
            break;
        case 2:
            registrar_despesa(despesas, &despesas_counter);
            break;
        case 3:
            mostrar_resumo(meta, renda, despesas_counter, despesas);
            break;
        case 4:
            definir_meta(&meta);
            break;
        case 5:
            exibir_ajuda();
            break;
        case 6:
            return 0;
        default:
            printf("Opção inválida!\n");
        }
    }
}
