#include <stdio.h>
#include <string.h>


#define MAX 100


struct Despesa {
    char nome[50];
    float valor;
    char tipo[20];
    char categoria[30];
};


float renda = 0;
float meta = 0;
struct Despesa despesas[MAX];
int total_despesas = 0;


void limpar_tela() {
    system("cls || clear");
}


void configurar_renda() {
    printf("\nDigite sua renda mensal: R$ ");
    scanf("%f", &renda);
}


void registrar_despesa() {
    if(total_despesas >= MAX) {
        printf("Limite de despesas atingido!\n");
        return;
    }
    
    printf("\nNome da despesa: ");
    scanf(" %[^\n]", despesas[total_despesas].nome);
    
    printf("Valor: R$ ");
    scanf("%f", &despesas[total_despesas].valor);
    
    printf("Tipo (Fixa/Variavel): ");
    scanf(" %[^\n]", despesas[total_despesas].tipo);
    
    printf("Categoria: ");
    scanf(" %[^\n]", despesas[total_despesas].categoria);
    
    total_despesas++;
    printf("Despesa registrada com sucesso!\n");
}


void mostrar_resumo() {
    limpar_tela();
    float total_gastos = 0;
    
    printf("\n=== RESUMO FINANCEIRO ===\n");
    printf("Renda Mensal: R$%.2f\n", renda);
    printf("Meta: R$%.2f\n\n", meta);
    
    printf("=== DESPESAS ===\n");
    for(int i = 0; i < total_despesas; i++) {
        printf("%s: R$%.2f (%s) [%s]\n", 
               despesas[i].nome, 
               despesas[i].valor,
               despesas[i].tipo,
               despesas[i].categoria
            );
        total_gastos += despesas[i].valor;
    }
    
    printf("\nTotal Gastos: R$%.2f\n", total_gastos);
    printf("Saldo Disponivel: R$%.2f\n", renda - total_gastos);
    
    if(meta > 0) {
        float falta = meta - (renda - total_gastos);
        if(falta <= 0) {
            printf("\nParabens! Voce alcancou sua meta!\n");
        } else {
            printf("\nFaltam R$%.2f para alcancar sua meta\n", falta);
        }
    }
    
    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

void definir_meta() {
    printf("\nDigite o valor da meta: R$ ");
    scanf("%f", &meta);
}


int main() {
    int opcao;
    
    while(1) {
        limpar_tela();
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Configurar renda\n");
        printf("2 - Registrar despesa\n");
        printf("3 - Ver resumo\n");
        printf("4 - Definir meta\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: configurar_renda(); break;
            case 2: registrar_despesa(); break;
            case 3: mostrar_resumo(); break;
            case 4: definir_meta(); break;
            case 5: return 0;
            default: printf("Opcao invalida!\n");
        }
    }
}