/*
* Tipo Abstrato de Dados de Lista
*
* Contém funções de manipulação (criação, inserção, remoção e liberação de memória), e também de impressão e cópia.
*
*/
#define FALSE 0
#define TRUE  1

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "lista.h"


LinkBloco* criaVetor(int i){
	long tamanho = pow(2,i);
	LinkBloco *vetor;
	vetor = calloc(tamanho,sizeof(LinkBloco));
	return vetor;
}

void criaLista(LinkLista lista){
	lista->primeiro = NULL;
    lista -> len=0;
    lista->ultimo = lista->primeiro;
}
int calculaFrente(char letra){
	int asc = letra;

	asc -= 97;
	return asc;
}
void imprimePalavra(Lista lista){
	LinkCelula celula;
	int i;
	celula = lista.primeiro;

	for(i=0;i< lista.len;i++,celula = celula->prox){
		printf("%c",celula->bloco->letra);
	}
	printf("\n");
}

int calculaTraz(char letra){
	int asc = letra;

	asc -= 97;
	if (!asc)
		return 0;
	return asc - 26;

}
Bloco criaRegistroVago(){
	LinkBloco bloco = (LinkBloco) malloc(sizeof(Bloco));
	bloco->tamPalavra = 0;

	return *bloco;
}
void insereBloco(char letra,int posicao, LinkLista lista){
	LinkBloco bloco = (LinkBloco) malloc(sizeof(Bloco));

	bloco->id = posicao;
	bloco->tamPalavra = 1;
	bloco->letra = letra;
	bloco ->pos = calculaFrente(letra);
	bloco->neg = calculaTraz(letra);
	bloco->valor = bloco->pos + bloco->neg < 0?bloco->pos:bloco->neg;

	insereUltimo(bloco, lista);

}
Boolean sentidoInverso(LinkBloco esq,LinkBloco dir ){
	return (esq->valor * dir->valor>0?FALSE:TRUE) ||
			(esq->pos * dir->neg>0?FALSE:TRUE);
}
int modulo(int a){
	if (a<0)
		return (a) * (-1);
	return a;
}
LinkBloco mesclaBlocos(LinkBloco esq, LinkBloco dir){
	LinkBloco bloco = (LinkBloco) malloc(sizeof(Bloco));
	int somaDireta = modulo(esq->valor) + modulo(dir->valor);
	int sentidoNeg = esq->neg< dir->neg?esq->neg:dir->neg;
	int sentidoPos = esq->pos>dir->pos?esq->pos:dir->pos;
	if(somaDireta < modulo(sentidoNeg)&& somaDireta < sentidoPos){
		bloco->valor = somaDireta;


	}
	else if(modulo(sentidoNeg)<sentidoPos){
		bloco->valor = modulo(sentidoNeg);
	}
	else{
		bloco->valor = sentidoPos;

	}
	bloco->pos = sentidoPos;
	bloco->neg = sentidoNeg;
	bloco->tamPalavra = esq->tamPalavra + dir->tamPalavra;
	return bloco;

}


void inserePrimeiro(LinkBloco bloco, LinkLista lista){

	LinkCelula primeiro  = (LinkCelula) malloc(sizeof(Celula));
	primeiro->anterior = NULL;
	primeiro->prox= lista -> primeiro;

	if(lista->len == 0){
		lista ->ultimo = primeiro;
	}
	else{
		lista->primeiro->anterior = primeiro;
	}
	lista->primeiro = primeiro;
	lista->primeiro->bloco = bloco;
    lista -> len++;
}

void insereUltimo(LinkBloco bloco, LinkLista memoria){

	LinkCelula ultimo = (LinkCelula) malloc(sizeof(Celula));
	ultimo -> prox = NULL;
	ultimo -> anterior = memoria -> ultimo;

	if(memoria->len == 0){
		memoria->primeiro = ultimo;
	}
	else{
		memoria->ultimo->prox = ultimo;
	}
	memoria->ultimo = ultimo;
	memoria->ultimo->bloco = bloco;
	memoria -> len ++;

}
int estaNoTopo(LinkCelula celula, LinkLista memoria){
	if(celula->anterior == NULL)
		return TRUE;
	return FALSE;
}
int estaNoFundo(LinkCelula celula, LinkLista memoria){
	if(celula->prox == NULL)
		return TRUE;
	return FALSE;
}
void sobeNaPilha(LinkCelula vaiSubir, LinkLista memoria){
	if(!estaNoTopo(vaiSubir,memoria)){
		LinkCelula anterior, proximo;
		anterior = vaiSubir->anterior;
		proximo = vaiSubir ->prox;

		anterior->prox = proximo;
		if(!estaNoFundo(vaiSubir,memoria)){
			proximo ->anterior = anterior;
		}
		else{
			memoria ->ultimo = anterior;

		}
		vaiSubir ->anterior = NULL;
		vaiSubir -> prox = memoria->primeiro;

		memoria->primeiro->anterior = vaiSubir;
		memoria->primeiro = vaiSubir;
	}
}
void removePrimeiro(LinkLista memoria){

    // Se for o único elemento da lista
    if (memoria->len==0){
//    	liberaMemoria(memoria);
        return;
    }
    else{
        LinkCelula primeiro = memoria ->primeiro ;
        memoria -> primeiro = primeiro->prox;
        memoria -> primeiro ->anterior = NULL;
        memoria -> len--;
        free(primeiro);
    }
}
void removeUltimo(LinkLista memoria){
	if(memoria ->len == 0){

	}
	else{
		LinkCelula ultimo = memoria->ultimo;
		memoria ->ultimo = ultimo->anterior;
		memoria ->ultimo ->prox = NULL;
		memoria->len --;
		free (ultimo);
	}
}

void retira(LinkCelula moldura, LinkLista memoria){

	moldura->anterior->prox = moldura->prox;
	moldura->prox->anterior = moldura->anterior;
	memoria -> len --;
	free(moldura);
}
void LiberaMemoria(Lista * lista){

    LinkCelula Aux, Aux2;
    Aux = lista->primeiro -> prox;

    while (Aux != NULL){
        Aux2 = Aux;
        Aux = Aux -> prox;
        free(Aux2);
    }

    free(lista->primeiro);

}
