#ifndef ARVOREAVL_H
#define ARVOREAVL_H

typedef struct IndiceAVL
{
  char* chave;
  int indice;
} IndiceAVL;

struct NO
{
  int info;
  int alt; //altura da arvore
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO* ArvoreAVL;

IndiceAVL* cria_IndiceAVL(int indice, char* chave);

//funcoes auxiliares
int alt_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int maior(int x, int y);
struct NO* procuraMenor(struct NO* atual);

//rotacoes
void RotacaoLL(ArvoreAVL *raiz);
void RotacaoRR(ArvoreAVL *raiz);
void RotacaoLR(ArvoreAVL *raiz);
void RotacaoRL(ArvoreAVL *raiz);

//insercao e remocao
int insere_ArvAVL(ArvoreAVL *raiz, int valor);
int remove_ArvAVL(ArvoreAVL *raiz, int valor);

//funcoes bst
ArvoreAVL* cria_ArvAVL();
void libera_NOAVL();
void libera_ArvAVL(ArvoreAVL *raiz);

//altura e quantdade de nos
int estaVazia_ArvAVL(ArvoreAVL *raiz);
int altura_ArvAVL(ArvoreAVL *raiz);
int totalNo_ArvAVL(ArvoreAVL *raiz);

//percorrendo
void preOrdem_ArvAVL(ArvoreAVL *raiz);
void emOrdem_ArvAVL(ArvoreAVL *raiz);
void posOrdem_ArvAVL(ArvoreAVL *raiz);

//consulta
int consulta_ArvAVL(ArvoreAVL *raiz, int valor);

#endif
