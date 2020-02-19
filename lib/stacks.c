/** Instruções pro Compilador **/
#include <stdio.h>
#include "stacks.h"

/** Definição das Funções de Stack **/

struct s_numStack ** newStack(void)
{
	return calloc(1, sizeof(struct s_numStack *));
}

/* Empurra um valor na Stack */
void push(struct s_numStack **topo, long valor)
{
	struct s_numStack * novoTopo;
	novoTopo=malloc(sizeof *novoTopo);
	if (!novoTopo)
	{
		fprintf(stderr, "ERRO: falha de malloc() ao executar a operação PUSH.\n");
		return;
	}
	novoTopo->elemento=valor;
	novoTopo->proximo=*topo;
	if(topo)
		novoTopo->proximo=*topo;
	else
		novoTopo->proximo=NULL;
	
	*topo=novoTopo;
}

/* Puxa um valor da Stack. */
long pop(struct s_numStack **pilha)
{
	struct s_numStack * topo;
	long devolver;
	
	if (isEmpty(pilha))
	{
		fprintf(stderr, "ERRO: tentativa de executar POP em uma pilha vazia.\n");
		return 0;
	}
	
	topo=*pilha;
	devolver=(*pilha)->elemento;
	
	*pilha=(*pilha)->proximo;
	free(topo);
	return devolver;
}

/* Retorna o elemento do topo da pilha sem tirar ele do lugar. */
long peek(struct s_numStack **pilha)
{
	return (*pilha)->elemento;
}

/* Checa se uma pilha está vazia */
int isEmpty(struct s_numStack **pilha)
{
	if (*pilha==NULL)
		return 1;
	else
		return 0;
}


