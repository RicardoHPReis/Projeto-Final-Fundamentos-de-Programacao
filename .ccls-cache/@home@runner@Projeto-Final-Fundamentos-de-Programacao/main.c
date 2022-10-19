// Projeto Final - Fundamentos de Programação
// Equipe:
// Ricardo Henrique Pires dos Reis
// Victor Gabriel Rodrigues da Silva
// Johnny Sarafim Pinto

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_config.h"
#ifdef _WIN32
    #include <Windows.h>
    #define LIMPA "cls"
#else
    #include <unistd.h>
    #define LIMPA "clear"
#endif

int main(void)
{
	// Configurações da matriz de jogo
	MatrizConfig matCfg;
	matCfg.modo = 0; // Modo de início
	matCfg.figura= '@'; //Figura de início
	matCfg.linhas = 15; // Tamanho padrão matriz
	matCfg.colunas = 15;  // Tamanho padrão matriz
	matCfg.numGeracoes = 10; // Numero de gerações padrão
	matCfg.vivo = '0', matCfg.morto = '.'; // Caracteres vivo e morto padrão
	
	/* Enquanto o usuário não selecionar a opção de terminar o jogo (7 numérico),
	 o menu inicial será mostrado após cada simulação */
	while (matCfg.modo != 7)
	{
		srand(time(NULL));
		int resposta = 0, respostaInserir = 0, respostaInv = 0;
		system(LIMPA);
		selecao_Menu_Modo(&matCfg); // Imprime menu
		
		if (matCfg.modo == 7) // Encerra o jogo
		{
	    	fim_de_Jogo();
	    	continue;
		}
		
		else if (matCfg.modo == 6) // Descrição das regras
		{
	    	descricaoRegras();
	    	continue;
		}

		else if (matCfg.modo == 5) // Descrição dos modos de jogo
		{
	    	descricaoModos();
	    	continue;
		}
		
		// Caso o usuário seleciona uma opção para iniciar o jogo
		else
		{
			// Caso o usuário que iniciar a matriz a partir de um arquivo .csv
			if (matCfg.modo != 4) 
			{
				selecao_Menu_Figura(&matCfg, matCfg);
			}
			perguntaCustomizarInicializacao(&resposta);
			
			if(resposta == 1) // Usuário deseja customizar jogo
			{
				perguntaMudarCaracter(&matCfg);
				perguntaTamanhoTabela(&matCfg);
				perguntaInicioLocalizacao(&matCfg, matCfg);
				perguntaNumeroGeracoes(&matCfg);
			}
			// Caso o usuário não deseje customizar onde a figura será colocada, ela será colocada no meio da tabela
			else
			{
				matCfg.locX = matCfg.linhas / 2;
				matCfg.locY = matCfg.colunas / 2;
			}
			perguntaInserirInvasor(&respostaInserir);
			// Usuário deseja inserir invasor
			if(respostaInserir == 1)
			{
				selecao_Menu_Modo_Invasor(&matCfg);
        		if (matCfg.modoInv != 4) 
				{
					selecao_Menu_Figura_Invasor(&matCfg, matCfg);
        		}
				perguntaCustomizarInicializacaoInvasor(&respostaInv);
				if(respostaInv == 1)
				{
					perguntaInicioLocalizacaoInvasor(&matCfg, matCfg);
					perguntaInicioGeracaoInvasor(&matCfg, matCfg);
				}
				else
				{
					matCfg.locX = matCfg.linhas/4 +1;
					matCfg.locY = matCfg.colunas/4 +1;
					matCfg.locXInv = (matCfg.linhas*3/4 -2);
					matCfg.locYInv = (matCfg.colunas*3/4 -2);
					matCfg.inicioInv = 1;
				}
			}
	    	telaCarregamento(); // Tela carregamento, iniciando a simulação
		}
		simulaGeracoes(matCfg);
		sleep(2);
		telaReinicio();
	}
	system(LIMPA);
	return 0;
}