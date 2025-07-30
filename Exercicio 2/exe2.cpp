#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define QUANTUM 2

typedef struct {
    int pid;
    int pid_pai;
    int tempo_execucao;
    int tempo_restante;
    bool concluido;
} Processo;

void simular_round_robin(Processo processos[], int n) {
    int tempo = 0, completados = 0;

    printf("\n--- Execucao Round Robin ---\n");

    while (completados < n) {
        for (int i = 0; i < n; i++) {
            if (!processos[i].concluido) {
                int exec = (processos[i].tempo_restante > QUANTUM) ? QUANTUM : processos[i].tempo_restante;

                printf("P%d de t=%d execucao t=%d\n", processos[i].pid, tempo, tempo + exec);

                tempo += exec;
                processos[i].tempo_restante -= exec;

                if (processos[i].tempo_restante == 0) {
                    processos[i].concluido = true;
                    completados++;
                }
            }
        }
    }
}

void imprimir_arvore(Processo processos[], int n) {
    printf("\n--- Arvore de Processos ---\n");

    for (int i = 0; i < n; i++) {
        if (processos[i].pid_pai == 0) {
            printf("P%d (pai: %d)\n", processos[i].pid, processos[i].pid_pai);

            for (int j = 0; j < n; j++) {
                if (processos[j].pid_pai == processos[i].pid) {
                    printf("  P%d (pai: %d)\n", processos[j].pid, processos[j].pid_pai);

                    for (int k = 0; k < n; k++) {
                        if (processos[k].pid_pai == processos[j].pid) {
                            printf("    P%d (pai: %d)\n", processos[k].pid, processos[k].pid_pai);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    Processo processos[MAX];

    printf("Quantos processos deseja criar? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processos[i].pid = i + 1;
        printf("\nProcesso P%d:\n", processos[i].pid);
        printf("  PID do pai (0 se for raiz): ");
        scanf("%d", &processos[i].pid_pai);
        printf("  Tempo de execucao: ");
        scanf("%d", &processos[i].tempo_execucao);

        processos[i].tempo_restante = processos[i].tempo_execucao;
        processos[i].concluido = false;
    }

    simular_round_robin(processos, n);
    imprimir_arvore(processos, n);

    return 0;
}
