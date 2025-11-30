/*
  Torre de Resgate - Módulo Avançado de Organização de Componentes
  - Permite cadastrar até 20 componentes (nome, tipo, prioridade)
  - Ordenação por:
      * Bubble sort por nome (string)
      * Insertion sort por tipo (string)
      * Selection sort por prioridade (int)
  - Conta comparações e mede tempo de execução com clock()
  - Busca binária por nome (após ordenação por nome)
  - Menu interativo e funções modularizadas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

/* Estrutura do componente */
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade; /* 1 a 10, maior = mais prioritário */
} Componente;

/* Função para limpar o final de linha de fgets */
void trim_newline(char *s) {
    if (!s) return;
    s[strcspn(s, "\r\n")] = '\0';
}

/* Exibe todos os componentes formatados */
void mostrarComponentes(Componente arr[], int n) {
    printf("\n=== Componentes (total: %d) ===\n", n);
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("%-3s | %-25s | %-12s | %s\n", "Idx", "Nome", "Tipo", "Prioridade");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %-25s | %-12s | %d\n", i+1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("---------------------------------------------------------------\n");
}

/* Troca dois componentes */
void swapComp(Componente *a, Componente *b) {
    Componente tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ------------------------------------------------------------
   Bubble Sort por nome (string)
   Conta comparações no ponteiro comparacoes
   Retorna via modificações no array
   ------------------------------------------------------------ */
void bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    if (comparacoes) *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (comparacoes) (*comparacoes)++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                swapComp(&arr[j], &arr[j+1]);
                trocou = 1;
            }
        }
        if (!trocou) break; /* otimização: lista já ordenada */
    }
}

/* ------------------------------------------------------------
   Insertion Sort por tipo (string)
   Conta comparações
   ------------------------------------------------------------ */
void insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    if (comparacoes) *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = arr[i];
        int j = i - 1;
        /* mover enquanto arr[j].tipo > key.tipo */
        while (j >= 0) {
            if (comparacoes) (*comparacoes)++;
            if (strcmp(arr[j].tipo, key.tipo) > 0) {
                arr[j+1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j+1] = key;
    }
}

/* ------------------------------------------------------------
   Selection Sort por prioridade (int)
   Conta comparações (cada comparação de prioridade incrementa)
   Ordena em ordem crescente por prioridade (se quiser decrescente, inverta)
   Vamos ordenar em ordem decrescente (prioridade maior primeiro),
   então buscamos o índice do máximo a cada iteração.
   ------------------------------------------------------------ */
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    if (comparacoes) *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int idxMax = i;
        for (int j = i + 1; j < n; j++) {
            if (comparacoes) (*comparacoes)++;
            if (arr[j].prioridade > arr[idxMax].prioridade) {
                idxMax = j;
            }
        }
        if (idxMax != i) swapComp(&arr[i], &arr[idxMax]);
    }
}

/* ------------------------------------------------------------
   Busca binária por nome (requer array ordenado por nome)
   Retorna índice encontrado ou -1 se não encontrado.
   Também conta comparações (cada strcmp é uma comparação).
   ------------------------------------------------------------ */
