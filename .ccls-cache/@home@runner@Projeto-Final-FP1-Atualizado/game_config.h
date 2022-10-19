#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "evolui_geracoes.h"
#include "desenho_figuras_demo.h"
#ifdef _WIN32
    #include <Windows.h>
    #define LIMPA "cls"
#else
    #include <unistd.h>
    #define LIMPA "clear"
#endif

void titulo_Menu(void)
{
	printf("*********************************************\n");
	printf("                 JOGO DA VIDA\n");
	printf("*********************************************\n\n\n\n");
	return;
}

void titulo_Menu_Modo_Opcao(int inicio)
{
	printf("1) Vida Eterna.\n\n");
	printf("2) Osciladores.\n\n");
	printf("3) Naves Espaciais.\n\n");
	printf("4) Ler matriz a partir de um arquivo.\n\n");
	if(inicio==1)
	{
		printf("5) Descrição dos modos de jogo.\n\n");
		printf("6) Regras do jogo.\n\n");
		printf("7) Sair do jogo.\n\n");
	}
	return;
}

void titulo_Menu_Opcoes(int pergunta, int descricao)
{
	if (pergunta == 0)
	{
		if (descricao == 0)

    	printf("Modos:\n");
    	if (descricao == 1)
    	printf("Figuras:\n");
	    if (descricao == 2)
		{
	    	printf("Opções de jogo:\n");
	    	printf("Digite 'S' para sim ou 'N' para não.\n");
	    }
		printf("---------------------------------------------\n\n");
	}
	else
	{
	    printf("Opções de jogo:\n");
	    if (descricao == 0)
	      printf("Digite um único caracter do teclado.\n");
	    if (descricao == 1)
	      printf("Digite o tamanho da tabela, considerando o tamanho mínimo de 15x15.\n");
	    if (descricao == 2)
	      printf("Digite as coordernadas da tabela em X e Y, sendo as coordenadas positivas.\n");
	    if (descricao == 3)
	    	printf("Digite o número de gerações, sabendo tem que ser positivo.\n");
	   	printf("---///---///---///---///---///---///---///---\n\n");
	}
	return;
}

void aviso_Erro(int tipoErro)
{
	system(LIMPA);
	titulo_Menu();
	if (tipoErro == 1)
	{
    	titulo_Menu_Opcoes(0, 0);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar presente no menu de seleção!\n");
	}
	else if (tipoErro == 2)
	{
    	titulo_Menu_Opcoes(0, 1);
    	printf("Digite a letra novamente!!!\n"
			"A letra precisa estar presente no menu de seleção!\n");
	}
	else if (tipoErro == 3)
	{
    	titulo_Menu_Opcoes(0, 2);
    	printf("Digite a letra novamente!!!\n"
			"A letra precisa ser 'S' para sim ou 'N' para não!\n");
	}
	else if (tipoErro == 4)
	{
    	titulo_Menu_Opcoes(1, 1);
    	printf("Digite o tamanho novamente!!!\n"
			"O tamanho precisa estar entre os requisitos!\n");
	}
	else if (tipoErro == 5)
	{
    	titulo_Menu_Opcoes(1, 2);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar entre os requisitos!\n");
	}
	else if (tipoErro == 6)
	{
    	titulo_Menu_Opcoes(1, 3);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar entre os requisitos!\n");
	}
  sleep(3);
  system(LIMPA);
  return;
}

void ler_string(char *resposta)
{
	int tamanho;
    char letra, *string;
	string = (char*) malloc (2*sizeof(char));
    
	scanf(" %c", &letra);

    for (tamanho = 0; letra != '\n'; tamanho++)
    {
        string[tamanho] = letra;
        string = (char*) realloc(string, (tamanho+3)*sizeof(char));

        scanf("%c", &letra);
    }
    string[tamanho+1] = '\0';
	*resposta = string[0];
	free(string);
}

void selecao_Menu_Modo(MatrizConfig *matCfg)
{
	char escolha;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 0);
	    titulo_Menu_Modo_Opcao(1);
	    printf("Escolha o modo de jogo: ");
		ler_string (&escolha);
	    matCfg->modo = escolha - '0';
	    if (matCfg->modo < 1 || matCfg->modo > 7)
	    	aviso_Erro(1);
	}
	while (matCfg->modo < 1 || matCfg->modo > 7);
	system(LIMPA);
	return;
}

