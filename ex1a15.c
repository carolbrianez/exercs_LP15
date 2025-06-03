#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char nomeArquivo[100];
    int x, y, width, height;

    printf("Digite o nome do arquivo (sem a extensão .svg): ");
    scanf("%s", nomeArquivo);

    printf("Digite a posição x do quadrado: ");
    scanf("%d", &x);

    printf("Digite a posição y do quadrado: ");
    scanf("%d", &y);

    printf("Digite a largura do quadrado: ");
    scanf("%d", &width);

    printf("Digite a altura do quadrado: ");
    scanf("%d", &height);

    strcat(nomeArquivo, ".svg");

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        return 1;
    }

    fprintf(arquivo, "<svg version=\"1.1\"\n");
    fprintf(arquivo, "     width=\"%d\" height=\"%d\"\n", x + width + 50, y + height + 50);
    fprintf(arquivo, "     xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(arquivo, "  <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"red\" />\n", x, y, width, height);
    fprintf(arquivo, "</svg>\n");

    fclose(arquivo);

    printf("Arquivo SVG '%s' criado com sucesso!\n", nomeArquivo);

    return 0;
}
