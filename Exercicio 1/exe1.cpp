#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

struct Processo {
    int pid;
    char nome[30];
    int usoCPU;
    int usoMem;
    int ativo; // 1 = executando, 0 = finalizado
};

void listar(struct Processo processos[], int n) {
    printf("\nPID\tNome\t\tCPU\tMem\tStatus\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-10s\t%d%%\t%d%%\t%s\n",
            processos[i].pid,
            processos[i].nome,
            processos[i].usoCPU,
            processos[i].usoMem,
            processos[i].ativo ? "Executando" : "Finalizado"
        );
    }
}

void finalizar(struct Processo processos[], int n) {
    int pid, i, achou = 0;
    printf("Digite o PID do processo que deseja finalizar: ");
    scanf("%d", &pid);

    for (i = 0; i < n; i++) {
        if (processos[i].pid == pid && processos[i].ativo) {
            processos[i].ativo = 0;
            processos[i].usoCPU = 0;
            processos[i].usoMem = 0;
            printf("Processo finalizado com sucesso!\n");
            achou = 1;
            break;
        }
    }

    if (!achou)
        printf("Processo não encontrado ou já finalizado.\n");
}

int main() {
    struct Processo processos[MAX] = {
        {1001, "chrome", 15, 30, 1},
        {1002, "discord", 10, 20, 1},
        {1003, "explorer", 5, 15, 1},
        {1004, "notepad", 2, 5, 1},
        {1005, "steam", 20, 40, 1}
    };

    int opcao;

    do {
        printf("\n=== GERENCIADOR DE TAREFAS (SIMULADO) ===\n");
        printf("1. Listar processos\n");
        printf("2. Finalizar processo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: listar(processos, MAX); break;
            case 2: finalizar(processos, MAX); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!.\n");
        }

    } while (opcao != 0);

    return 0;
}
