typedef struct 
{
	int modo, modoInv; // Modo da figura principal e invasora
	char figura, figuraInv; // Forma da figura principal
	int locX, locY, locXInv, locYInv; // Localização da figura
	int linhas, colunas; // Tamanho da matriz
	int numGeracoes; // Numero de gerações que serão simuladas
	int inicioInv; // Quando a célula invasora irá surgir
	char vivo, morto;
	char **matriz;
	char **matrizCopia;
}
MatrizConfig;