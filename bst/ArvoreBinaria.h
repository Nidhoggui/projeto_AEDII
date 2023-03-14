#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

//elementos da arvore

typedef struct IndiceBST {
  char* chave;
  int indice;
} IndiceBST;

struct NO
{
  IndiceBST info;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO *ArvBin;

//funcoes da arvore

//funcoes indice

IndiceBST* cria_IndiceBST(int indice, char* chave);

//cria e destroi
ArvBin* cria_ArvBin();
void libera_NO(); //funcao auxiliar para liberar toda a arvore
void libera_ArvBin(ArvBin *raiz);

//altura e quantdade de nos
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNo_ArvBin(ArvBin *raiz);

//percorrendo
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

//insercao e remocao
int insere_ArvBin(ArvBin *raiz, IndiceBST info);

struct NO* remove_atual(struct NO* atual); //funcao auxiliar para remover um elemento da arvore
int remove_ArvBin(ArvBin *raiz, int valor);

//consulta
int consulta_ArvBin(ArvBin *raiz, int valor);

#endif
