#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mediana_de_tres(int *V, int inicio, int meio, int fim) {
    if ((V[inicio] < V[meio] && V[meio] < V[fim]) || (V[fim] < V[meio] && V[meio] < V[inicio]))
        return meio;
    else if ((V[meio] < V[inicio] && V[inicio] < V[fim]) || (V[fim] < V[inicio] && V[inicio] < V[meio]))
        return inicio;
    else
        return fim;
}

int particiona(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;
    
    int meio = (inicio + final) / 2;
    int pivo_idx = mediana_de_tres(V, inicio, meio, final);
    
    aux = V[inicio];
    V[inicio] = V[pivo_idx];
    V[pivo_idx] = aux;
    pivo = V[inicio];

    esq = inicio;
    dir = final;

    while (esq < dir) {
        while (esq <= final && V[esq] <= pivo)
            esq++;
        while (dir >= 0 && V[dir] > pivo)
            dir--;

        if (esq < dir) {
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }

    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}

void quicksort(int *V, int inicio, int fim) {
    int pivo;
    if (fim > inicio) {
        pivo = particiona(V, inicio, fim);
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

    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock();
    quicksort(V, 0, count - 1);
    fim = clock();

    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%d,%.6f\n", count, tempo_execucao);

    free(V);
    return 0;
}
