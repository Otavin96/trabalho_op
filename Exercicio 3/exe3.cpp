#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCOS 50

typedef struct {
    int id;
    int tamanho;
    int ocupado; // 0 = livre, 1 = ocupado
} Bloco;

Bloco blocos[MAX_BLOCOS];
int total_blocos = 0;
int proximo_id = 0;

// Inicializa com um único bloco livre de tamanho 20
void inicializar() {
    blocos[0].id = proximo_id++;
    blocos[0].tamanho = 20;
    blocos[0].ocupado = 0;
    total_blocos = 1;
}

// Mostra todos os blocos na tela
void mostrar_blocos() {
    printf("\nEstado atual da memoria:\n");
    for (int i = 0; i < total_blocos; i++) {
        printf("Bloco ID %d | Tamanho: %d | %s\n",
               blocos[i].id,
               blocos[i].tamanho,
               blocos[i].ocupado ? "Ocupado" : "Livre");
    }
}

// Tenta alocar memória com First Fit
void alocar(int tamanho) {
    for (int i = 0; i < total_blocos; i++) {
        if (!blocos[i].ocupado && blocos[i].tamanho >= tamanho) {
            if (blocos[i].tamanho == tamanho) {
                blocos[i].ocupado = 1;
            } else {
                // Dividir o bloco
                for (int j = total_blocos; j > i + 1; j--) {
                    blocos[j] = blocos[j - 1];
                }

                blocos[i + 1].id = proximo_id++;
                blocos[i + 1].tamanho = blocos[i].tamanho - tamanho;
                blocos[i + 1].ocupado = 0;

                blocos[i].tamanho = tamanho;
                blocos[i].ocupado = 1;
                total_blocos++;
            }
            printf("Bloco alocado com sucesso!\n");
            return;
        }
    }
    printf("Erro: nao foi possivel alocar memoria.\n");
}

void desalocar(int id) {
    int i;
    for (i = 0; i < total_blocos; i++) {
        if (blocos[i].id == id && blocos[i].ocupado) {
            blocos[i].ocupado = 0;
            break;
        }
    }


    if (i < total_blocos - 1 && !blocos[i].ocupado && !blocos[i + 1].ocupado) {
        blocos[i].tamanho += blocos[i + 1].tamanho;
        for (int j = i + 1; j < total_blocos - 1; j++) {
            blocos[j] = blocos[j + 1];
        }
        total_blocos--;
    }

    if (i > 0 && !blocos[i].ocupado && !blocos[i - 1].ocupado) {
        blocos[i - 1].tamanho += blocos[i].tamanho;
        for (int j = i; j < total_blocos - 1; j++) {
            blocos[j] = blocos[j + 1];
        }
        total_blocos--;
    }
    printf("Bloco desalocado com sucesso!\n");
}

int main() {
    inicializar();

    int opcao;
    while (1) {
        mostrar_blocos();
        printf("\n1 - Alocar memoria\n2 - Desalocar bloco\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;
        else if (opcao == 1) {
            int tam;
            printf("Digite o tamanho do bloco a alocar: ");
            scanf("%d", &tam);
            alocar(tam);
        } else if (opcao == 2) {
            int id;
            printf("Digite o ID do bloco a desalocar: ");
            scanf("%d", &id);
            desalocar(id);
        } else {
            printf("Opção invalida.\n");
        }
    }

    return 0;
}

