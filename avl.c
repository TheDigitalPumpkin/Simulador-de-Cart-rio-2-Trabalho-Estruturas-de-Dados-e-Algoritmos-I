#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

struct cliente
{
	signed int cod_cliente;
	signed int valor;
	signed int op;
	signed int nulo;
};

struct no
{
	struct cliente client;
	struct no* pai;
	struct no* esquerda;
	struct no* direita;
	signed int altura;
	signed int fator_balanco;
};

No* criar_avl()
{
	No* raiz = (No*) malloc(sizeof(No));
	
	if(raiz == NULL)
	{
		printf("Memoria insuficiente.\n");
		exit(1);
	}
	
	else
	{
		raiz->fator_balanco = 0;
		raiz->altura = 1;
		raiz->direita = NULL;
		raiz->esquerda = NULL;
		raiz->pai = NULL;
		raiz->client.nulo = 1;
		raiz->client.valor = 0;
		raiz->client.op = 0;
		return raiz;
	}
}

No* remove_no(No* raiz, signed int chave){
	signed int fator;
	if(raiz == NULL){
        return raiz;
    }
    if(chave < raiz->client.cod_cliente){
        raiz->esquerda = remove_no(raiz->esquerda, chave);
    }
    else if(chave > raiz->client.cod_cliente)
        raiz->direita = remove_no(raiz->direita, chave);    
    else
    {
    	
        if((raiz->esquerda == NULL) || (raiz->direita == NULL))
        {
            No* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if(temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
             *raiz = *temp;

            free(temp);
        }
		else
	    {
	        No* temp = avl_minimo(raiz->direita);
	        raiz->client = temp->client;
	        raiz->direita = remove_no(raiz->direita, temp->client.cod_cliente);
	    }
    }

    if(raiz == NULL){
    	return raiz;
    }
    atualiza_altura(raiz);
    fator = balanco_no(raiz);
    if(fator > 1 && balanco_no(raiz->esquerda) >= 0)
    	return rotacao_direita(raiz);
    	
    if(fator > 1 && balanco_no(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
	
	if(fator < -1 && balanco_no(raiz->direita) <= 0)
        return rotacao_esquerda(raiz);    
	  
    if(fator < -1 && balanco_no(raiz->direita) > 0)
    {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }
    return raiz;
}

No* avl_minimo(No* raiz)
{
	No* auxiliar = raiz;
	if(auxiliar->esquerda == NULL){
		
		return auxiliar;
	}
	
	else
	auxiliar = avl_minimo(raiz->esquerda);
	
	return 0;
}

int printa_raiz(No* raiz){
	printf("%d %d %d\n", raiz->client.cod_cliente, raiz->client.op, raiz->client.valor);
	return raiz->client.cod_cliente;
}

No* insere_no(No* raiz, signed int codigo_cliente, signed int operacao, signed int valor)
{	

	signed int fator;
	if(raiz->client.nulo == 1){
		raiz->client.cod_cliente = codigo_cliente;
		raiz->client.op = 1;
		raiz->client.valor = 0;
			
		if(operacao == 1){
			raiz->client.valor = raiz->client.valor - valor;
		}
		else{
			raiz->client.valor = raiz->client.valor + valor;
		}
		raiz->pai = NULL;
		raiz->altura = 1;
		raiz->esquerda = NULL;
		raiz->direita = NULL;
		raiz->client.nulo = 0;
	}
	else if(consulta_no(raiz, codigo_cliente)){
		atualiza_no(raiz, codigo_cliente, operacao, valor);
	}
	else if(codigo_cliente < raiz->client.cod_cliente)
	{
		if(raiz->esquerda == NULL)
		{
			
			raiz->esquerda = (No*) malloc(sizeof(No));
			raiz->esquerda->client.cod_cliente = codigo_cliente;
			raiz->esquerda->client.op = 1;
			raiz->esquerda->client.valor = 0;
			
			if(operacao == 1){
				raiz->esquerda->client.valor = raiz->esquerda->client.valor - valor;
			}
			else{
				raiz->esquerda->client.valor = raiz->esquerda->client.valor + valor;
			}
			
			raiz->esquerda->pai = raiz;
			raiz->esquerda->altura = 1;
			raiz->esquerda->esquerda = NULL;
			raiz->esquerda->direita = NULL;	
			raiz->esquerda->client.nulo = 0;		
		}
		
		else{
			raiz->esquerda = insere_no(raiz->esquerda, codigo_cliente, operacao, valor);
		}
	}
	
	else
	{
		if(raiz->direita == NULL)
		{
			raiz->direita = (No*) malloc(sizeof(No));
			raiz->direita->client.cod_cliente = codigo_cliente;
			raiz->direita->client.op = 1;
			raiz->direita->client.valor = 0;
			
			if(operacao == 1){
				raiz->direita->client.valor = raiz->direita->client.valor - valor;
			}
			else{
				raiz->direita->client.valor = raiz->direita->client.valor + valor;
			}
			
			raiz->direita->pai = raiz;
			raiz->direita->altura = 1;
			raiz->direita->esquerda = NULL;
			raiz->direita->direita = NULL;
			raiz->direita->client.nulo = 0;
		}
		
		else{
			raiz->direita = insere_no(raiz->direita, codigo_cliente, operacao, valor);
		}
	}
	
	fator = balanco_no(raiz);
	raiz->altura = atualiza_altura(raiz);
	if(fator > 1 && balanco_no(raiz->esquerda) >= 0){
    	raiz = rotacao_direita(raiz);
    	return raiz;
    }
    
    else if(fator > 1 && balanco_no(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        raiz = rotacao_direita(raiz);
        return raiz;
    }
	
	else if(fator < -1 && balanco_no(raiz->direita) <= 0){
		raiz = rotacao_esquerda(raiz);
        return raiz;    
    }
	  
    else if(fator < -1 && balanco_no(raiz->direita) > 0)
    {
        raiz->direita = rotacao_direita(raiz->direita);
        raiz = rotacao_esquerda(raiz);
        return raiz;
    }

	else{
		return raiz;
	} 
}

signed int consulta_no(No* raiz, signed int chave)
{
	if(raiz == NULL || raiz->client.cod_cliente == chave){
		return 1;
	}
	
	if(chave < raiz->client.cod_cliente)
	{
		if(raiz->esquerda == NULL){
			
			return 0;
		}
		
		else
		return consulta_no(raiz->esquerda, chave);
	}
	
	else if(chave > raiz->client.cod_cliente)
	{
		if(raiz->direita == NULL){
			return 0;
		}
		else
		return consulta_no(raiz->direita, chave);
	}
	return 0;
}

No* atualiza_no(No* raiz, signed int chave, signed int operacao, signed int valor)
{
	if(raiz == NULL || raiz->client.cod_cliente == chave){
		raiz->client.op++;
		if(operacao == 1){
			raiz->client.valor = raiz->client.valor - valor;
		}
		else{
			raiz->client.valor = raiz->client.valor + valor;
		}
		return raiz;
	}
	
	if(chave < raiz->client.cod_cliente)
	{
		if(raiz->esquerda == NULL){
			return raiz;
		}
		
		else
		return atualiza_no(raiz->esquerda, chave, operacao, valor);
	}
	
	else if(chave > raiz->client.cod_cliente)
	{
		if(raiz->direita == NULL){
			return raiz;
		}
		else
		return atualiza_no(raiz->direita, chave, operacao, valor);
	}
	return raiz;
}

int funcao_conta_nos(No* raiz)
{
	int cont = 0;
	
	if(raiz != NULL)
	{
		cont++;
		cont += funcao_conta_nos(raiz->esquerda);
		cont += funcao_conta_nos(raiz->direita);
	}

	return cont;
}

signed int numero_nos(No* raiz){
	signed int cont = 0;
	if(raiz != NULL){
		cont = funcao_conta_nos(raiz);
		printf("%d\n",cont);
	}
	return cont;
}

void lista_chaves_em_ordem(No* raiz, char ordem)
{
	if(raiz == NULL)
		return;
		
	if(ordem == 'c')
	inOrdem(raiz);
	
	else if(ordem == 'd'){
		
		inOrdemInvertido(raiz);
	}
}

void lista_chaves_nivel(No* raiz, signed int nivel)
{
	if(raiz == NULL)
	return;
	
	if(nivel == 1)
	printf("%d\n", raiz->client.cod_cliente);
	
	else if(nivel > 1)
	{
		lista_chaves_nivel(raiz->esquerda, nivel - 1);
		lista_chaves_nivel(raiz->direita, nivel - 1);
	}
}

signed int altura_no(No* x)
{
	return x ? x->altura : 0;
}

signed int balanco_no(No* x)
{
	if(x == NULL) return 0;
	
	else return altura_no(x->esquerda) - altura_no(x->direita);
}

No* balanceamento(No* x)
{
	if(balanco_no(x) == -2)
	{
		No* y = x->direita;
		
		if(balanco_no(y) == 1){
			rotacao_direita(x);
			rotacao_esquerda(x);
		}
		
		else 
		x = rotacao_esquerda(x);
	}
	
	else if(balanco_no(x) == 2)
	{
		No* y = x->esquerda;
		
		if(balanco_no(y) == -1){
			rotacao_esquerda(x);
			rotacao_direita(x);
		}
		
		else 
		x = rotacao_direita(x);
	}
	
	return x;
}

signed int max(signed int x, signed int y)
{
	
	return (x > y) ? x : y;
}

No* rotacao_direita(No* x){
	No* y = x->esquerda;
	
    if(x != NULL){
	  	if (x->pai != NULL){ 
	    	if (x->pai->esquerda == x){ 
	      		x->pai->esquerda = y; 
	    	} else{
	      		x->pai->direita = y;
	    	}
	  	}

	  	y->pai = x->pai; 
	  	x->esquerda = y->direita;

	  	if (x->esquerda != NULL) 
	    	x->esquerda->pai = x;  

	  	y->direita = x; 
	  	x->pai = y; 
	}
	x->altura = atualiza_altura(x);
	y->altura = atualiza_altura(y);
	return y;
}

No* rotacao_esquerda(No* x){
	No* y = x->direita;
    if(x != NULL){

	  	if (x->pai != NULL){  
	    	if (x->pai->direita == x){ 
	      		x->pai->direita = y; 
	    	} else{ 
	      		x->pai->esquerda = y; 
	    	}
	  	}

	  	y->pai = x->pai; 
	  	x->direita = y->esquerda;

	  	if (x->direita != NULL) 
	    	x->direita->pai = x; 

	  	y->esquerda = x; 
	  	x->pai = y; 

        x->altura = atualiza_altura(x);
        y->altura = atualiza_altura(y);
	}

	return y;
}

void rotacao_dupla_esquerda(No* x)
{
	No* y = x->direita;
	y = rotacao_direita(y);
	x = rotacao_esquerda(x);
}

void rotacao_dupla_direita(No* x)
{
	No* y = x->esquerda;
	y = rotacao_esquerda(y);
	x = rotacao_direita(x);
}

signed int atualiza_altura(No* x)
{
	if(x == NULL) return 0;
	
	x->altura = max(altura_no(x->esquerda), altura_no(x->direita)) + 1;
	return x->altura;
}

void antesOrdem(No* raiz)
{
	
	if(raiz != NULL && raiz->client.nulo == 0)
	{
		printf("%d %d %d\n", raiz->client.cod_cliente, raiz->client.op, raiz->client.valor);
		
		antesOrdem(raiz->esquerda);
		
		antesOrdem(raiz->direita);
	}
}

void posOrdem(No* raiz)
{
	if(raiz != NULL && raiz->client.nulo == 0)
	{
		posOrdem(raiz->esquerda);
		
		posOrdem(raiz->direita);
		
		printf("%d %d %d\n", raiz->client.cod_cliente, raiz->client.op, raiz->client.valor);
	}
}

void inOrdem(No* raiz)
{
	if(raiz != NULL && raiz->client.nulo == 0)
	{
		inOrdem(raiz->esquerda);
		
		printf("%d %d %d\n", raiz->client.cod_cliente, raiz->client.op, raiz->client.valor);
		
		inOrdem(raiz->direita);
	}
}

void inOrdemInvertido(No* raiz)
{
	if(raiz != NULL && raiz->client.nulo == 0)
	{
		inOrdemInvertido(raiz->direita);
		
		printf("%d %d %d\n", raiz->client.cod_cliente, raiz->client.op, raiz->client.valor);
		
		inOrdemInvertido(raiz->esquerda);
	}
}

