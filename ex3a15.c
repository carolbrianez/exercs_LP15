#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void circulo(FILE *fp, int cx, int cy, int raio, const char *cor) {
    fprintf(fp, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"%s\" />\n", cx, cy, raio, cor);
}

void linha(FILE *fp, int x1, int y1, int x2, int y2, const char *cor, int espessura) {
    fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"%d\" />\n", x1, y1, x2, y2, cor, espessura);
}

void texto(FILE *fp, int x, int y, const char *conteudo, const char *cor, int tamanho) {
    fprintf(fp, "<text x=\"%d\" y=\"%d\" fill=\"%s\" font-size=\"%d\">%s</text>\n", x, y, cor, tamanho, conteudo);
}

void retangulo(FILE *fp, int x, int y, int largura, int altura, const char *cor) {
    fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" />\n", x, y, largura, altura, cor);
}

void mostrarCores() {
    printf("\n[ATENÇÃO]\n");
    printf("Ao informar o nome da cor, utilize a palavra em INGLÊS.\n");
    printf("Exemplo: red, blue, green, yellow, black, white, gray, orange, purple, pink, brown, cyan, magenta\n");
    printf("Você também pode usar códigos hexadecimais (ex: #ff0000 para vermelho).\n");
}

int main() {
    char nomeArquivo[100];
    FILE *fp;
    char entrada[256];
    char figura;

    mostrarCores();

    printf("Digite o nome do arquivo SVG: ");
    if (!fgets(nomeArquivo, sizeof(nomeArquivo), stdin)) {
        fprintf(stderr, "Erro ao ler o nome do arquivo.\n");
        return 1;
    }
    nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;

    fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(fp, "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    while (1) {
        printf("Digite a figura (R para Retângulo, C para Círculo, L para Linha, T para Texto, F para finalizar): ");
        if (!fgets(entrada, sizeof(entrada), stdin))
            break;
        if (sscanf(entrada, " %c", &figura) != 1)
            continue;

        if (figura == 'F' || figura == 'f') {
            break;
        }

        switch (figura) {
            case 'R':
            case 'r': {
                int x, y, largura, altura;
                char cor[20];
                printf("Digite x, y, largura, altura e cor do retângulo (separe por ESPAÇO, NÃO por vírgula | cor em INGLÊS): ");
                if (fgets(entrada, sizeof(entrada), stdin) &&
                    sscanf(entrada, "%d %d %d %d %19s", &x, &y, &largura, &altura, cor) == 5) {
                    retangulo(fp, x, y, largura, altura, cor);
                } else {
                    printf("Entrada inválida para retângulo.\n");
                }
                break;
            }
            case 'C':
            case 'c': {
                int cx, cy, raio;
                char cor[20];
                printf("Digite cx, cy, raio e cor do círculo (separe por ESPAÇO, NÃO por vírgula | cor em INGLÊS): ");
                if (fgets(entrada, sizeof(entrada), stdin) &&
                    sscanf(entrada, "%d %d %d %19s", &cx, &cy, &raio, cor) == 4) {
                    circulo(fp, cx, cy, raio, cor);
                } else {
                    printf("Entrada inválida para círculo.\n");
                }
                break;
            }
            case 'L':
            case 'l': {
                int x1, y1, x2, y2, espessura;
                char cor[20];
                printf("Digite x1, y1, x2, y2, cor e espessura da linha (separe por ESPAÇO, NÃO por vírgula | cor em INGLÊS): ");
                if (fgets(entrada, sizeof(entrada), stdin) &&
                    sscanf(entrada, "%d %d %d %d %19s %d", &x1, &y1, &x2, &y2, cor, &espessura) == 6) {
                    linha(fp, x1, y1, x2, y2, cor, espessura);
                } else {
                    printf("Entrada inválida para linha.\n");
                }
                break;
            }
            case 'T':
            case 't': {
                int x, y, tamanho;
                char conteudo[100], cor[20];
                printf("Digite o valor de x: ");
                if (!(fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%d", &x) == 1)) {
                    printf("Entrada inválida para x.\n");
                    break;
                }
                printf("Digite o valor de y: ");
                if (!(fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%d", &y) == 1)) {
                    printf("Entrada inválida para y.\n");
                    break;
                }

                printf("Digite o conteúdo do texto: ");
                if (!fgets(conteudo, sizeof(conteudo), stdin)) {
                    printf("Erro ao ler o conteúdo do texto.\n");
                    break;
                }
                conteudo[strcspn(conteudo, "\n")] = 0;

                printf("Digite cor e tamanho do texto (separe por ESPAÇO, NÃO por vírgula | cor em INGLÊS): ");
                if (!(fgets(entrada, sizeof(entrada), stdin) &&
                      sscanf(entrada, "%19s %d", cor, &tamanho) == 2)) {
                    printf("Entrada inválida para cor/tamanho do texto.\n");
                    break;
                }
                texto(fp, x, y, conteudo, cor, tamanho);
                break;
            }
            default:
                printf("Figura inválida.\n");
        }
    }

    fprintf(fp, "</svg>\n");
    fclose(fp);
    printf("Arquivo SVG '%s' criado com sucesso.\n", nomeArquivo);

    return 0;
}