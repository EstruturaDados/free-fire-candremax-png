#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções do sistema
void inserirItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void buscarItem(Item mochila[], int totalItens);

int main() {
    Item mochila[MAX_ITENS]; // Vetor que representa a mochila
    int totalItens = 0;      // Controla quantos itens estão na mochila
    int opcao;

    do {
        printf("\n=== Sistema de Inventario ===\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

// Função para inserir um item
void inserirItem(Item mochila[], int *totalItens) {
    if(*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remove \n do final

    printf("Digite o tipo do item (arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // Limpar buffer

    mochila[*totalItens] = novoItem;
    (*totalItens)++;
    printf("Item adicionado com sucesso!\n");

    listarItens(mochila, *totalItens);
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *totalItens) {
    if(*totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for(int i = 0; i < *totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Remove item deslocando os seguintes
            for(int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*totalItens)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if(!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }

    listarItens(mochila, *totalItens);
}

// Função para listar todos os itens
void listarItens(Item mochila[], int totalItens) {
    if(totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for(int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", 
                i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial por nome
void buscarItem(Item mochila[], int totalItens) {
    if(totalItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
}
