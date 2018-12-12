#include <stdio.h>        /*Alunos: Bruno Bacelar e Gabriel Lacerda.*/
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int main() 
{	
	No* T = criar_avl();
	while(1){
		char op;
		scanf("%c",&op);
		if(op == 'i'){
			signed int cod, operation;
			signed int value;
			scanf("%d",&cod);
			scanf("%d",&operation);
			scanf("%d",&value);
			T = insere_no(T, cod, operation, value);
		}
		
		else if(op == 'c'){
			signed int key;
			scanf("%d", &key);
			if(consulta_no(T, key)){
				printf("existe no com chave: %d\n", key);
			}
			else{
				printf("nao existe no com chave: %d\n", key);
			}
		}
		
		else if(op == 'r'){
			signed int key;
			scanf("%d", &key);
			T = remove_no(T, key);
		}
		
		else if(op == 'p'){
			char x;
			scanf(" %c", &x);
			lista_chaves_em_ordem(T, x);
		}
		
		else if(op == 'n'){
			signed int nivel;
			scanf("%d", &nivel);
			lista_chaves_nivel(T, nivel);	
		}
		
		else if(op == 'h'){
			signed int altura = altura_no(T);
			printf("%d\n", altura);
		}
		
		else if(op == 'f'){
			printf("-+- Inicio relatorio -+-\n");
			numero_nos(T);
			while(T != NULL){
				int aux = printa_raiz(T);
				T = remove_no(T, aux);
			}
			printf("-+- Fim relatorio -+-");
			break;
		}
	}
	
	free(T);

}
