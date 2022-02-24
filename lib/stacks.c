#include <stdio.h>
#include "stacks.h"

//Definition of the struct
struct s_numStack ** newStack(void)
{
	return calloc(1, sizeof(struct s_numStack *));
}

//Push a value to the stack
void push(struct s_numStack **topo, long valor)
{
	struct s_numStack * novoTopo;
	novoTopo=malloc(sizeof *novoTopo);
	if (!novoTopo)
	{
		fprintf(stderr, "ERRO: falha de malloc() ao executar a opera��o PUSH.\n");
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

//Pull a value from the stack
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

//Return the first element of the struct
long peek(struct s_numStack **pilha)
{
	return (*pilha)->elemento;
}

//Check if stack is empty
int isEmpty(struct s_numStack **pilha)
{
	if (*pilha==NULL)
		return 1;
	else
		return 0;
}


