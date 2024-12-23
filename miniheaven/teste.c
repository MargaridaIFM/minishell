#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s padrão [arquivo...]\n", argv[0]);
        return 1;
    }

    // Criar um vetor de argumentos para o execvp
    char *grep_args[argc + 1];
    grep_args[0] = "grep";  // Comando a ser executado
    for (int i = 1; i < argc; i++) {
        grep_args[i] = argv[i]; // Copiar os argumentos da linha de comando
    }
    grep_args[argc] = NULL;  // Terminar o vetor com NULL

    // Executar o comando grep usando execvp
    if (execvp("grep", grep_args) == -1) {
        perror("Erro ao executar grep");
        return 1;
    }

    // Este código nunca será executado se o execvp for bem-sucedido
    return 0;
}