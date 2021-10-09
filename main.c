#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_COLUNA 150
#define TAM_LINHA 150
#define TAM_VALIDO 20

void carregaImagem(int imagem[][TAM_COLUNA]);
void printaImagem(int imagem[][TAM_COLUNA]);
void processaImagem(int imagem[][TAM_COLUNA]);
bool validacao(int imagem[][TAM_COLUNA], int col, int lin);
bool quadradoValida(int imagem[][TAM_COLUNA], int col, int lin);

int tam_lin, tam_col;

int main() {
    int imagem[TAM_LINHA][TAM_COLUNA];

    carregaImagem(imagem);

    printaImagem(imagem);

    processaImagem(imagem);

}

void carregaImagem(int imagem[][TAM_COLUNA]) {
    FILE *arq;
    arq = fopen("qr_invalido.pgm", "r");
    char buffer;
    char *tempStr = malloc(2 *sizeof(char));;
    if(arq == NULL) {
        printf("\nERRO NA ABERTURA DO ARQUIVO!\n");
    } else {
        for(int k=0; k<49; k++) {
            fscanf(arq, "%c",&buffer);
        }

        fscanf(arq, "%d %d",&tam_col, &tam_lin);

        while(!feof(arq)) {
            for(int lin=0; lin < tam_lin; lin++) {
                for(int col=0; col < tam_col; col++) {
                    fscanf(arq,"%d", &imagem[lin][col]);
                }
            }
        }
    }
    fclose(arq);
}

void printaImagem(int imagem[][TAM_COLUNA]) {
    for(int lin=0; lin < tam_lin; lin++) {
        for(int col=0; col < tam_col; col++) {
            if(imagem[lin][col] == 255) {
                printf("%c", 178);
            } else if(imagem[lin][col] == 0) {
                printf(" ", imagem[lin][col]);
            }
        }
        printf("\n");
    }
}

void processaImagem(int imagem[][TAM_COLUNA]) {
    bool valido1 = false;
    bool valido2 = false;
    bool valido3 = false;

    for(int lin=0; lin < tam_lin; lin++)
    {
        for(int col=0; col < tam_col; col++)
        {
            if(imagem[lin][col]!=255)
            {
                if(lin < 40 && col < 40 && valido1 == false) {
                    if (validacao(imagem, col, lin) == true) {
                        valido1 = true;
                    }
                }
                if(lin < 40 && col > 55 && valido2 == false) {
                    if (validacao(imagem, col, lin) == true) {
                        valido2 = true;
                    }
                }
                if(lin > 60 && col < 40 && valido3 == false) {
                    if (validacao(imagem, col, lin) == true) {
                        valido3 = true;
                    }
                }
            }

        }
    }
    if (valido1 == true) {
        printf("\nSuperior esquerdo valido\n");
    } else {
        printf("\nSuperior esquerdo invalido\n");
    }
    if (valido2 == true) {
        printf("\nSuperior direito valido\n");
    } else {
        printf("\nSuperior direito invalido\n");
    }
    if (valido3 == true) {
        printf("\nInferior esquerdo valido\n");
    } else {
        printf("\nInferior esquerdo invalido\n");
    }

    if(valido1 && valido2 && valido3) {
        printf("\nQR code valido\n");
    } else {
        printf("\nQR code invalido\n");
    }
}

bool validacao(int imagem[][TAM_COLUNA], int col, int lin){

    int count = 0;
    bool valido = true;
    bool loop = true;
    col++;
    lin++;
    int linMedia = lin;
    int colMedia = col;

    while(loop && valido) {
        if (imagem[lin][col] == 0) {
            count++;
        }
        if (imagem[lin][col] == 255) {
            loop = false;
            col -= 3;
        }
        col++;
    }
    colMedia = (colMedia + col)/2;
    if (count < TAM_VALIDO) {
        valido = false;
    }
    loop = true;
    count = 0;

    while(loop && valido) {
        if (imagem[lin][col] == 0) {
            count++;
        }
        if (imagem[lin][col] == 255) {
            loop = false;
            lin -= 3;
        }
        lin++;
    }
    linMedia = (linMedia + lin)/2;
    if (count < TAM_VALIDO) {
        valido = false;
    }
    loop = true;
    count = 0;

    while(loop && valido) {
        if (imagem[lin][col] == 0) {
            count++;
        }
        if (imagem[lin][col] == 255 || col < 0) {
            loop = false;
            col += 3;
        }
        col--;
    }
    if (count < TAM_VALIDO) {
        valido = false;
    }
    loop = true;
    count = 0;

    while(loop && valido) {
        if (imagem[lin][col] == 0) {
            count++;
        }
        if (imagem[lin][col] == 255 || lin < 0) {
            loop = false;
            lin += 3;
        }
        lin--;
    }
    if (count < TAM_VALIDO) {
        valido = false;
    }
    loop = true;
    count = 0;

    if (valido == true) {
        lin = linMedia;
        col = colMedia;
        if (imagem[lin][col] == 0) {
            while(imagem[lin][col] != 255) {
                lin--;
            }
            lin++;

            while(imagem[lin][col] != 255) {
                col--;
            }
            col++;
        }
        bool validaQuad = false;
        if(imagem[lin][col] == 0) {
            validaQuad = quadradoValida(imagem, col, lin);
        }
        return validaQuad;

    } else {
        return false;
    }

}

bool quadradoValida(int imagem[][TAM_COLUNA], int col, int lin){
    col++;
    int lin_ini = lin;
    int col_limit = col;
    int count = 0;

    while(imagem[lin][col_limit] == 0) {
        col_limit++;
    }
    while(col != col_limit) {
        while (imagem[lin][col] == 0) {
            count++;
            lin++;
        }
        lin = lin_ini;
        col++;
    }
    if(count > 90) {
        return true;
    } else {
        return false;
    }

}
