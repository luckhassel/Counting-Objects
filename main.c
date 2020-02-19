/** Instruções para o compilador **/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lib/stacks.h"
#include "lib/ppm.h"

/** Declaração de estruturas, funções, etc **/
void macro(tBitmap area, long ***visitado, numStack Y, numStack X, long y, long x);

/** Main **/
int main(int argc, char *argv[])
{
	/* Inicialização */
	long x,y, contagem, **explorado;
	numStack pilha_x=newStack(), pilha_y=newStack();
	tBitmap mapa;
	
	setlocale(LC_ALL, "");
	if (argc < 2)
	{	
		printf("Por favor, inicialize o programa usando \"%s nome_do_arquivo.ppm\".\n", argv[0]);
		exit(1);
	}

	arquivo_pra_bitmap(argv[1], &mapa);
	
	explorado = malloc(mapa.altura*sizeof*explorado);
	for(y=0; y<mapa.altura; y++)
		explorado[y]=malloc(mapa.largura*sizeof**explorado);
	
	for(y=0; y<mapa.altura; ++y)
		for(x=0; x<mapa.largura; ++x)
			explorado[y][x]=-1;
	
	/* Meio */
	contagem=0;
	explorado[0][0]=0;

	do
	{
		/* 1. Seleciona o lugar certo pra começar e marca como explorado */
		for(y=0; y<mapa.altura; ++y)
			for(x=0; x<mapa.largura; ++x)
				if (explorado[y][x]==-1)
				{
					explorado[y][x]=0;
					if(!mesmoPixel(mapa.matriz[y][x], mapa.matriz[0][0]))
						goto sai_do_loop; /* Uma das poucas aplicações legitimas de GOTO. Outras: http://stackoverflow.com/questions/245742/examples-of-good-gotos-in-c-or-c */
				}
		sai_do_loop:
		
		if(y<mapa.altura && x<mapa.largura)
		{
			++contagem;
			push(pilha_x, x);
			push(pilha_y, y);
		
			while(!isEmpty(pilha_x)&&!isEmpty(pilha_y))
			{
				x = pop(pilha_x);
				y = pop(pilha_y);
				explorado[y][x]=contagem;
				
				/* Adiciona pixels adjacentes as Stacks. Do jeito bruto. */
				if(y==0)
				{
					if (x==0)
					{
						macro(mapa, &explorado, pilha_y,pilha_x,0,1);
						macro(mapa, &explorado, pilha_y,pilha_x,1,0);
					}
					else if(x==mapa.largura-1)
					{
						macro(mapa, &explorado, pilha_y,pilha_x,0,mapa.largura-2);
						macro(mapa, &explorado, pilha_y,pilha_x,1,mapa.largura-1);
					}
					else
					{
						macro(mapa, &explorado, pilha_y,pilha_x,0,x-1);
						macro(mapa, &explorado, pilha_y,pilha_x,0,x+1);
						macro(mapa, &explorado, pilha_y,pilha_x,1,x);
					}
				}
				else if(y==mapa.altura-1)
				{
					if (x==0)
					{
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-2,0);
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-1,1);
					}
					else if(x==mapa.largura-1)
					{
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-1,mapa.largura-2);
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-2,mapa.largura-1);
					}
					else
					{
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-1,x-1);
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-1,x+1);
						macro(mapa, &explorado, pilha_y,pilha_x,mapa.altura-2,x);
					}
				}
				else
				{
					if (x==0)
					{
						macro(mapa, &explorado, pilha_y,pilha_x,y-1,0);
						macro(mapa, &explorado, pilha_y,pilha_x,y+1,0);
						macro(mapa, &explorado, pilha_y,pilha_x,y,1);
					}
					else if(x==mapa.largura-1)
					{
						macro(mapa, &explorado, pilha_y,pilha_x,y-1,mapa.largura-1);
						macro(mapa, &explorado, pilha_y,pilha_x,y+1,mapa.largura-1);
						macro(mapa, &explorado, pilha_y,pilha_x,y,mapa.largura-2);
					}
					else
					{
						macro(mapa, &explorado, pilha_y,pilha_x,y-1,x);
						macro(mapa, &explorado, pilha_y,pilha_x,y,x+1);
						macro(mapa, &explorado, pilha_y,pilha_x,y+1,x);
						macro(mapa, &explorado, pilha_y,pilha_x,y,x-1);
					}
				}
			}
		}
	}while(y<mapa.altura && x<mapa.largura);
	
	/* Termina */
	
	#ifdef IMPRIME
	/* Usar a flag "-D IMPRIME" no GCC para incluir essa parte. */
	long display_y, display_x;
	for(display_y=0; display_y<mapa.altura; ++display_y)
	{
		for(display_x=0; display_x<mapa.largura; ++display_x)
			if(explorado[display_y][display_x])
				printf("%ld",explorado[display_y][display_x]);
			else
				printf(" ");
		printf("\n");
	}
	#endif
	
	printf("Contagem: %ld\n", contagem);
	return 0; 
}

/* Pra economizar espaço. */
void macro(tBitmap area, long ***visitado, numStack Y, numStack X, long y, long x)
{
	if(!mesmoPixel(area.matriz[y][x], area.matriz[0][0]) && ((*visitado)[y][x] == 0 || (*visitado)[y][x]==-1))
	{
		push(Y, y);
		push(X, x);
	}else if(mesmoPixel(area.matriz[y][x],area.matriz[0][0]))
		(*visitado)[y][x]=0;
		
}
