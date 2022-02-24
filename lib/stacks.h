/*
Creates an element called (numStack) that is actually a pointer to a pointer.
But, the main advantage of it is to hide the implementation from the user.
*/
  
#ifndef STACKS_H 
#define STACKS_H

#include <stdio.h>
#include <stdlib.h>

struct s_numStack
{
	long elemento;
	struct s_numStack *proximo;
};

typedef struct s_numStack ** numStack;

void push(struct s_numStack **pilha, long valor);
long pop(struct s_numStack **pilha);
long peek(struct s_numStack **pilha);
int isEmpty(struct s_numStack **pilha);
struct s_numStack ** newStack(void);
#endif
