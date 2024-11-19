#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mediana_de_tres(int *V, int inicio, int fim) {
    int idx1 = inicio + rand() % (fim - inicio + 1);
    int idx2 = inicio + rand() % (fim - inicio + 1);
    int idx3 = inicio + rand() % (fim - inicio + 1);

    int val1 = V[idx1];
    int val2 = V[idx2];
    int val3 = V[idx3];

    // Encontrar a mediana dos três valores
    if ((val1 <= val2 && val2 <= val3) || (val3 <= val2 && val2 <= val1))
        return idx2;
    else if ((val2 <= val1 && val1 <= val3) || (val3 <= val1 && val1 <= val2))
        return idx1;
    else
        return idx3;
}

int particiona(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;
    
    int pivo_idx = mediana_de_tres(V, inicio, final);
    
    aux = V[inicio];
    V[inicio] = V[pivo_idx];
    V[pivo_idx] = aux;
    pivo = V[inicio];

    esq = inicio + 1;
    dir = final;

    while (esq <= dir) {
        while (esq <= final && V[esq] <= pivo)
            esq++;
        while (dir > inicio && V[dir] > pivo)
            dir--;

        if (esq < dir) {
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
            esq++;
            dir--;
        }
    }

    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}

void quicksort(int *V, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(V, inicio, fim);
        quicksort(V, inicio, pivo - 1);
        quicksort(V, pivo + 1, fim);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    char *nome_arquivo = argv[1];
    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int count = 0;
    int num;
    while (fscanf(fp, "%d", &num) == 1) {
        count++;
    }

    int *V = (int *)malloc(count * sizeof(int));
    if (V == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        fclose(fp);
        return 1;
    }

    rewind(fp);
    int i = 0;
    while (i < count && fscanf(fp, "%d", &V[i]) == 1) {
        i++;
    }
    fclose(fp);

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    clock_t inicio_tempo, fim_tempo;
    double tempo_execucao;

    inicio_tempo = clock();
    quicksort(V, 0, count - 1);
    fim_tempo = clock();

    tempo_execucao = ((double)(fim_tempo - inicio_tempo)) / CLOCKS_PER_SEC;
    printf("%d,%.6f\n", count, tempo_execucao);

    free(V);
    return 0;
}
