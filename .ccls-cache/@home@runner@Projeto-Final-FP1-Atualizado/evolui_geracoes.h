#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes_desenhos.h"
#ifdef _WIN32 
    #include <Windows.h> 
    #define LIMPA "cls"
#else 
    #include <unistd.h> 
    #define LIMPA "clear"
#endif

void montaMatrizArquivo(char ***matriz, int locX, int locY, MatrizConfig matc) 
{
    // Linha do arquivo
    char line[200];
    char *token;
    // Números escritos no arquvio
    int numero;
    // Linha da matriz
    int linhaMatriz = locX;

    // Arquivo contendo a configuração da matriz
    FILE *arquivo = fopen("desenho.csv", "r");

    // Caso não consiga abrir o arquivo
    if (arquivo == NULL) 
	{
        perror("Unable to read the file");
        exit(1);
    }

    // Lendo as linhas do arquivo
    while(fgets(line, sizeof(line), arquivo)) 
	{
        // Separando a linha pelas virgulas
        token = strtok(line, ",");
        // Lendo até que não encontre mais nada na linha
        while(token != NULL) 
		{
            // Convertendo string para inteiro
            numero = atoi(token);
            numero --;
            (*matriz)[linhaMatriz][numero+locY] = matc.vivo;
            token = strtok(NULL, ",");
        }
        linhaMatriz ++;
    }
    // Fechando o arquivo
    fclose(arquivo);
}

// Analisando se o caractére é vivo ou morto
int contVivo(char *vet, MatrizConfig matc) 
{
    // Quantidade de caracteres vivos
    int cont = 0;
    for (int a = 0; a < 8; a ++)
	{
		 if (vet[a] == matc.vivo)
            cont ++;
	}
    free(vet);
    return cont;
}

int analisaVizinho(char*** matOriginal, MatrizConfig matc, int lcX, int lcY) 
{
    // Vetor de caracteres
    char *vet;
    vet = (char*) malloc (8 * sizeof(char));
    // Preenchendo o vetor com o caractere correspondente a celula morta
    for (int valor = 0; valor < lcX; valor ++) 
            vet[valor] = matc.morto;
    // Analisando os vizinhos da celula
    // Vizinho a direita
    if (lcY + 1 < matc.colunas) 
		vet[0] = (*matOriginal)[lcX][lcY + 1];
    
	// Vizinho na diagonal inferior direita
    if (lcX + 1 < matc.linhas && lcY + 1 < matc.colunas)
		vet[1] = (*matOriginal)[lcX + 1][lcY + 1];
    
	// Vizinho abaixo
    if (lcX + 1 < matc.linhas) 
		vet[2] = (*matOriginal)[lcX + 1][lcY];
    
	// Vizinho na diagonal inferior esquerda
    if (lcX + 1 < matc.linhas && lcY - 1 >= 0)
		vet[3] = (*matOriginal)[lcX + 1][lcY - 1];
    
	// Vizinho a esquerda
    if (lcY - 1 >= 0)
		vet[4] = (*matOriginal)[lcX][lcY - 1];
    
	// Vizinho na diagonal superior esquerda
    if (lcX - 1 >= 0 && lcY - 1 >= 0)
		vet[5] = (*matOriginal)[lcX - 1][lcY - 1];
    
	// Vizinho acima
    if (lcX - 1 >= 0)
		vet[6] = (*matOriginal)[lcX - 1][lcY];
    
	// Vizinho na diagonal superior direita
    if (lcX - 1 >= 0 && lcY + 1 < matc.colunas) 
		vet[7] = (*matOriginal)[lcX - 1][lcY + 1];

    // Calculando a quantidade de celulas vivas
    return contVivo(vet, matc);
}


void evoluiGeracao(char ***matOriginal, char ***matCopia, MatrizConfig matc)
{
    // Número de células vizinhas vivas de outra célula
    int vizinhoVivo = 0;
    // Celula atual
    char celula;
    // Passando pelas células da matriz para decidir se a celula vive ou morre
    for (int b = 0; b < matc.linhas; b++) 
	{
        for (int c = 0; c < matc.colunas; c++)
		{
            celula = (*matOriginal)[b][c];
            vizinhoVivo = analisaVizinho(matOriginal, matc, b, c);
            // Definindo se a celula ficará viva ou morta
            if (celula ==  matc.vivo) 
			{
                // Uma célula viva permanece viva se tiver 2 ou 3 células vizinhas vivas
                if (vizinhoVivo == 2 || vizinhoVivo == 3) 
                    celula = matc.vivo;
                // Uma célula viva, com menos de 2 ou mais de 3 células vizinhas vivas morre
                else if (vizinhoVivo < 2 || vizinhoVivo > 3)
                    celula = matc.morto;
            }
            // Uma célula morta ganha vida se tiver exatamente 3 células vizinhas vivas
            else if (celula == matc.morto && vizinhoVivo == 3)
                celula = matc.vivo;
            (*matCopia)[b][c] = celula;
        }
    }
}

