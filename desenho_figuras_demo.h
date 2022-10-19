#include <stdio.h>
#include <stdlib.h>

#define MORTO '.'
#define VIVO '0'

void titulo_Menu_Figura_Opcao(int modo) 
{
	if (modo==1)
	{
		printf("A) Bloco.\n\n");
    	printf("%c %c\n%c %c\n\n\n", VIVO, VIVO, VIVO, VIVO);
		printf("B) Bote.\n\n");
    	printf("%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n\n\n", MORTO, VIVO, VIVO, MORTO, VIVO, MORTO, MORTO, VIVO, MORTO, VIVO, VIVO, MORTO);
		printf("C) Comilão.\n\n");
    	printf("%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n\n\n", VIVO, VIVO, MORTO, 
		MORTO, VIVO, MORTO, MORTO, MORTO, MORTO, VIVO, VIVO, VIVO, MORTO, MORTO, MORTO, VIVO);
	}
	else if (modo==2)
	{
		printf("A) Blinker.\n\n");
    	printf("%c %c %c\n\n\n", VIVO, VIVO, VIVO);
		printf("B) Sapo.\n\n");
    	printf("%c %c %c %c\n%c %c %c %c\n\n\n", MORTO, VIVO, VIVO, VIVO, VIVO, VIVO, VIVO, 
		MORTO);
	}
	else
	{
		printf("A) Glider.\n\n");
    	printf("%c %c %c\n%c %c %c\n%c %c %c\n\n\n", VIVO, VIVO, VIVO, VIVO, MORTO, MORTO, MORTO,
		VIVO, MORTO);
		printf("B) LWSS.\n\n");
    	printf("%c %c %c %c %c\n%c %c %c %c %c\n%c %c %c %c %c\n%c %c %c %c %c\n\n\n", MORTO, VIVO, 
		MORTO, MORTO, VIVO, VIVO, MORTO, MORTO, MORTO, MORTO, VIVO, MORTO, MORTO, MORTO, VIVO, VIVO,
		VIVO, VIVO, VIVO, MORTO);
	}
	return;
}



void desenhoExemplo(void) 
{
	printf("%c %c %c %c %c		%c %c %c %c %c\n%c %c %c %c %c		%c %c "
	"%c %c %c\n", MORTO,MORTO, MORTO, MORTO, VIVO, MORTO, MORTO, VIVO, VIVO, 
	MORTO, MORTO, VIVO, VIVO, VIVO, MORTO, MORTO, VIVO, MORTO, VIVO, VIVO);
	printf("%c %c %c %c %c  -->  %c %c %c %c %c\n", MORTO, VIVO, MORTO, VIVO,
	MORTO, VIVO, VIVO, MORTO, VIVO, VIVO);
	printf("%c %c %c %c %c		%c %c %c %c %c\n%c %c %c %c %c		%c %c "
	"%c %c %c\n\n", VIVO, MORTO, MORTO, VIVO, MORTO, MORTO, MORTO, MORTO, 
	VIVO, MORTO, MORTO, MORTO, VIVO, MORTO, MORTO, MORTO, MORTO, MORTO, 
	MORTO, MORTO);
}