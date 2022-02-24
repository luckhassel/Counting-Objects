/*
This program basically analyze pixels of an image in the format PPM and then it will return
how many object are in the image. It's strongly linked to the test images, but that was the purpose.
Uses a lot concepts like memory, file reading, queues and stacks.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lib/stacks.h"
#include "lib/ppm.h"

//Declaring functions and structures
void macro(tBitmap area, long ***visitado, numStack Y, numStack X, long y, long x);

//Main function
int main(int argc, char *argv[])
{
	//Initialization
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
	
	contagem=0;
	explorado[0][0]=0;

	do
	{
		//Select the right place and mark it as explored
		for(y=0; y<mapa.altura; ++y)
			for(x=0; x<mapa.largura; ++x)
				if (explorado[y][x]==-1)
				{
					explorado[y][x]=0;
					if(!mesmoPixel(mapa.matriz[y][x], mapa.matriz[0][0]))
						goto sai_do_loop; //One of a fill good example of using goto (when necessary)
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
				
				//Add pixels that are around the one to the stack
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
	
	//Finish
	
	#ifdef IMPRIME
	//If use flag "--imprime", it will call it
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

//To save some space
void macro(tBitmap area, long ***visitado, numStack Y, numStack X, long y, long x)
{
	if(!mesmoPixel(area.matriz[y][x], area.matriz[0][0]) && ((*visitado)[y][x] == 0 || (*visitado)[y][x]==-1))
	{
		push(Y, y);
		push(X, x);
	}else if(mesmoPixel(area.matriz[y][x],area.matriz[0][0]))
		(*visitado)[y][x]=0;
		
}