void selecao_Menu_Figura(MatrizConfig *matCfg, MatrizConfig matc)
{
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 1);
	    titulo_Menu_Figura_Opcao(matc.modo);
	    printf("Escolha a figura inicial para o jogo: ");
	    ler_string(&matCfg->figura);
		if (matCfg->figura >= 'a' && matCfg->figura <= 'c')
	    		matCfg->figura -= 32;
	    if (matCfg->figura < 'A' || matCfg->figura > 'C')
	    	aviso_Erro(2);
		if(matc.modo==2 || matc.modo==3)
		{
			if (matCfg->figura == 'C')
			{
				matCfg->figura = '@';
				aviso_Erro(2);
			}
		}
	}
	while (matCfg->figura < 'A' || matCfg->figura > 'C');
	system(LIMPA);
	return;
}

void selecao_Menu_Modo_Invasor(MatrizConfig *matCfg)
{
	char escolha;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 0);
	    titulo_Menu_Modo_Opcao(0);
	    printf("Escolha a figura do invasor: ");
	    ler_string (&escolha);
		matCfg->modoInv = escolha - '0';
	    if (matCfg->modoInv < 1 || matCfg->modoInv > 4)
	      aviso_Erro(1);
	}
	while (matCfg->modoInv < 1 || matCfg->modoInv > 4);
	system(LIMPA);
	return;
}

void selecao_Menu_Figura_Invasor(MatrizConfig *matCfg, MatrizConfig matc)
{
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 1);
	    titulo_Menu_Figura_Opcao(matc.modoInv);
	    printf("Escolha a figura inicial para o jogo: ");
	    ler_string(&matCfg->figuraInv);
		if (matCfg->figuraInv >= 'a' && matCfg->figuraInv <= 'c')
	    		matCfg->figuraInv -= 32;
	    if (matCfg->figuraInv < 'A' || matCfg->figuraInv > 'C')
	    	aviso_Erro(2);
		if(matc.modoInv==2 || matc.modoInv==3)
		{
			if (matCfg->figuraInv == 'C')
			{
				matCfg->figuraInv = '@';
				aviso_Erro(2);
			}
		}
	}
	while (matCfg->figuraInv < 'A' || matCfg->figuraInv > 'C');
	system(LIMPA);
	return;
}

void perguntaCustomizarInicializacao(int *resposta)
{
	char resposta_Customizar;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja customizar algo no jogo? ");
	    ler_string(&resposta_Customizar);
	    if (resposta_Customizar == 's' || resposta_Customizar == 'n')
	    	resposta_Customizar -= 32;
	    if (resposta_Customizar != 'S' && resposta_Customizar != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Customizar != 'S' && resposta_Customizar != 'N');
	if (resposta_Customizar == 'S') 
		*resposta=1;
	system(LIMPA);
	return;
}

void perguntaMudarCaracter(MatrizConfig *matCfg)
{
	char resposta_Mudar_Caracter;
	system(LIMPA);
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja mudar os caracteres da tabela padrão (0 e .)? ");
	    ler_string(&resposta_Mudar_Caracter);
	    if (resposta_Mudar_Caracter == 's' || resposta_Mudar_Caracter == 'n')
	    	resposta_Mudar_Caracter -= 32;
	    if (resposta_Mudar_Caracter != 'S' && resposta_Mudar_Caracter != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Mudar_Caracter != 'S' && resposta_Mudar_Caracter != 'N');
	
	if (resposta_Mudar_Caracter == 'S')
	{
	    system(LIMPA);
	    titulo_Menu();
	    titulo_Menu_Opcoes(1, 0);
	    printf("\nEscolha o caracter para as células mortas: ");
	    ler_string(&matCfg->morto);
	    printf("\n\nEscolha o caracter para as células vivas: ");
	    ler_string(&matCfg->vivo);
	}
	system(LIMPA);
	return;
}

void perguntaTamanhoTabela(MatrizConfig *matCfg)
{
	char resposta_Tamanho;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja mudar o tamanho da tabela padrão? ");
	    ler_string(&resposta_Tamanho);
	    if (resposta_Tamanho == 's' || resposta_Tamanho == 'n')
	    	resposta_Tamanho -= 32;
	    if (resposta_Tamanho != 'S' && resposta_Tamanho != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Tamanho != 'S' && resposta_Tamanho != 'N');
	
	if (resposta_Tamanho == 'S')
	{
	    system(LIMPA);
		do
		{
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1, 1);
	    	printf("Escolha o comprimento da linha e da coluna (O mínimo é 15x15): ");
	    	scanf("%d %d", &matCfg->linhas, &matCfg->colunas);
	    	if (matCfg->linhas < 15 || matCfg->colunas < 15)
	        	aviso_Erro(4);
	    }
		while (matCfg->linhas < 15 || matCfg->colunas < 15);
	}
	system(LIMPA);
	return;
}

