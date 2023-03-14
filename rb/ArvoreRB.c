#include <stdlib.h>
#include <stdio.h>
#include "ArvoreRB.h"

//funcoes auxiliares
int eh_raiz(arvore elemento)
{
  return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento)
{
  return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento)
{
  return irmal(elemento->pai);
}

arvore irmao(arvore elemento)
{
  if(eh_filho_esquerdo) return elemento->pai->dir;
  else return elemento->pai->esq;
}

enum cor cor(arvore elemento)
{
  enum cor c;

  if(elemento==NULL) c = PRETO;
  else c = elemento->cor;

  return c;
}

arvore no_null;

/*
  Inicializa a arvore vazia com a raiz = null

  inicializa o no nulo duplo preto

  Por isso a funcao inicializar e diferente das outras
*/

IndiceAVL* cria_IndiceRB(int indice, int chave)
{
  IndiceRB * irb = (IndiceRB*) malloc(sizeof(IndiceRB));
  irb->indice = indice;
  irb->chave = chave;
}

void inicializar(arvore *raiz)
{
  *raiz = NULL;
  no_null = (arvore) malloc(sizeof(struct no_bst));
  no_null->cor = DUPLO_PRETO;
  no_null->dado = 0;
  no_null->esq = NULL;
  no_null->dir = NULL;
}

void rotacao_simples_direita(arvore *raiz, arvore pivo)
{
  arvore u, t1;
  u = pivo->esq;
  t1 = u->dir;

  /*
    Para fazer a ligacao da raiz da sub-arvore resultante com o seu pai

    primeiro tem que verificar por onde ela vai ser ligada (direita ou esquerda)
  */

  int posicao_pivo_esq = eh_filho_esquerdo(pivo);

  //atualizando posicoes dos ponteiros

  pivo->esq = t1;
  if(t1 != NULL) t1->pai = pivo;

  u->dir = pivo;

  u->pai = pivo->pai;
  pivo->pai = u;

  if(eh_raiz(u)) *raiz = u;
  else
  {
    //caso nao exista um pai pra u, u passa a ser a raiz da arvore
    //caso exista um pai pra u, ele precisa ser ligado do lado direito ou esquerdo da arvore

    if(posicao_pivo_esq) u->pai->esq = u;
    else u->pai->dir = u;
  }
}


//de forma analoga
void rotacao_simples_esquerda(arvore *raiz, arvore pivo)
{
  arvore u, t1;
  u = pivo->dir;
  t1 = u->esq;

  int posicao_pivo_esq = eh_filho_esquerdo(pivo);

  pivo->dir = t1;
  if(t1 != NULL) t1->pai = pivo;

  u->esq = pivo;

  u->pai = pivo->pai;
  pivo->pai = u;

  if(eh_raiz(u)) *raiz = u;
  else
  {
    if(posicao_pivo_esq) u->pai->esq = u;
    else u->pai->dir = u;
  }
}

void rotacao_dupla_direita(arvore *raiz, arvore elemento)
{
  rotacao_simples_esquerda(raiz, (elemento->esq));
  rotacao_simples_direita(raiz, elemento)
}

void rotacao_dupla_esquerda(arvore *raiz, arvore elemento)
{
  rotacao_simples_direita(raiz, (elemento->dir));
  rotacao_simples_esquerda(raiz, elemento)
}

void ajustar(arvore *raiz, arvore elemento)
{
  /*
    Motivos para uma arvore está desajustada:

      -> Tanto o elemento quanto o seu pai estao na cor VERMELHA


  */
  while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO)
  {
    //CASO 1: Desce o preto do vo
    if(cor(tio(elemento)) == VERMELHO)
    {
      tio(elemento)->cor = PRETO;
      elemento->pai->cor = PRETO;
      elemento->pai->pai->cor = VERMELHO;

      //Agora precisa verificar se tornar o avo vermelho fez uma sequencia vermelho-vermelho

      elemento = elemento->pai->pai;
      continue;
    }
    //CASO 2a: Rotacao simples a direita
    if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai))
    {
      rotacao_simples_direita(raiz, elemento->pai->pai);
      elemento->pai->cor = PRETO;
      (irmao(elemento))->cor = VERMELHO;
      //o "elemento" tecnicamente ja e vermelho
      continue;
    }
    //CASO 2b: Rotacao simples a esquerda
    if(!(eh_filho_esquerdo(elemento)) && !(eh_filho_esquerdo(elemento->pai)))
    {
      rotacao_simples_esquerda(raiz, elemento->pai->pai);
      elemento->pai->cor = preto;
      (irmao(elemento))->cor = VERMELHO;
      continue;
    }

    //CASO 3a: Rotacao dupla a direita
    if(!(eh_filho_esquerdo(elemento)) && eh_filho_esquerdo(elemento->pai))
    {
      rotacao_dupla_direita(raiz, elemento->pai->pai);
      elemento->cor = PRETO;
      elemento->direita->cor = VERMELHO;
      continue;
    }

    //CASO 3b: Rotacao dupla a esquerda
    if(!(eh_filho_esquerdo(elemento->pai)) && eh_filho_esquerdo(elemento))
    {
      rotacao_dupla_esquerda(raiz, elemento->pai->pai);
      elemento->cor = PRETO;
      elemento->direita->cor = VERMELHO;
      continue;
    }
  }
  (*raiz)->cor = PRETO;
}

