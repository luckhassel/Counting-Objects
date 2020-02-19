/** Pré Compilador **/
#include <stdio.h>
#include <string.h>
#include "ppm.h"

/** Definição das funções de PPM **/

/** Definição de funções **/
/** Acessa um arquivo salvo e carrega na memória como um tBitmap **/
void arquivo_pra_bitmap(char diretorio[], tBitmap *area)
{
	/* Inicializa */
	char *buffer, *token /*, *a, *b */;
	long i,j, N;
	FILE * arquivo;
	
	/* Carrega o arquivo como um Buffer */
	arquivo = fopen(diretorio, "rb");
	if (arquivo == NULL)
	{
		printf("Erro: O arquivo \"%s\" não pode ser encontrado.\n", diretorio);
		exit(1);
	}
	
	fseek(arquivo, 0, SEEK_END);
	N = ftell(arquivo);
	fseek(arquivo, 0, SEEK_SET);
	buffer = malloc((N+1)*sizeof(char));
	if(buffer==NULL)
	{
		printf("Erro: o sistema não tem mais espaço disponivel.\n");
		exit(1);
	}
	
	fread(buffer, N, 1, arquivo);
	buffer[N]='\0';
	fclose(arquivo);
	
	
	
	/* Le o cabeçalho e testa as informações */
	token = strtok(buffer, " \t\n\r\v\f");
	
	if(strcmp(token, "P6"))
	{
		printf("Erro: O arquivo não está no formato PPM.\n");
		exit(1);
	}
	
	token=strtok(NULL, " \t\n\r\v\f");
	area->largura=atoi(token);
	token=strtok(NULL, " \t\n\r\v\f");
	area->altura=atoi(token);
	
	token=strtok(NULL, " \t\n\r\v\f"); /* O exercicio especifica que aqui o valor sempre será 255 */
	
	while(*token++!='\0') /* STRTOK pode ter dificuldades em pegar o resto do código, que pode incluir \0's por ser binario, por isso uso essa linha aqui */
		;
	
	/* Carrega os valores na matriz */
	area->matriz=malloc(area->altura*sizeof(*area->matriz));
	if (area->matriz==NULL)
	{
		printf("Erro: Não há mais memória disponivel.\n");
		exit(1);
	}
	for(i=0; i<area->altura; ++i)
	{
		area->matriz[i]=malloc(area->largura*sizeof(**area->matriz));
		if (area->matriz[i]==NULL)
		{
			printf("Erro: Não há mais memória disponivel.\n");
			exit(1);
		}
	}
	
	for(i=0; i<area->altura; ++i)
		for(j=0; j<area->largura; ++j)
		{
			area->matriz[i][j].r=*token++;
			area->matriz[i][j].g=*token++;
			area->matriz[i][j].b=*token++;
		}
	
	free(buffer);
}


/* Compara dois tPixels */
int mesmoPixel(tPixel A, tPixel B)
{
	if(A.r==B.r && A.g == B.g && A.b == B.b)
		return 1;
	return 0;
}