void perguntaInicioLocalizacao(MatrizConfig *matCfg, MatrizConfig matc)
{
	char resposta_Localizacao;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja escolher o local inicial da figura? ");
	    ler_string(&resposta_Localizacao);
	    if (resposta_Localizacao == 's' || resposta_Localizacao == 'n')
	    	resposta_Localizacao -= 32;
	    if (resposta_Localizacao != 'S' && resposta_Localizacao != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Localizacao != 'S' && resposta_Localizacao != 'N');
	
	if (resposta_Localizacao == 'S')
	{
	    system(LIMPA);
	    do
		{
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1, 2);
	    	printf("Escolha a localização X Y (O mínimo é 1x1 e"
			" o máximo é %dx%d): ", matc.linhas, matc.colunas);
	    	scanf("%d %d", &matCfg->locX, &matCfg->locY);
	    	if ((matCfg->locX < 1 || matCfg->locX > matc.linhas) ||
			(matCfg->locY < 1 || matCfg->locY > matc.colunas))
	        	aviso_Erro(5);
		}
		while ((matCfg->locX < 1 || matCfg->locX > matc.linhas) ||
		(matCfg->locX < 1 || matCfg->locX > matc.colunas));
	}
	
	// Caso o usuário não deseje customizar onde a figura será colocada, ela será colocada em uma posição aleatória
	else
	{
		matCfg->locX = matc.linhas / 2;
		matCfg->locY = matc.colunas / 2;
	}
	system(LIMPA);
	return;
}

void perguntaNumeroGeracoes(MatrizConfig *matCfg)
{
	char resposta_Geracoes;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja escolher o número de gerações que serão rodadas? ");
		ler_string(&resposta_Geracoes);
	    if (resposta_Geracoes == 's' || resposta_Geracoes == 'n')
	    	resposta_Geracoes -= 32;
	    if (resposta_Geracoes != 'S' && resposta_Geracoes != 'N')
	    	aviso_Erro(3);
		system(LIMPA);
	}
	while (resposta_Geracoes != 'S' && resposta_Geracoes != 'N');
	
	if (resposta_Geracoes == 'S')
	{
		do
		{
			titulo_Menu();
			titulo_Menu_Opcoes(1, 3);
			printf("Digite o número de gerações que serão rodados (O mínimo é 1): ");
			scanf("%d", &matCfg->numGeracoes);
			if (matCfg->numGeracoes < 1)
		    	aviso_Erro(6);
		}
		while (matCfg->numGeracoes < 1);
		system(LIMPA);
	}
	return;
}

void perguntaInserirInvasor(int *respostaInserir)
{
	char resposta_Invasor;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja adicionar um invasor na tabela? ");
	    ler_string(&resposta_Invasor);
	    if (resposta_Invasor == 's' || resposta_Invasor == 'n')
	    	resposta_Invasor -= 32;
	    if (resposta_Invasor != 'S' && resposta_Invasor != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Invasor != 'S' && resposta_Invasor != 'N');
	
	if (resposta_Invasor == 'S')
		*respostaInserir = 1;
	system(LIMPA);
	return;
}

void perguntaCustomizarInicializacaoInvasor(int *respostaInv)
{
	char resposta_Customizar;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja customizar algo no jogo? ");
	    ler_string(&resposta_Customizar);
	    if (resposta_Customizar == 's' || resposta_Customizar == 'n')
	    	resposta_Customizar -= 32;
	    if (resposta_Customizar != 'S' && resposta_Customizar != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Customizar != 'S' && resposta_Customizar != 'N');
	
	if (resposta_Customizar == 'S')
		*respostaInv=1;
	system(LIMPA);
	return;
}

void perguntaInicioLocalizacaoInvasor(MatrizConfig *matCfg, MatrizConfig matc)
{
	char resposta_Localizacao;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja escolher o local inicial da figura? ");
	    ler_string(&resposta_Localizacao);
	    if (resposta_Localizacao == 's' || resposta_Localizacao == 'n')
	    	resposta_Localizacao -= 32;
	    if (resposta_Localizacao != 'S' && resposta_Localizacao != 'N')
	    	aviso_Erro(3);
	}
	while (resposta_Localizacao != 'S' && resposta_Localizacao != 'N');
	
	if (resposta_Localizacao == 'S')
	{
	    system(LIMPA);
	    do
		{
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1, 2);
	    	printf("Escolha a localização X Y (O mínimo é 1x1 e"
			" o máximo é %dx%d): ", matc.linhas, matc.colunas);
	    	scanf("%d %d", &matCfg->locXInv, &matCfg->locYInv);
	    	if ((matCfg->locXInv < 1 || matCfg->locXInv > matc.linhas) ||
			(matCfg->locYInv < 1 || matCfg->locYInv > matc.colunas))
	        	aviso_Erro(5);
		}
		while ((matCfg->locXInv < 1 || matCfg->locXInv > matc.linhas) ||
		(matCfg->locYInv < 1 || matCfg->locYInv > matc.colunas));
	}
	else
	{
		matCfg->locXInv = matc.linhas/2 - 4;
		matCfg->locYInv = matc.colunas/2 - 4;
	}
	system(LIMPA);
	return;
}

