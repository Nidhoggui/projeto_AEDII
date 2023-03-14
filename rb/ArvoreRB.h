#ifndef ARVORERB_H
#define ARVORERB_H

#include <stdlib.h>

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct indiceRB {
  int chave;
  int indice;
} indiceRB;

typedef struct NO
{
  indiceRB dado;
  struct NO *esq;
  struct NO *dir;
  struct NO *pai; //para nao usar recursao
  enum cor cor;
} no_bst;

typedef no_bst* arvore;

IndiceAVL* cria_IndiceRB(int indice, int chave);

void inicializar(arvore *raiz);
void adicionar (int valor, arvore *raiz);
void remover (int valor, arvore *raiz);

int altura(arvore raiz);
int maior(int a, int b);
indiceRB maior_elemento(arvore raiz);
//indiceRB menor_elemento(arvore raiz);
void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);

void imprimir_elemento(arvore raiz);
void imprimir(arvore raiz);

enum cor cor(arvore elemento);
void ajustar(arvore *raiz, arvore elemento);
void reajustar(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);

int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
arvore irmao(arvore elemento);
arvore tio(arvore elemento);
void retira_duplo_preto(arvore *raiz, arvore elemento);

#endif
