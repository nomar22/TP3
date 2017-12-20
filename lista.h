#ifndef _TADLISTA_H_
#define _TADLISTA_H_

#define FALSE 0
#define TRUE 1
/*
* Tipo Abstrato de Dados Lista
*
* Contém funções de manipulação (criação, inserção, remoção e liberação de memória), e também de impressão e cópia.
*
*/

#include <stdlib.h>
#include <stdio.h>




typedef struct bloco{
	int tamPalavra;
	int valor;
	int pos;
	int neg;
	int id;
	char letra;

}Bloco;

typedef Bloco *LinkBloco;

typedef int Boolean;

typedef struct Celula *LinkCelula;

typedef struct {
  LinkCelula primeiro;
  LinkCelula ultimo;
  int len;
}Lista;
typedef  Lista *LinkLista;



typedef struct Celula {
	LinkBloco bloco;
	LinkCelula anterior;
	LinkCelula prox;


}Celula;

LinkBloco* criaVetor(int i);

void criaLista(LinkLista lista);

Bloco criaRegistroVago();

LinkBloco pegarLista(int pos, LinkLista lista);

int vazia(Lista lista);

void inserePrimeiro(LinkBloco pagina, LinkLista memoria);

void removePrimeiro(LinkLista lista);

void insereBloco(char letra,int posicao, LinkLista lista);

void liberaMemoria(LinkLista lista);
void insereUltimo(LinkBloco bloco, LinkLista memoria);

LinkBloco mesclaBlocos(LinkBloco esq, LinkBloco dir);

void imprimePalavra(Lista lista);

void imprimeReverso(Lista lista);
void LiberaMemoria(Lista *lista);

#endif