void perguntaInicioGeracaoInvasor(MatrizConfig *matCfg, MatrizConfig matc)
{
	char resposta_Invasor;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja inserir um momento específico para adicionar\n"
		"o invasor na tabela? ");
	    ler_string(&resposta_Invasor);
	    if (resposta_Invasor == 's' || resposta_Invasor == 'n')
	      resposta_Invasor -= 32;
	    if (resposta_Invasor != 'S' && resposta_Invasor != 'N')
	      aviso_Erro(3);
	}
	while (resposta_Invasor != 'S' && resposta_Invasor != 'N');

	if (resposta_Invasor == 'S')
	{
	    system(LIMPA);
	    do
		{
		    titulo_Menu();
	    	titulo_Menu_Opcoes(1, 3);
	    	printf("Digite o número de gerações para aparecer\n"
			"o invasor (O mínimo é 1 e o máximo é %d): ", matc.numGeracoes);
	    	scanf("%d", &matCfg->inicioInv);
	    	if (matCfg->inicioInv < 1 || matCfg->inicioInv > matc.numGeracoes)
		   		aviso_Erro(6);
	    }
		while (matCfg->inicioInv < 1 || matCfg->inicioInv > matc.numGeracoes);
	}
	system(LIMPA);
	return;
}

void telaCarregamento(void)
{
	system(LIMPA);
	titulo_Menu();
	printf("Preparando jogo\nCarregando.\n");
	usleep(500*1000);
	system(LIMPA);
	
	titulo_Menu();
	printf("Preparando jogo\nCarregando..\n");
	usleep(500*1000);
	system(LIMPA);
	    
	titulo_Menu();
	printf("Preparando jogo\nCarregando...\n");
	usleep(500*1000);
	system(LIMPA);
}

void telaReinicio(void)
{
	system(LIMPA);
	titulo_Menu();
	printf("Reiniciando.\n");
	usleep(500*1000);
	system(LIMPA);
	  
	titulo_Menu();
	printf("Reiniciando..\n");
	usleep(500*1000);
	system(LIMPA);
	    
	titulo_Menu();
	printf("Reiniciando...\n");
	usleep(500*1000);
	system(LIMPA);
}

void descricaoModos(void)
{
	char continuar;
	titulo_Menu();
	printf("Descrição dos modos de jogo:\n");
	printf("---------------------------------------------\n\n");
	printf("1°) Vida Eterna - Formações que não se alteram\n"
		   "em gerações subsequentes a não ser que sejam\n"
		   "perturbadas por outras células.\n\n");
	printf("2°) Osciladores - Formações periódicas com\n"
		   "comportamento previsível.\n\n");
	printf("3°) Naves Espaciais - Formações que deslizam\n"
		   "uma posição na diagonal a cada nova geração.\n\n");
	printf("4°) Ler arquivo - O programa lê o arquivo\n"
		   "desenho.csv e cria uma formação com base nos\n"
		   "números digitados nele.\n\n");
	printf("Digite qualquer tecla para continuar:\n");
	ler_string(&continuar);
	return;
}

void descricaoRegras(void)
{
	char continuar;
	titulo_Menu();
	printf("Regras de jogo:\n");
	printf("---------------------------------------------\n\n");
	printf("1° - Qualquer célula viva com menos de dois\n"
		   "vizinhos vivos morre de solidão.\n\n");
	printf("2° - Qualquer célula viva com mais de três\n"
		   "vizinhos vivos morre de superpopulação.\n\n");
	printf("3° - Qualquer célula com exatamente três\n"
		   "vizinhos vivos se torna uma célula viva.\n\n");
	printf("4° - Qualquer célula com dois vizinhos vivos\n"
		   "continua no mesmo estado para a próxima geração.\n\n");
	printf("Células vivas: %c\nCélulas mortas: %c\n\n\n", VIVO, MORTO);
	desenhoExemplo();
	printf("Digite qualquer tecla para continuar:\n");
	ler_string(&continuar);
	return;
}

void fim_de_Jogo(void)
{
	printf("*********************************************\n");
	printf("                  FIM DE JOGO\n");
	printf("*********************************************\n");
	sleep(3);
	return;
}