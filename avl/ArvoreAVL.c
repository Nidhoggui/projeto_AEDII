#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

ArvoreAVL* cria_ArvAVL()
{
  ArvoreAVL *raiz = (ArvoreAVL*) malloc(sizeof(ArvoreAVL));
  if(raiz != NULL)
  {
    *raiz = NULL;
  }
  return raiz;
}

IndiceAVL* cria_IndiceAVL(int indice, char* chave)
{
  IndiceAVL * iavl = (IndiceAVL*) malloc(sizeof(IndiceAVL));
  iavl->indice = indice;
  iavl->chave (char*) malloc(sizeof(chave));
  strcpy(iavl->chave, chave);
}

void libera_NO(struct NO *no)
{
  if(no == NULL)
  {
    return;
  }
  libera_NO(no->esq);
  libera_NO(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvAVL(ArvoreAVL *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  libera_NO(*raiz); //endereco da raiz
  free(raiz); //
}

int estaVazia_ArvAVL(ArvoreAVL *raiz)
{
  if(raiz == NULL) //raiz = endereco
  {
    return 1;
  }
  if(*raiz == NULL) //*raiz = condeudo do endereco/endereco que aponta para o primeiro no
  {
    return 1;
  }
  return 0;
}

int altura_ArvAVL(ArvoreAVL *raiz)
{
  if (raiz == NULL)
  {
    //a arvore nao foi declarada ou sua declaracao deu pau
    return 0;
  }

  if(*raiz == NULL)
  {
    //a arvore foi declarada mas ainda nao foi adicionado nenhum no
    return 0;
  }

  int alt_esq = altura_ArvAVL(&((*raiz)->esq));
  int alt_dir = altura_ArvAVL(&((*raiz)->dir));

  if(alt_esq > alt_dir)
  {
    return (alt_esq + 1);
  }else{
    return (alt_dir + 1);
  }
}

int totalNo_ArvAVL(ArvoreAVL *raiz)
{
  if (raiz == NULL)
  {
    return 0;
  }
  if(*raiz == NULL)
  {
    return 0;
  }
  int alt_esq = totalNo_ArvAVL(&((*raiz)->esq));
  int alt_dir = totalNo_ArvAVL(&((*raiz)->dir));
  return (alt_esq + alt_dir + 1);
}

void preOrdem_ArvAVL(ArvoreAVL *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  if(*raiz != NULL)
  {
    printf("%d\n", (*raiz)->info);
    preOrdem_ArvAVL(&((*raiz)->esq));
    preOrdem_ArvAVL(&((*raiz)->dir));
  }
  //se *raiz == NULL
  //a funcao simplesmente retorna sem fazer nada
  //equivalente a um return vazio
}

void emOrdem_ArvAVL(ArvoreAVL *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  if(*raiz != NULL)
  {
    emOrdem_ArvAVL(&((*raiz)->esq));
    printf("%d\t", (*raiz)->info);
    emOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void posOrdem_ArvAVL(ArvoreAVL *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  if(*raiz != NULL)
  {
    posOrdem_ArvAVL(&((*raiz)->esq));
    posOrdem_ArvAVL(&((*raiz)->dir));
    printf("%d\t", (*raiz)->info);
  }
}

int consulta_ArvAVL(ArvoreAVL *raiz, int valor)
{
  if(raiz == NULL || *raiz == NULL) return 0;
  struct NO* atual = *raiz;

  while(atual != NULL)
  {
    if(valor == atual->info)
    {
      return 1;
    }
    if(valor > atual->info)
    {
      atual = atual->dir;
    }else{
      atual = atual->esq;
    }
  }
  return 0;
}


int alt_NO(struct NO* no)
{
  if(no == NULL)
  {
    return -1;
  }else{
      return no->alt;
  }
}

int fatorBalanceamento_NO(struct NO* no)
{
    //labs retorna o valor em modulo(valor absoluto)
    return labs(alt_NO(no->esq) - alt_NO(no->dir));
}

int maior(int x, int y)
{
  if(x > y)
  {
    return x;
  }else{
    return y;
  }
}

void RotacaoLL(ArvoreAVL *raiz)
{
  struct NO *no;

  no = (*raiz)->esq;
  (*raiz)->esq = no->dir;
  no->dir = *raiz;

  (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
  no->alt = maior(alt_NO(no->esq), (*raiz)->alt) + 1;

  *raiz = no;
}

void RotacaoRR(ArvoreAVL *raiz)
{
  struct NO *no;

  no = (*raiz)->dir;
  (*raiz)->dir = no->esq;
  no->esq = (*raiz);

  (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
  no->alt = maior(alt_NO(no->dir), (*raiz)->alt) + 1;

  (*raiz) = no;
}

void RotacaoLR(ArvoreAVL *raiz)
{
  RotacaoRR(&(*raiz)->esq);
  RotacaoLL(raiz);
}

void RotacaoRL(ArvoreAVL *raiz)
{
  RotacaoLL(&(*raiz)->dir);
  RotacaoRR(raiz);
}

int insere_ArvAVL(ArvoreAVL *raiz, indiceAVL valor)
{
  int res = 0;

  if(*raiz == NULL)
  {
    //arvore esta vazia ou no folha
    struct NO *novo;
    novo = (struct NO*)malloc(sizeof(struct NO));

    if(novo == NULL) return 0;

    novo->info = valor;
    novo->alt = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    *raiz = novo;
    return 1;
  }

  struct NO *atual = *raiz;

  if(valor < atual->info)
  {
    if((res = insere_ArvAVL(&(atual->esq), valor))==1)
    {
      if(fatorBalanceamento_NO(atual) >= 2)
      {
        if(valor < (*raiz)->esq->info)
        {
          RotacaoLL(raiz);
        }else{
          RotacaoLR(raiz);
        }
      }
    }
  }else{
    if(valor > atual->info)
    {
      if((res=insere_ArvAVL(&(atual->dir), valor))==1)
      {
        if(fatorBalanceamento_NO(atual) >= 2)
        {
          if((*raiz)->dir->info < valor)
          {
            RotacaoRR(raiz);
          }else{
            RotacaoRL(raiz);
          }
        }
      }
      }else{
        puts("Valor duplicado!");
        return 0;
      }
    }

  atual->alt = maior (alt_NO(atual->esq), alt_NO(atual->dir)) + 1;

  return res;
}

struct NO* procuraMenor(struct NO* atual)
{
  //Funcao responsavel por tratar a remocao de um no com 2 filhos
  struct NO *no1 = atual;
  struct NO *no2 = atual->esq;

  while(no2 != NULL)
  {
    no1 = no2;
    no2 = no2->esq;
  }
  return no1;
}

int remove_ArvAVL(ArvoreAVL *raiz, int valor)
{
  //Funcao responsavel pela busca do no a ser removido
  if(*raiz == NULL)
  {
    puts("valor nao existe!");
    return 0;
  }
  int res = 0;

  if(valor < (*raiz)->info)
  {
    if((res=remove_ArvAVL(&(*raiz)->esq, valor))==1)
    {
      if(alt_NO((*raiz)->dir->esq) <= alt_NO((*raiz)->dir->dir))
      {
        RotacaoRR(raiz);
      }else{
        RotacaoRL(raiz);
      }
    }
  }

  if((*raiz)->info < valor)
  {
    if((res=remove_ArvAVL(&(*raiz)->dir, valor))==1)
    {
      if(fatorBalanceamento_NO(*raiz) >= 2)
      {
        if(alt_NO((*raiz)->esq->dir) <= alt_NO((*raiz)->esq->esq))
        {
          RotacaoLL(raiz);
        }else{
          RotacaoLR(raiz);
        }
      }
    }
  }

  if((*raiz)->info == valor)
  {
    if(((*raiz)->esq==NULL || (*raiz)->dir==NULL))
    {
      struct NO *oldNode = (*raiz);
      if((*raiz)->esq != NULL)
      {
        *raiz = (*raiz)->esq;
      }else{
        *raiz = (*raiz)->dir;
      }
      free(oldNode);
    }else{

      struct NO *temp = procuraMenor((*raiz)->dir);
      (*raiz)->info = temp->info;
      remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);

      if(fatorBalanceamento_NO(*raiz) >= 2)
      {
        if(alt_NO((*raiz)->esq->dir) <= alt_NO((*raiz)->esq->esq))
        {
          RotacaoLL(raiz);
        }else{
          RotacaoLR(raiz);
        }
      }
    }
    return 1;
  }
  return res;
}
