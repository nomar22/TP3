
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
/*
 * tp3.c
 *
 *  Created on: 16/06/2013
 *      Author: rafaelramon
 */
// os números que encontram-se na lista são as potencias de 2 100 010 001
//http://daemoniolabs.wordpress.com/2012/04/28/bit-hacking-manipulacao-de-bits/
Boolean estaNalista(int inteiro){
	int retorno = inteiro && !(inteiro &(inteiro-1));
//	printf("potencia de 2 %d - %d \n", inteiro,retorno);
	return retorno;
}
//Logaritmo base 2
int logDois(int pos){
	int retorno = 0;
	while (pos>0){
		pos = pos/2;
		retorno ++;
	}
	return retorno;
}
///	   0   1	 1   0       0   1
//AFD  0-------> 1 --------> 0 ----> E
Boolean letrasSeparadas(int inteiro){
	int result, rest;
	Boolean pri= FALSE;
	Boolean zero = FALSE;

	result = inteiro/2;
	rest = inteiro%2;
	while(result > 1){
		if (!rest && pri){
			zero = TRUE;
		}
		else if(rest && !pri){
			pri = TRUE;
		}
		else if(rest && pri && zero){
			return TRUE;
		}
		rest = result % 2;
		result = result/2;
	}
	if (!result && pri){
		zero = TRUE;
	}
	else if(rest && !pri){
		pri = TRUE;
	}
	else if((rest || result) && pri && (zero|| !rest)){
		return TRUE;
	}

	return FALSE;

}
LinkBloco pegarLista(int pos, LinkLista lista){
	int i = 0;
	//sabidamente uma potencia de 2
	int num = logDois(pos);
	LinkCelula aux;
	aux = lista->primeiro;
	while(i < num && pos >0){
		aux = aux->prox;
		i++;
	}
	return aux->bloco;

}
int menorAnteriorUsado(int inteir){
	//Comeca por uma posicao anterior ao do id
	for (;letrasSeparadas(inteir) ; inteir--);
	return inteir-1; //Retorna a posicao do menorAnterior

}
LinkBloco melhorCaso(int id, LinkBloco *vetor){
	LinkBloco melhor = NULL;
	LinkBloco bloco, compara,segParc = NULL;
	int inicio,maiorPreenchido;
	Boolean  terminou = FALSE;
	// -1 deve pegar a partir da posição anterior do vetor
	// -1 pois ids comecam com 0 e inteiros a partir do 1

	inicio = id;

	while(!terminou){
		// Utiliza neste caso o anterior -1, pois quer se saber o menor antes do atual
		maiorPreenchido = menorAnteriorUsado(id);
		bloco = vetor[maiorPreenchido];
		// +1 para utilizar o valor do inteiro e -1 para usar o valor do indice
		int segunda = ((inicio+1 )- (maiorPreenchido+1))-1;
		segParc = vetor[segunda];
		if (!letrasSeparadas(segunda+1)&& segunda != maiorPreenchido){
			//Caso seja uma soma válida, converge os blocos e compara se é melhor que
			//o atual melhor
			//TODO aqui q o pau tá cCOMENDO
			compara = mesclaBlocos(segParc,bloco);
			if(melhor==NULL || melhor->valor > compara->valor ){
				melhor = compara ;
			}
		}
		id = maiorPreenchido;
		if(id+1 <= (inicio+1)/2){
			terminou = TRUE;
		}
	}
	return  melhor;

}
void calculaValor(int i, LinkBloco *vetor, LinkLista lista){
	//Ainda não calculado

	//Pegar diretamente da lista lida do arquivo
	//+1 pois a lógica binária utilizada considera o primeiro indice = 0
	if(estaNalista(i+1)){
		vetor[i] = pegarLista(i,lista);
	}
//		pegar dos subconjuntos
	else{
		vetor[i] = melhorCaso(i, vetor);
	}
}


int main(int argc, char** argv) {

	int numSenhas	;
	int count, i,j;

	char *ArquivoInput = argv[1];  //Primeiro Parametro:Arquivo de Entrada.
	char *ArquivoOutput = argv[2]; //Segundo Parametro:Arquivo de Saída.
	char c = ' ';
	Lista lista ;
	//Vetor de blocos
	LinkBloco *vetor;
	long int tamanhoVetor;


	FILE *fp;
	fp = fopen(ArquivoInput,"r"); //Abre arquivo para escrever
	FILE *arquivoSaida;
	arquivoSaida = fopen(ArquivoOutput,"w"); //Abre arquivo para escrever
	if(!fp){
		printf("Erro na leitura de entrada!");
		return 0;
	}
	fscanf (fp,"%d\n",&numSenhas);
	//Passa por todas as Instancias
	for(count=0;count<numSenhas;count++){
		fscanf (fp,"%c", &c);
			criaLista(&lista);
			insereBloco(c,i,&lista);

		for(j = 0;c != '\n';j++){
			fscanf (fp,"%c", &c);
			insereBloco(c,j,&lista);
		}
		vetor =  criaVetor(j);
		tamanhoVetor = pow(2,j);
		imprimePalavra(lista);
		for (i=0;i<tamanhoVetor-1; i++){
			//devemos mover apenas blocos juntos a partir do valor do número binário
			if(!letrasSeparadas(i+1)){
				 calculaValor(i,vetor,&lista);
			}
			else{
				vetor[i] = NULL;
			}
		}
		LinkBloco aux ;
		for(i =0; i<tamanhoVetor ; i++){
			aux = vetor[i];
		}

		fprintf(arquivoSaida,"%d \n",modulo(vetor[tamanhoVetor-2]->valor));
		LiberaMemoria(&lista);
	}


    return (0);
}

