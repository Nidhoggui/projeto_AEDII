#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"

//funcoes da arvore

ArvBin* cria_ArvBin()
{
  ArvBin *raiz = (ArvBin*) malloc(sizeof(ArvBin));
  if(raiz != NULL)
  {
    *raiz = NULL;
  }
  return raiz;
}

IndiceBST* cria_IndiceBST(int indice, char* chave)
{
  IndiceBST * ibst = (IndiceBST*) malloc(sizeof(IndiceBST));
  ibst->indice = indice;
  ibst->chave (char*) malloc(sizeof(chave));
  strcpy(ibst->chave, chave);
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

void libera_ArvBin(ArvBin *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  libera_NO(*raiz); //endereco da raiz
  free(raiz); //
}

int estaVazia_ArvBin(ArvBin *raiz)
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

int altura_ArvBin(ArvBin *raiz)
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

  int alt_esq = altura_ArvBin(&((*raiz)->esq));
  int alt_dir = altura_ArvBin(&((*raiz)->dir));

  if(alt_esq > alt_dir)
  {
    return (alt_esq + 1);
  }else{
    return (alt_dir + 1);
  }
}

int totalNo_ArvBin(ArvBin *raiz)
{
  if (raiz == NULL)
  {
    return 0;
  }
  if(*raiz == NULL)
  {
    return 0;
  }
  int alt_esq = totalNo_ArvBin(&((*raiz)->esq));
  int alt_dir = totalNo_ArvBin(&((*raiz)->dir));
  return (alt_esq + alt_dir + 1);
}

void preOrdem_ArvBin(ArvBin *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  if(*raiz != NULL)
  {
    printf("%s\n", (*raiz)->info->chave);
    preOrdem_ArvBin(&((*raiz)->esq));
    preOrdem_ArvBin(&((*raiz)->dir));
  }
  //se *raiz == NULL
  //a funcao simplesmente retorna sem fazer nada
  //equivalente a um return vazio
}

void emOrdem_ArvBin(ArvBin *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  if(*raiz != NULL)
  {
    emOrdem_ArvBin(&((*raiz)->esq));
    printf("%s\t", (*raiz)->info->chave);
    emOrdem_ArvBin(&((*raiz)->dir));
  }
}

void posOrdem_ArvBin(ArvBin *raiz)
{
  if(raiz == NULL)
  {
    return;
  }
  if(*raiz != NULL)
  {
    posOrdem_ArvBin(&((*raiz)->esq));
    posOrdem_ArvBin(&((*raiz)->dir));
    printf("%s\t", (*raiz)->info->chave);
  }
}

int insere_ArvBin(ArvBin *raiz, IndiceBST* info)
{
  if(raiz == NULL)
  {
    return 0;
  }
  //define o no que sera inserido na arvore
  struct NO* novo;
  novo = (struct NO*) malloc(sizeof(struct NO));

  if(novo == NULL)
  {
    return 0;
  }

  novo->info = info;
  novo->esq = NULL;
  novo->dir = NULL;

  //procura onde este no sera inserido na arvore
  if(*raiz == NULL)
  {
    *raiz = novo;
  }else{
    struct NO *atual = *raiz;
    struct NO *ant = NULL;

    while(atual != NULL)
    {
      ant = atual;
      if(strcmp(info->chave, atual->info->chave) == 0)
      {
        //se o elemento ja existir na arvore
        //nao tem pra que adicionar 2 elementos iguais
        free(novo);
        return 0;
      }
      if(strcmp(info->chave, atual->info->chave) > 0)
      {
        atual = atual->dir;
      }else{
        atual = atual->esq;
      }
      //em algum momento chega em uma folha e sai do while
    }
    if(strcmp(info->chave, ant->info->chave) > 0)
    {
      ant->dir = novo;
    }else{
      ant->esq = novo;
    }
  }
  return 1;
}

struct NO* remove_atual(struct NO* atual)
{
  //Responsavel por tratar os 3 tipos de remocao

  //no sem filho da esquerda(nao tem nenhum valor menor)
  //substitui pelo primeiro filho da direita
  struct NO *no1, *no2;
  if(atual->esq == NULL)
  {
    no2 = atual->dir;
    free(atual);
    return no2;
  }
  //tem dois filhos
  //procura no mais a direita da subarvore a esquerda
  no1 = atual;
  no2 = atual->esq;
  while(no2->dir != NULL)
  {
    no1 = no2;
    no2 = no2->dir;
  }

  //copia o filho mais a direita na sub arvore esquerda p o no removido
  if(no1 != atual)
  {
    no1->dir = no2->esq;
    no2->esq = atual->esq;
  }

  no2->dir = atual->dir;
  free(atual);
  return no2;
}

int remove_ArvBin(ArvBin *raiz, char *chave)
{
  //Busca do nó a ser removido
  if(raiz == NULL) return 0;
  struct NO* ant = NULL;
  struct NO* atual = *raiz;
  while(atual != NULL)
  {
    if(strcmp(chave, atual->info) == 0)
    {
      if(atual == *raiz)
      {
        *raiz = remove_atual(atual);
      }else{
        //remove o no que o ant vai apontar, agora e null
        if(ant->dir == atual)
        {
          ant->dir = remove_atual(atual);
        }else{
          ant->esq = remove_atual(atual);
        }
      }
      return 1;
    }
    ant = atual;
    if(strcmp(chave, atual->info) > 0)
    {
      atual = atual->dir;
    }else{
      atual = atual->esq;
    }
  }
}

int consulta_ArvBin(ArvBin *raiz, int valor)
{
  if(raiz == NULL || *raiz == NULL) return 0;
  struct NO* atual = *raiz;

  while(atual != NULL)
  {
    if(strcmp(chave, atual->info) == 0)
    {
      return atal->info->indice;
    }
    if(strcmp(chave, atual->info) > 0)
    {
      atual = atual->dir;
    }else{
      atual = atual->esq;
    }
  }
  return -1;
}
