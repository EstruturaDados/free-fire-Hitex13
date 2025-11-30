#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Struct Item – representa um item na mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função: inserirItem
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️  Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Adicionar Item ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", mochila[*total].nome);

    printf("Tipo (arma, munição, cura...): ");
    scanf(" %[^\n]", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("✔️ Item adicionado com sucesso!\n");
}

// Função: listarItens
void listarItens(Item mochila[], int total) {
    printf("\n===== Itens na Mochila =====\n");

    if (total == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função: buscarItem – BUSCA SEQUENCIAL
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    int encontrado = 0;  // flag

    printf("\n🔍 Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n📌 Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ O item \"%s\" não foi encontrado na mochila.\n", nomeBusca);
    }
}

// Função: removerItem
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n⚠️  Mochila vazia! Nada para remover.\n");
        return;
    }

    char nome[30];
    int encontrado = 0;

    printf("\n🗑️ Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;

            // Desloca os itens
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;
            printf("✔️ Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado, nada foi removido.\n");
    }
}

// MAIN – Menu e fluxo principal
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=========== Menu da Mochila ==========\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;

            case 2:
                removerItem(mochila, &total);
                break;

            case 3:
                listarItens(mochila, total);
                break;

            case 4:
                buscarItem(mochila, total);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);
    // Finaliza o programa
    //gosto dos emojis eles sao um style a mais no progama esse foi mas de boa aquela de war quase me mata minha cabeça doi ainda 

    return 0;
}
