#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    float y;
} Ponto;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(Uso: %s <arquivo.csv>\n, argv[0]);
        return 1;
    }

    // Abre o arquivo CSV para leitura
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf( %s.\n, argv[1]);
        return 1;
    }

    int numRegistros = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numRegistros++;
    }

    rewind(arquivo);

    Ponto *pontos = (Ponto *)malloc(numRegistros * sizeof(Ponto));
    if (pontos == NULL) {
        fclose(arquivo);
        return 1;
    }

    int somaX = 0;
    float somaY = 0.0;
    for (int i = 0; i < numRegistros; i++) {
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            free(pontos);
            fclose(arquivo);
            return 1;
        }
        sscanf(linha, "%d,%f", &pontos[i].x, &pontos[i].y);
        somaX += pontos[i].x;
        somaY += pontos[i].y;
    }

    fclose(arquivo);

    float mediaX = (float)somaX / numRegistros;
    float mediaY = somaY / numRegistros;

    float somaXY = 0.0;
    float somaXQuadrado = 0.0;
    for (int i = 0; i < numRegistros; i++) {
        somaXY += (pontos[i].x - mediaX) * (pontos[i].y - mediaY);
        somaXQuadrado += (pontos[i].x - mediaX) * (pontos[i].x - mediaX);
    }

    float coeficienteAngular = somaXY / somaXQuadrado;
    float coeficienteLinear = mediaY - coeficienteAngular * mediaX;

    printf("y = %.2fx + %.2f\n", coeficienteAngular, coeficienteLinear);

    free(pontos);

    return 0;
}