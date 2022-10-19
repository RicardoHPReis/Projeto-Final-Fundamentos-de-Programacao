#include <stdio.h>
#include <stdlib.h>
#include "matrizConfig.h"

// Alocando as matrizes que serão utilizadas
void criaMatriz(MatrizConfig *matCfg, MatrizConfig matc)
{
    // Alocando matriz principal
    matCfg->matriz = (char**) malloc (matc.linhas*sizeof(char*));
	matCfg->matrizCopia = (char**) malloc (matc.linhas*sizeof(char*));
    
	// Alocando as fileiras das matrizes
    for (int a = 0; a < matc.linhas; a++) 
	{
        (matCfg->matriz)[a] = (char*) malloc (matc.colunas*sizeof(char));
		(matCfg->matrizCopia)[a] = (char*) malloc (matc.colunas*sizeof(char));
    }
	
    // Preenchendo matrizes
    for (int b = 0; b < matc.linhas; b++)
	{
        for(int c = 0; c < matc.colunas; c++)
		{
            (matCfg->matriz)[b][c] = matc.morto; // Matriz Original
			(matCfg->matrizCopia)[b][c] = matc.morto; //Matriz Cópia
        }
    }
}

void imprimeMatriz(char **mat, MatrizConfig matc)
{
    for (int d = 0; d < matc.linhas; d++)
	{
        for (int e = 0; e < matc.colunas; e++)
		{
            printf("%c ", mat[d][e]);
		}
        printf("\n");
	}
	return;
}
void limpaMatriz(MatrizConfig *matCfg, MatrizConfig matc)
{
	for (int f = 0; f < matc.linhas; f++ )
	{
		free((matCfg->matriz)[f]);
    	free((matCfg->matrizCopia)[f]);
	}
	free(matCfg->matriz);
	free(matCfg->matrizCopia);
}

void bloco(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int g = 0; g < 2; g++)
	{
        for (int h = 0; h < 2; h++)
        	(*mat)[lcX+g][lcY+h] = matc.vivo; 
    }
}
void bote(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int i=0;i<2;i++)
	{
		(*mat)[lcX][lcY+i] = matc.vivo;
		(*mat)[lcX+1][lcY+3*i-1] = matc.vivo;
		(*mat)[lcX+2][lcY+i] = matc.vivo;
	}        
}
void comilao(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int j = 0; j < 2; j++)
        (*mat)[lcX][lcY+j] = matc.vivo;
    for (int k = 0; k < 3; k++)
        (*mat)[lcX+2][lcY+k+1] = matc.vivo;
	(*mat)[lcX+1][lcY] = matc.vivo;
    (*mat)[lcX+3][lcY+3] = matc.vivo;
}

void blinker(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int m = 0; m < 3; m++)
        (*mat)[lcX][lcY+m] = matc.vivo;
}
void frog(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int n = 0; n < 3; n++)
	{
		(*mat)[lcX][lcY+n] = matc.vivo;
		(*mat)[lcX+1][lcY+n-1] = matc.vivo;
	}
}
void glider(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int o = 0; o < 3; o++)
        (*mat)[lcX][lcY+o] = matc.vivo;
    (*mat)[lcX+1][lcY] = matc.vivo;
    (*mat)[lcX+2][lcY+1] = matc.vivo;
}

void lwss(char ***mat, int lcX, int lcY, MatrizConfig matc)
{
    for (int p = 0; p < 2; p++)
        (*mat)[lcX][lcY+p*3] = matc.vivo;
    for (int q=0; q<3; q++)
	{
		(*mat)[lcX+1+q][lcY-1] = matc.vivo;
		(*mat)[lcX+3][lcY+q] = matc.vivo;
	}    
    (*mat)[lcX+2][lcY+3] = matc.vivo;
}