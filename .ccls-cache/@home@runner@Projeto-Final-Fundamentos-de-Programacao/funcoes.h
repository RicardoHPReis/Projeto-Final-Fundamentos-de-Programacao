#include <stdio.h>
#include <stdlib.h>

// Alocando as matrizes que serão utilizadas
char **criaMatriz(char ** mat, int numeroLinha, int numeroColuna, char morto)
{
    int i, j;
    // Alocando matriz principal
    mat = (char **)malloc(numeroLinha * sizeof(char *));
    // Alocando as fileiras das matrizes
    for (i = 0; i < numeroColuna; i ++) {
        mat[i] = (char *)malloc(numeroColuna * sizeof(char));
    }
    // Preenchendo matrizes
    for (i = 0; i < numeroLinha; i ++){
        for(j = 0; j < numeroColuna; j ++){
            mat[i][j] = morto; // Matriz Original
        }
    }

    return mat;
}

char **criaMatrizCopia(char **matCopia, int numeroLinha, int numeroColuna, char morto)
{
    int i, j;
    // Alocando matriz cópia
    matCopia = (char **) malloc (numeroLinha * sizeof(char *));
    // Alocando as fileiras das matrizes
    for (i = 0; i < numeroColuna; i ++) {
        matCopia[i] = (char *)malloc(numeroColuna * sizeof(char));
    }
    // Preenchendo matrizes
    for (i = 0; i < numeroLinha; i ++){
        for(j = 0; j < numeroColuna; j ++){
            matCopia[i][j] = morto; // Matriz Cópia
        }
    }

    return matCopia;
}

void imprimeMatriz(char **mat, int numeroLinha, int numeroColuna)
{
    int i, j;
    for (i=0;i<numeroLinha;i++){
        for(j=0;j<numeroColuna;j++){
            printf("%c ", mat[i][j]);}
            printf("\n");}
	return;
}
void limpaMatriz(char **mat, int numeroLinha)
{
    int i;
    for (i = 0; i < numeroLinha; i++ )
    free(mat[i]);
    free(mat);
	return;
}

void bloco(char **mat, int linha, int coluna, char vivo)
{
    int i, j;
    for (i=0;i<2;i++){
        for(j=0;j<2;j++){
            mat[i+linha][j+coluna] = vivo;}}
	return;
}
void bote(char **mat, int linha, int coluna, char vivo)
{

    int i;
    for (i=0;i<2;i++)
        mat[linha][coluna+i]=vivo;
    for (i=0;i<2;i++)
        mat[linha+1][coluna-1+(3*i)]=vivo;
    for (i=0;i<2;i++)
        mat[linha+2][coluna+i]=vivo;
	return;
}
void comilao(char **mat, int linha, int coluna, char vivo)
{
    int i;
    for (i=0;i<2;i++)
        mat[linha][coluna+i]=vivo;
    mat[linha+1][coluna]=vivo;
    for (i=0;i<3;i++)
        mat[linha+2][coluna+1+i]=vivo;
    mat [linha+3][coluna+3]=vivo;
	return;
}

void blinker(char **mat, int linha, int coluna, char vivo)
{
    int i;
    for (i=0;i<3;i++)
        mat[linha][coluna+i]=vivo;
	return;
}
void frog(char **mat, int linha, int coluna, char vivo)
{
    int i;
    for (i=0;i<3;i++)
        mat[linha][coluna+i]=vivo;
    for (i=0;i<3;i++)
        mat[linha+1][coluna+i-1]=vivo;
	return;
}
void glider(char **mat, int linha, int coluna, char vivo)
{
   int i;
    for (i=0;i<3;i++)
        mat[linha][coluna+i]=vivo;
    mat[linha+1][coluna]=vivo;
    mat[linha+2][coluna+1]=vivo;
	return;
}

void lwss(char **mat, int linha, int coluna, char vivo)
{
   
    int i;
    for (i=0;i<2;i++)
        mat[linha][coluna+(3*i)]=vivo;
    for (i=0;i<3;i++)
        mat[linha+1+i][coluna-1]=vivo;
    for (i=0;i<3;i++)
        mat[linha+3][coluna+i]=vivo;
    mat[linha+2][coluna+3]=vivo;
	return;
}