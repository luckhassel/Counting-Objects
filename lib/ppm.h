/*
Helper to work with PPM images. It has a type tPixel that stores RGB values and also some other functions
that check memory status, and auxiliar ones.
*/
 
#ifndef PPM_H 
#define PPM_H 

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "stacks.h"

typedef struct sPixel
{
	int r; /* "Red" */ 
	int g; /* "Green" */
	int b; /* "Blue" */
} tPixel;

typedef struct sBitmap
{
	long largura;
	long altura;
	tPixel ** matriz;
} tBitmap;

int mesmoPixel(tPixel A, tPixel B);
void arquivo_pra_bitmap(char diretorio[], tBitmap *area);

#endif
