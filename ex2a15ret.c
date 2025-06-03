//Crie a função retangulo que tem como argumento um ponteiro para um stream, a função deve receber do usuário a posição de um quadrado (x e y), a largura (width), a altura (height) e imprimir no stream recebido o rect

#include <stdio.h>

void retangulo(FILE *arquivo) {
    int x, y, width, height;

    printf("Digite a posição x do retângulo: ");
    scanf("%d", &x);

    printf("Digite a posição y do retângulo: ");
    scanf("%d", &y);

    printf("Digite a largura do retângulo: ");
    scanf("%d", &width);

    printf("Digite a altura do retângulo: ");
    scanf("%d", &height);

    fprintf(arquivo, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"blue\" />\n", x, y, width, height);
}

int main() {
    FILE *arquivoSVG = fopen("retangulo.svg", "w");

    if (arquivoSVG == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(arquivoSVG, "<svg version=\"1.1\" width=\"500\" height=\"500\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    retangulo(arquivoSVG);

    fprintf(arquivoSVG, "</svg>\n");

    fclose(arquivoSVG);

    printf("Arquivo SVG 'retangulo.svg' criado com sucesso!\n");

    return 0;
}

