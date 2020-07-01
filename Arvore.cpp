#include <stdlib.h>
#include <stdio.h>

// Estrutura do node
typedef struct tree_node
{
	struct tree_node *parent;
	struct tree_node *left_child;
	struct tree_node *right_child;
	int key;
} node;

int main(int argc, char *argv[])
{
	// Funções declaradas	
	node *busca (node *raiz, int key);
	node *inserir (node *raiz, int key);
	node *minimo (node *raiz);
	node *maximo (node *raiz);
	void imprimir (node *raiz);
	void deletar (node *raiz, int key);

	// Inicializa arvore com NULL
	node *root, *aux;
	root = NULL;

	// Variaveis que controlam o pequeno menu interativo
	int op, dado;
	do {
		printf ("\nArvore Binaria de Busca\n\t1 - Inserir\n\t2 - Apagar\n\t3 - Minimo\n\t4 - Maximo\n\t5 - Busca\n\t6 - Imprimir\n\t0 - Sair\n");
		scanf ("%d", &op);

		switch(op){
			case 1:
				printf ("Dado a inserir: ");
				scanf ("%d", &dado);
				root = inserir (root, dado);
				break;

			case 2:
				printf ("Dado a apagar: ");
				scanf ("%d", &dado);
				deletar (root, dado);
				break;
			
			case 3:
				printf ("Menor valor: ");
				aux = minimo (root);
				printf ("%d\n", (*aux).key);
				break;

			case 4:
				printf ("Maior valor: ");
				aux = maximo (root);
				printf ("%d\n", (*aux).key);
				break;
			case 5:
				printf ("Valor: ");
				scanf ("%d", &dado);
				aux = busca (root, dado);
				if (aux != NULL)
					printf ("Achado! Na memória: %d\n", aux);
				else
					printf ("Valor nao encontrado.\n");
				break;

			case 6:
				imprimir (root);
				printf("\n");
				break;
		}    		
	}while (op != 0);

	return 0;
}

node *busca (node *raiz, int key)
{
	node *aux = raiz;

	while (aux != NULL) 
	{
		if ((*aux).key == key) {		
			return aux;
		} else if (key < (*aux).key) {
			aux = (*aux).left_child;
		} else {
			aux = (*aux).right_child;
		}
	}
	return NULL;
}

node *inserir (node *raiz, int key) 
{
	node *aux;

	if (raiz == NULL) {
		raiz = (node*) malloc (sizeof(node));
		(*raiz).key = key;
		(*raiz).parent = (*raiz).left_child = (*raiz).right_child = NULL;
	}

	else { 
		if (key <= (*raiz).key) {
			aux = inserir ((*raiz).left_child, key);
			(*raiz).left_child = aux;
			(*aux).parent = raiz;
		} else {
			aux = inserir ((*raiz).right_child, key);
			(*raiz).right_child = aux;
			(*aux).parent = raiz;
		}
	}

	return raiz;
}

void imprimir (node *raiz)
{
	if (raiz != NULL) {
		imprimir ((*raiz).left_child);
		printf("%d  ", (*raiz).key);
		imprimir ((*raiz).right_child);
	}
}

node *minimo (node *raiz) 
{
	node *aux = raiz;

	while (aux != NULL)
	{
		if ((*aux).left_child == NULL) {
			break;
		} else {
			aux = (*aux).left_child;
		}
	}
	return aux;
}

node *maximo (node *raiz) 
{
	node *aux = raiz;

	while (aux != NULL)
	{
		if ((*aux).right_child == NULL) {
			break;
		} else {
			aux = (*aux).right_child;
		}
	}
	return aux;
}

node *sucessor (node *raiz)
{
	node *aux;

	if ((*raiz).right_child != NULL) {
		return minimo ((*raiz).right_child);
	}

	aux = (*raiz).parent;

	while (aux != NULL && raiz == (*aux).right_child)
	{
		raiz = aux;
		aux = (*aux).parent;
	}
	return aux;
}

node *predecessor (node *raiz)
{
	node *aux;

	if ((*raiz).left_child != NULL) {
		return maximo ((*raiz).left_child);
	}

	aux = (*raiz).parent;

	while (aux != NULL && raiz == (*aux).left_child)
	{
		raiz = aux;
		aux = (*aux).parent;
	}
	return aux;
}

void deletar (node *raiz, int key)
{
	if (raiz == NULL) {
		return;
	}

	node *pai, *filho, *aux, *set;

	set = busca (raiz, key);
	if (set == NULL){
		printf("Valor não encontrado.\n");
		return;
	} else
		printf("Deletado.\n");

	pai = (*set).parent;

	// node é uma folha
	if (((*set).left_child == NULL) && ((*set).right_child == NULL)) {
		// é um filho da direita de seu pai
		if ((*pai).right_child == set)
			(*pai).right_child = NULL;
		
		// ou filho da esquerda
		else
			(*pai).left_child = NULL;
		
		free (set);
		return;
	}
	
	// node tem um filho
	if ((*set).left_child == NULL) {
		filho = (*set).right_child;
		// é um filho da esquerda de seu pai
		if (key < (*pai).key)
			(*pai).left_child = (*set).right_child;
		else
			(*pai).right_child = (*set).right_child;

		(*filho).parent = (*set).parent;
		free(set);

	} else if ((*set).right_child == NULL) {
		filho = (*set).left_child;
		// é um filho da direita
		if (key > (*pai).key)
			(*pai).right_child = (*set).left_child;
		else
			(*pai).left_child = (*set).left_child;

		(*filho).parent = (*set).parent;
		free(set);
	}

	// node tem 2 filhos
	else {
		aux = minimo ((*set).right_child);

		(*set).key = (*aux).key;
		
		deletar ((*set).right_child, (*aux).key);

		return;
	}
	return;
}