void configuraMatriz(char ***matriz, MatrizConfig matCfg)
{
    // Vida eterna
    if (matCfg.modo == 1) 
	{
        if (matCfg.figura == 'A') //Bloco
            bloco(matriz, matCfg.locX, matCfg.locY, matCfg);
        else if (matCfg.figura == 'B') //Bote
            bote(matriz, matCfg.locX, matCfg.locY, matCfg);
        else // Comilão
            comilao(matriz, matCfg.locX, matCfg.locY, matCfg);
    }
    // Osciladores
    else if (matCfg.modo == 2) 
	{
        if (matCfg.figura == 'A') //Blinker
            blinker(matriz, matCfg.locX, matCfg.locY, matCfg);
        else if (matCfg.figura == 'B') //Sapo
            frog(matriz, matCfg.locX, matCfg.locY, matCfg);
    }
    // Naves espaciais
    else if (matCfg.modo == 3)
	{
        if (matCfg.figura == 'A') // Glider
            glider(matriz, matCfg.locX, matCfg.locY, matCfg);
        else if (matCfg.figura == 'B') //LWSS
            lwss(matriz, matCfg.locX, matCfg.locY, matCfg);
    }
    // Lendo a partir de um arquivo .csv
    else
        montaMatrizArquivo(matriz, matCfg.locX, matCfg.locY, matCfg);
}


void configuraMatrizInvasor(char ***matrizInvasor, MatrizConfig matCfg)
{
    // Vida eterna
    if (matCfg.modoInv == 1)
	{    
        if (matCfg.figuraInv == 'A') //Bloco
            bloco(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
        else if (matCfg.figuraInv == 'B') //Bote
            bote(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
        else //Comilão
            comilao(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
    }
    // Osciladores
    else if (matCfg.modoInv == 2) 
	{
        if (matCfg.figuraInv == 'A') //Blinker
            blinker(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
        else if (matCfg.figuraInv == 'B') //Sapo
            frog(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
    }
    // Naves espaciais
    else if (matCfg.modoInv == 3) 
	{
        if (matCfg.figuraInv == 'A') //Glider       
            glider(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
        else if (matCfg.figuraInv == 'B') //LWSS
            lwss(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
    }
    // Lendo a partir de um arquivo .csv
    else
        montaMatrizArquivo(matrizInvasor, matCfg.locXInv, matCfg.locYInv, matCfg);
}

void simulaGeracoes (MatrizConfig matCfg)
{
    // Criando a matriz e preenchendo com zero
	criaMatriz(&matCfg, matCfg);   
    configuraMatriz(&matCfg.matriz, matCfg);
    // Caso os invasores devam ser adicionados já na primeira geração
    if (matCfg.inicioInv == 1)
    	configuraMatrizInvasor(&matCfg.matriz, matCfg);

    // Imprimindo a matriz
    usleep(500*1000);;
	system(LIMPA);
    imprimeMatriz(matCfg.matriz, matCfg);

    for (int d = 2; d <= matCfg.numGeracoes; d++) 
	{
	    // Espera um metade de um segundo e limpa a tela
	    usleep(500*1000);
		system(LIMPA);
	    // Modificando matriz cópia
	    if (d % 2 == 0)
		{
	        evoluiGeracao(&matCfg.matriz, &matCfg.matrizCopia, matCfg);
	        // Caso esteja na hora de adicionar a célula invasora
	        if (d == matCfg.inicioInv)
	        	configuraMatrizInvasor(&matCfg.matrizCopia, matCfg);
			imprimeMatriz(matCfg.matrizCopia, matCfg); // Imprimindo matriz cópia
	    }
	    // Modificando matriz original
	    else 
		{
	        evoluiGeracao(&matCfg.matrizCopia, &matCfg.matriz, matCfg);
	        // Caso esteja na hora de adicionar a célula invasora
	        if (d == matCfg.inicioInv)
	            configuraMatrizInvasor(&matCfg.matriz, matCfg);
	        imprimeMatriz(matCfg.matriz, matCfg); // Imprimindo matriz original
	    }
    }
    limpaMatriz(&matCfg, matCfg);
}