void adicionar(int valor, arvore *raiz)
{
    arvore posicao, pai, novo
    posicao = *raiz;
    pai = NULL;

    /*
      vai ate a posicao vaga adequada para o elemento
    */

    while(posicao != NULL)
    {
      pai = posicao;
      if(valor > posicao->dado->chave) posicao = posicao->dir;
      else posicao = posicao->esq;
    }

    /*
    o pai esta sendo o ultimo elemento antes do que vai adicionar agora
    achei o lugar do pai, na variavel "pai"
    achei o lugar que sera inserido o novo no na variavel "posicao"
    */

    //inicializa um novo novo elemento
    novo = (arvore) mallor(sizeof(struct no_bst));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    /*
      Este elemento vai ser adicionado na arvore agora

        pai->esq = novo;
        pai->dir = novo;
        *raiz = novo;

      Estas sao as possibilidades
    */

    if(eh_raiz(novo)) *raiz = novo;
    else
    {
      if(valor > pai->dado->chave) pai->dir = novo;
      else pai->esq = novo;
    }

    //apos inserir, verificar e ajustar a arvore resultante
    ajustar(raiz, novo);

    //raiz tem que ser a raiz absoluta, recursao nao tem vez aqui
}

void imprimir_elemento(arvore raiz)
{
  switch (raiz->cor) {
    case PRETO:
      printf("\x1b[30m[%d]\x1b[0m", raiz->dado->chave);
      break;
    case VERMELHO:
      printf("\x1b[31m[%d]\x1b[0m", raiz->dado->chave);
      break;
    case DUPLO_PRETO:
      printf("\x1b[30m[%d]\x1b[0m", raiz->dado->chave);
      break;
  }
}

indiceRB maior_elemento(arvore raiz)
{
	if(raiz == NULL) return NULL;
	if(raiz->dir == NULL) return raiz->dado;
	else return maior_elemento(raiz->dir);
}

void remover (int valor, arvore *raiz)
{
  arvore posicao;
  posicao = *raiz;

  while(posicao != NULL)
  {
    if(valor == posicao->dado->chave)
    {
      //verifica se o elemento possui dois filhos
      if(posicao->esq != NULL && posicao->dir != NULL)
      {
        posicao->dado = maior_elemento(posicao->esq);
        remover(posicao->dado->chave, &(posicao->esq));
        break;
      }

      //o elemento possui apenas um filho (direito)
      if(posicao->esq == NULL && posicao->dir != NULL)
      {
        //o seu filho direito sobe para a posicao do elemento a ser removido e recebe a cor preta
        posicao->dir->cor = PRETO;
        posicao->dir->pai = posicao->pai;

        if(eh_raiz(posicao))
        {
          *raiz = posicao->dir;
        }else{
          if(eh_filho_esquerdo(posicao))
          {
            posicao->pai->esq = posicao->dir;
          }else{
            posicao->pai->dir = posicao->dir;
          }
        }
        free(posicao);
        break;
      }

      //o elemento possui apenas um filho (esquerdo)
      if(posicao->esq != NULL && posicao->dir == NULL)
      {
        posicao->esq->cor = PRETO;
        posicao->esq->pai = posicao->pai;

        if(eh_raiz(posicao))
        {
          *raiz = posicao->esq;
        }else{
          if(eh_filho_esquerdo(posicao))
          {
            posicao->pai->esq = posicao->esq;
          }else{
            posicao->pai->dir = posicao->dir;
          }
        }
        free(posicao);
        break;
      }

      //o elemento nao possui filhos
      if(posicao->esq == NULL && posicao->dir == NULL)
      {
        //remover raiz sem filhos
        if(eh_raiz(posicao))
        {
          *raiz = NULL;
          free(posicao);
          break;
        }
        /*
          Rrmover elemento que nao possui filhoes e nao e uma raiz
          se for vermelho, apenas remove atualizando o ponteiro do pai
          se for preto, substitui pelo duplo preto e depois ajusta a arvore
        */
        if(posicao->cor == VERMELHO)
        {
          if(eh_filho_esquerdo(posicao)) posicao->pai->esq = NULL;
          else posicao->pai->dir = NULL;
          free(posicao);
          break;
        }else{
          no_null->cor = DUPLO_PRETO;
          no_null->pai = posicao->pai;
          if(eh_filho_esquerdo(posicao)) posicao->pai->esq = no_null;
          else posicao->pai->dir = no_null;

          free(posicao);
          reajustar(raiz, no_null);
          break;
        }
      }
    }
    if(valor > posicao->dado) posicao = posicao->dir;
    else posicao = posicao->esq;
  }
}

