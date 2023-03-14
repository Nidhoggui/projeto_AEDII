#ifndef TABELA_H
#define TABELA_H
#include "../bst/ArvoreBinaria.h"
#include "../avl/ArvoreAVL.h"
#include "../rb/ArvoreRB.h"
#include<stdio.h>

typedef struct pato
{
  int idade;
  float peso;
  char *profissao;
  char *cpf; //cadastro de pato fisico
  char *habitat;
} patacoada;

typedef struct tabela
{
  FILE *arquivo_dados;
  ArvBin indiceBST;
  ArvoreAVL indiceAVL;
  arvore indiceRB;
}tabela;

int inicializar_Tabela(tabela *tabela);
void salvar_Pato(tabela *tabela, patacoada *pato);

patacoada* bst_search_pato(tabela *tabela, char *profissao);
patacoada* avl_search_pato(tabela *tabela, char *habitat);
patacoada* avp_search_pato(tabela *tabela, int idade);
void salva_arquivo_pato_bst(char *profissao, ArvBin raiz);
void salva_arquivo_pato_avl(char *habitat, ArvoreAVL raiz);
void salva_arquivo_pato_avp(int idade, arvore raiz);
void salva_arvore_pato_bst(ArvBin raiz, FILE *file);
void salva_arvore_pato_avl(ArvoreAVL raiz, FILE *file);
void salva_arvore_pato_avp(arvore raiz, FILE *file);
void carregar_arquivo_pato_bst(char *profissao, ArvBin *raiz);
void carregar_arquivo_pato_avl(char *habitat, ArvoreAVL *raiz);
void carregar_arquivo_pato_avp(char *idade, arvore *raiz);

patacoada* ler_pato();
void tirar_enter(char *string);

#endif
