/** 
  * 	Quando se trata da definição de Stacks e Queues não importa realmente a maneira
  * como estas estrutras estão armazenadas na memória, mas sim o interfaceamento usado.
  * 	É por isso que o protótipo abaixo cria um novo tipo (numStack) que é na verdade um
  * ponteiro duplo para uma strutura (struct s_numStack**). Essa caracteristica pode parecer meio
  * estranha a principio, mas acredito que é um jeito interessante de interfacear o código.
  * 	Esse design "esconde" acesso dos elementos da estrutura do usuario final (o que
  * costuma ser considerado uma boa prática), dando acesso apenas à push(), pop(), peek()
  *	e isEmpty() pra controle, além da macro novaStack pra inicializar as pilhas com 0.
  * 	A ideia original era usar uma static global aqui pra dizer onde o topo da stack está
  * e só deixar o usuario acessar esse topo. O problema é que ai eu só teria uma variavel topo
  * ou teria que ter uma array e interfacear cada uma. O método que eu usei aqui tem o mesmo
  * resultado final, mas permitindo o uso de pilhas individuas declaradas com struct s_numStack *.
  *		Pode não ser a melhor implementação, mas eu gostei assim.
  *
  *		GUSTAVO GODOY.
  **/
  
#ifndef STACKS_H /* Proteção de Header que impede de rodar o código duas vezes */
#define STACKS_H /* quando multiplos arquivos chamam esse header */
/** Pré-compilador */
#include <stdio.h>
#include <stdlib.h>

/** Declaração de estruturas, funções, variaveis globais, etc **/
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
