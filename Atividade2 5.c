#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

//  STRUCT ITEM
//  Representa um objeto dentro da mochila do jogador
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

//  Função: inserirItem
//  Objetivo: cadastrar um item no inventário
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Cadastro de Item ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*total].nome);

    printf("Tipo (arma, munição, cura, etc): ");
    scanf(" %[^\n]", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("\nItem cadastrado com sucesso!\n");
}

//  Função: listarItens
//  Objetivo: mostrar todos os itens da mochila
void listarItens(Item mochila[], int total) {
    printf("\n========= Itens na Mochila =========\n");

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

    printf("====================================\n");
}

//  Função: buscarItem
//  Objetivo: localizar um item pelo nome (busca sequencial)
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado na mochila!\n");
}

//  Função: removerItem
//  Objetivo: deletar um item baseado no nome
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia! Nada para remover.\n");
        return;
    }

    char nomeRemove[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemove);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemove) == 0) {
            // Move itens para preencher o espaço
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;

            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem não encontrado! Nada foi removido.\n");
}

//  MAIN
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=============== Menu da Mochila ===============\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4:
                buscarItem(mochila, totalItens);
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