void reajustar(arvore *raiz, arvore elemento)
{
  //caso 1
  if(eh_raiz(elemento))
  {
    retira_duplo_preto(raiz, elemento);
  }

  //caso 2
  if( cor(elemento->pai) == PRETO &&
      cor(irmao(elemento)) == VERMELHO &&
      cor(irmao(elemento)->dir) == PRETO &&
      cor(irmao(elemento)->esq) == PRETO
    )
  {
    //verifica se e caso 2 esquerdo ou direito
    if(eh_filho_esquerdo(elemento)) rotacao_simples_esquerda(raiz, elemento->pai);
    else rotacao_simples_direita(raiz, elemento->pai);

    elemento->pai->pai->cor = PRETO;
    elemento->pai->cor = VERMELHO;

    reajustar(raiz, elemento);
    return;
  }

  //caso 3
  if( cor(elemento->pai) == PRETO &&
      cor(irmao(elemento)) == PRETO &&
      cor(irmao(elemento)->dir) == PRETO &&
      cor(irmao(elemento)->esq) == PRETO
    )
  {
    //printf("caso 3\n");
    irmao(elemento)->cor = VERMELHO;

    retira_duplo_preto(raiz, elemento);
    reajustar(raiz, elemento->pai);
    return;
  }

  //caso 3 simétrico
  if( cor(elemento->pai) == PRETO &&
      cor(irmao(elemento)) == PRETO &&
      cor(irmao(elemento)->dir) == PRETO &&
      cor(irmao(elemento)->esq) == PRETO
    )
  {
    //printf("caso 3\n");
    irmao(elemento)->cor = VERMELHO;

    retira_duplo_preto(raiz, elemento);
    reajustar(raiz, elemento->pai);
    return;
  }

  //caso 4
  if( cor(elemento->pai) == VERMELHO &&
      cor(irmao(elemento)) == PRETO &&
      cor(irmao(elemento)->dir) == PRETO &&
      cor(irmao(elemento)->esq) == PRETO
    )
  {
    irmao(elemento)->cor = VERMELHO;
    elemento->pai->cor = PRETO;

    retira_duplo_preto(raiz, elemento);
    return;
  }

  //caso 5
  if(
    cor(irmao(elemento)) == PRETO &&
    cor(irmao(elemento)->esq) == VERMELHO &&
    cor(irmao(elemento)->dir) == PRETO)
   {
    if(eh_filho_esquerdo(elemento))
    {
      irmao(elemento)->cor = VERMELHO;
      irmao(elemento)->esq->cor = PRETO;
      rotacao_simples_direita(raiz, irmao(elemento));
    }
    else
    {
      irmao(elemento)->cor = VERMELHO;
      irmao(elemento)->dir->cor = PRETO;
      rotacao_simples_esquerda(raiz, irmao(elemento));
    }

    reajustar(raiz, elemento);
    return;
  }

  //simetrico do caso 5
  if(
    cor(irmao(elemento)) == PRETO &&
    cor(irmao(elemento)->dir) == VERMELHO &&
    cor(irmao(elemento)->esq) == PRETO)
   {
    if(!(eh_filho_esquerdo(elemento)))
    {
      irmao(elemento)->cor = VERMELHO;
      irmao(elemento)->dir->cor = PRETO;
      rotacao_simples_esquerda(raiz, irmao(elemento));
    }
    else
    {
      irmao(elemento)->cor = VERMELHO;
      irmao(elemento)->esq->cor = PRETO;
      rotacao_simples_direita(raiz, irmao(elemento));
    }

    reajustar(raiz, elemento);
    return;
  }

  //caso 6
  if( cor(irmao(elemento)) == PRETO &&
      cor(irmao(elemento)->dir) == VERMELHO &&
      cor(elemento) == PRETO &&
      eh_filho_esquerdo(elemento)
    )
  {
    rotacao_simples_direita(raiz, irmao(elemento));
    irmao(elemento)->cor = cor(elemento->pai);
    elemento->pai->cor = PRETO;
    irmao(elemento)->dir->cor = PRETO;
    retira_duplo_preto(raiz, elemento);
    return;
  }

  //caso simétrico 6
  if( cor(irmao(elemento)) == PRETO &&
      cor(irmao(elemento)->esq) == VERMELHO &&
      cor(elemento) == PRETO &&
      !eh_filho_esquerdo(elemento)
    )
  {
    rotacao_simples_esquerda(raiz, irmao(elemento));
    irmao(elemento)->cor = cor(elemento->pai);
    elemento->pai->cor = PRETO;
    irmao(elemento)->esq->cor = PRETO;
    retira_duplo_preto(raiz, elemento);
    return;
  }
}

void retira_duplo_preto(arvore *raiz, arvore elemento)
{
  if(elemento == no_null)
  {
    if(eh_filho_esquerdo(elemento)) elemento->pai->esq = NULL;
    else elemento->pai->dir = NULL;
  }
  else
  {
    elemento->cor = PRETO;
  }
}
