/**
  *	Suporte para trabalhar com imagens do tipo PPM (especificamente o padrão P6):
  *	Define o tipo tPixel que armazena um trio de inteiros RGB e o tipo tBitmap que cria uma matriz bidimensional de tPixels e armazena informação de largura e altura.
  *	Define a função arquivo_pra_bitmap que carrega um arquivo do disco para a memória como um tBitmap.
  *	Define outras funções auxiliares também.
 **/
 
#ifndef PPM_H /* Proteção de Header que impede de rodar o código duas vezes */
#define PPM_H /* quando multiplos arquivos chamam esse header */
/** Instruções para o compilador **/
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "stacks.h"

/** Declaração de estruturas, funções, etc **/
typedef struct sPixel
{
	int r; /* "Red" - Vermelho */ 
	int g; /* "Green" - Verde */
	int b; /* "Blue" - Azul*/
} tPixel;

typedef struct sBitmap
{
	long largura;
	long altura;
	tPixel ** matriz;
} tBitmap;

int mesmoPixel(tPixel A, tPixel B);
void arquivo_pra_bitmap(char diretorio[], tBitmap *area); /** IMPORTANTE! matriz é carregada como matriz[altura][largura]!!! **/

#endif
