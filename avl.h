#ifndef AVL_H
#define AVL_H

typedef struct cliente Cliente;
typedef struct no No;

No* criar_avl();
signed int numero_nos(No* raiz);
int printa_raiz(No* raiz);
signed int funcao_conta_nos(No* raiz);
No* insere_no(No* raiz, signed int codigo_cliente, signed int operacao, signed int valor);
No* atualiza_no(No* raiz, signed int chave, signed int operacao, signed int valor);
signed int consulta_no(No* raiz, signed int chave);
No* remove_no(No* raiz, signed int chave);
void lista_chaves_em_ordem(No* raiz, char ordem);
void lista_chaves_nivel(No* raiz, signed int nivel);
signed int altura_no(No* x);
signed int balanco_no(No* x);
No* balanceamento(No* x);
void relatorio(No* raiz);
signed int max(signed int x, signed int y);
No* rotacao_direita(No* x);
No* rotacao_esquerda(No* x);
void rotacao_dupla_esquerda(No* x);
void rotacao_dupla_direita(No* x);
signed int atualiza_altura(No* x);
No* avl_minimo(No* raiz);
void preOrdem(No* raiz);
void posOrdem(No* raiz);
void inOrdem(No* raiz);
void inOrdemInvertido(No* raiz);

#endif