int buscaBinariaPorNome(Componente arr[], int n, const char *chave, long *comparacoes) {
    int left = 0, right = n - 1;
    if (comparacoes) *comparacoes = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (comparacoes) (*comparacoes)++;
        int cmp = strcmp(arr[mid].nome, chave);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/* ------------------------------------------------------------
   Função para clonar um array de componentes (útil para comparar tempos
   sem alterar o original quando necessário)
   ------------------------------------------------------------ */
Componente* clonarArray(Componente src[], int n) {
    Componente *copia = malloc(sizeof(Componente) * n);
    if (!copia) return NULL;
    for (int i = 0; i < n; i++) copia[i] = src[i];
    return copia;
}

/* Menu principal e fluxo do programa */
int main(void) {
    Componente lista[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    int ordenadoPorNome = 0; /* flag para indicar se o último ordenamento foi por nome */

    printf("=== Torre de Resgate - Organização de Componentes ===\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar componente (até %d)\n", MAX_COMPONENTES);
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort)\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Buscar componente-chave por NOME (Busca Binária) [requer ordenação por nome]\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            /* entrada inválida, limpa e continua */
            int c; while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }
        int c; while ((c = getchar()) != '\n' && c != EOF); /* limpar buffer */

        if (opcao == 1) {
            if (total >= MAX_COMPONENTES) {
                printf("Limite de componentes atingido.\n");
                continue;
            }
            printf("Digite nome do componente: ");
            fgets(lista[total].nome, MAX_NOME, stdin);
            trim_newline(lista[total].nome);

            printf("Digite tipo do componente (controle/suporte/propulsao/...): ");
            fgets(lista[total].tipo, MAX_TIPO, stdin);
            trim_newline(lista[total].tipo);

            do {
                printf("Digite prioridade (1 a 10): ");
                if (scanf("%d", &lista[total].prioridade) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Entrada inválida. Insira um número entre 1 e 10.\n");
                    lista[total].prioridade = -1;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                }
            } while (lista[total].prioridade < 1 || lista[total].prioridade > 10);

            total++;
            printf("Componente cadastrado com sucesso.\n");
            ordenadoPorNome = 0; /* qualquer cadastro altera ordem */
        }
        else if (opcao == 2) {
            mostrarComponentes(lista, total);
        }
        else if (opcao == 3) { /* Bubble sort por nome */
            if (total == 0) { printf("Nenhum componente para ordenar.\n"); continue; }
            /* clona para não alterar original se você quiser comparar; aqui alteramos diretamente */
            long comparacoes = 0;
            clock_t start = clock();
            bubbleSortNome(lista, total, &comparacoes);
            clock_t end = clock();
            double tempo = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nOrdenacao por NOME (Bubble Sort) concluida.\n");
            printf("Comparacoes: %ld\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            ordenadoPorNome = 1;
            mostrarComponentes(lista, total);
        }
        else if (opcao == 4) { /* Insertion sort por tipo */
            if (total == 0) { printf("Nenhum componente para ordenar.\n"); continue; }
            long comparacoes = 0;
            clock_t start = clock();
            insertionSortTipo(lista, total, &comparacoes);
            clock_t end = clock();
            double tempo = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nOrdenacao por TIPO (Insertion Sort) concluida.\n");
            printf("Comparacoes: %ld\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            ordenadoPorNome = 0;
            mostrarComponentes(lista, total);
        }
        else if (opcao == 5) { /* Selection sort por prioridade */
            if (total == 0) { printf("Nenhum componente para ordenar.\n"); continue; }
            long comparacoes = 0;
            clock_t start = clock();
            selectionSortPrioridade(lista, total, &comparacoes);
            clock_t end = clock();
            double tempo = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nOrdenacao por PRIORIDADE (Selection Sort) concluida.\n");
            printf("Comparacoes: %ld\n", comparacoes);
            printf("Tempo: %.6f segundos\n", tempo);
            ordenadoPorNome = 0;
            mostrarComponentes(lista, total);
        }
        else if (opcao == 6) { /* Busca binária por nome (requer ordenação por nome) */
            if (!ordenadoPorNome) {
                printf("A busca binaria requer que o vetor esteja ordenado por NOME (execute a opcao 3 primeiro).\n");
                continue;
            }
            if (total == 0) { printf("Nenhum componente cadastrado.\n"); continue; }
            char chave[MAX_NOME];
            printf("Digite o nome do componente-chave a buscar: ");
            fgets(chave, MAX_NOME, stdin);
            trim_newline(chave);

            long comparacoes = 0;
            clock_t start = clock();
            int idx = buscaBinariaPorNome(lista, total, chave, &comparacoes);
            clock_t end = clock();
            double tempo = (double)(end - start) / CLOCKS_PER_SEC;

            printf("\nBusca Binaria por NOME concluida.\n");
            printf("Comparacoes (strcmp usadas): %ld\n", comparacoes);
            printf("Tempo da busca: %.6f segundos\n", tempo);

            if (idx >= 0) {
                printf("Componente encontrado no indice %d:\n", idx+1);
                printf("Nome: %s\nTipo: %s\nPrioridade: %d\n",
                       lista[idx].nome, lista[idx].tipo, lista[idx].prioridade);
                printf("\nComponente-chave confirmado. Pode iniciar a montagem!\n");
            } else {
                printf("Componente nao encontrado. Verifique o nome e tente novamente.\n");
            }
        }
        else if (opcao == 0) {
            printf("Encerrando...\n");
        }
        else {
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
    //cara inciante e veterando simples chega no veterano VIRA BAGUNÇA QUE ISSO AQUI MANO TA MALUCO ISSO NAO ATIVIDADE NAO TEM FIM NEM CHAT GPT TAVA ME AJUDANDO A TERMINA ISSO CADA HORA UMA COISA DIFERENTE MEU DEUS DO CÉU ME AJUDA AI POR FAVOR
}
