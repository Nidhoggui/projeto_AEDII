#include<stdio.h>
#include<stdlib.h>
#include "tabela.h"
#include<string.h>

void tirar_enter(char *string)
{
  char *ptr = strtok(string, "\n");
  if (ptr != NULL) {
    strcpy(string, ptr);
  }
}


void carregar_arquivo_pato_bst(char *profissao, ArvBin *raiz)
{
  FILE *arq;
  arq = fopen(profissao, "r+");

  if (arq == NULL) {
    return;
  }

  char *linha = NULL;
  size_t len = 0;

  while (getline(&linha, &len, arq) != -1) {
    char *profissao = strtok(linha, ";");
    if (profissao == NULL) {
      continue; // linha inválida
    }

    indiceBST *novo = (indiceBST *) malloc(sizeof(indiceBST));
    novo->profissao = (char *) malloc(strlen(profissao) + 1);
    strcpy(novo->profissao, profissao);
    profissao = strtok(NULL, ";");
    novo->indice = atoi(profissao);
    insere_ArvBin(raiz, novo);
  }

  fclose(arq);
  free(linha);
}

void carregar_arquivo_pato_avl(char *habitat, ArvoreAVL *raiz)
{
  FILE *arq;
  arq = fopen(habitat, "r+");

  if (arq == NULL) {
    return;
  }

  char *linha = NULL;
  size_t len = 0;

  while (getline(&linha, &len, arq) != -1) {
    char *habitat = strtok(linha, ";");
    if (habitat == NULL) {
      continue; // linha inválida
    }

    indiceAVL *novo = (indiceAVL *) malloc(sizeof(indiceAVL));
    novo->habitat = (char *) malloc(strlen(habitat) + 1);
    strcpy(novo->habitat, habitat);
    novo->indice = atoi(habitat);
    insere_ArvAVL(raiz, novo);
  }

  fclose(arq);
  free(linha);
}

void carregar_arquivo_pato_avp(char *nome_arquivo, arvore *raiz)
{
    FILE *arq;
    arq = fopen(nome_arquivo, "r");

    if (arq == NULL) {
        return;
    }

    int idade, indice;
    while (fscanf(arq, "%d;%d\n", &idade, &indice) != EOF) {

        ArvRN *novo = cria_ArvRN(idade,indice);
        *raiz = insere_ArvRN(*raiz, novo);
    }

    fclose(arq);
}

int inicializar_Tabela(tabela *tabela)
{
  tabela->arquivo_dados = fopen("patos.dat", "a+b");

  tabela->indiceBST = cria_ArvBin();
  tabela->indiceAVL = cria_ArvAVL();
  tabela->indiceRB = inicializar(&tabela->indiceRB);

  carregar_arquivo_pato_bst("pato_bst.txt", &(tabela->indiceBST));
  carregar_arquivo_pato_avl("pato_avl.txt", &(tabela->indiceAVL));
  carregar_arquivo_pato_avp("pato_avp.txt", &(tabela->indiceAVL));

  if(tab->arquivo_dados != NULL) return 1;
  else return 0;
}

void salva_arvore_pato_bst(ArvBin raiz, FILE *arq)
{
  if(raiz != NULL)
  {
    fwrite(raiz->info, sizeof(raiz->info), 1, arq);
    salva_arquivo_pato_bst(arq, raiz->esq);
    salva_arquivo_pato_bst(arq, raiz->dir);
  }
}

void salva_arquivo_pato_bst(char *profissao, ArvBin raiz)
{
  FILE *arq;
  arq = fopen(profissao, "wb");
  if(file != NULL)
  {
    salva_arvore_pato_bst(ArvBin raiz, FILE *arq);
    fclose(arq);
  }
}

void salva_arvore_pato_avl(ArvoreAVL raiz, FILE *arq)
{
  if(raiz != NULL)
  {
    fwrite(raiz->info, sizeof(raiz->info), 1, arq);
    salva_arquivo_pato_avl(arq, raiz->esq);
    salva_arquivo_pato_avl(arq, raiz->dir);
  }
}

void salva_arquivo_pato_bst(char *habitat, ArvoreAVL raiz)
{
  FILE *arq;
  arq = fopen(habitat, "wb");
  if(file != NULL)
  {
    salva_arvore_pato_bst(ArvoreAVL raiz, FILE *arq);
    fclose(arq);
  }
}

void salva_arvore_pato_avp(arvore raiz, FILE *arq)
{
  if(raiz != NULL)
  {
    fwrite(raiz->dado, sizeof(raiz->dado), 1, arq);
    salva_arquivo_pato_avp(arq, raiz->esq);
    salva_arquivo_pato_avp(arq, raiz->dir);
  }
}

void salva_arquivo_pato_bst(char *idade, arvore raiz)
{
  FILE *arq;
  arq = fopen(idade, "wb");
  if(file != NULL)
  {
    salva_arvore_pato_bst(arvore raiz, FILE *arq);
    fclose(arq);
  }
}

void salvar_Pato(tabela *tabela, patacoada *pato)
{
  int pato_pos;


  fseek(tabela->arquivo_dados, 0, SEEK_END);
  pato_pos = ftell(tabela->arquivo_dados) / sizeof(patacoada);
  fwrite(pato, sizeof(patacoada), 1, tabela->arquivo_dados);

  insere_ArvBin(&tabela->indiceBST, cria_IndiceBST(pato_pos, pato->profissao));

  insere_ArvAVL(&tabela->indiceAVL, cria_IndiceAVL(pato_pos, pato->habitat));


  adicionar(tabela->indiceRB, );
  //int valor, arvore *raiz

/*
  salva_arquivo_pato_bst(pato->profissao, tabela->indiceBST);
  salva_arquivo_pato_avl(pato->habitat, tabela->indiceAVL);
  salva_arquivo_pato_avp(pato->idade, tabela->indiceRB);
  */
}

patacoada* ler_pato()
{
  patacoada *pato = (patacoada*) malloc(sizeof(patacoada));

  printf("Digite a idade do pato: ");
  scanf("%d", &pato->idade);

  printf("Digite o peso do pato: ");
  scanf("%f", &pato->peso);

  printf("Digite a profissão do pato: ");
  pato->profissao = ler_string();

  printf("Digite o CPF do pato: ");
  pato->cpf = ler_string();

  printf("Digite o habitat do pato: ");
  pato->habitat = ler_string();

  return pato;
}

char* ler_string()
{
  char buffer[100];
  char *string = NULL;
  int tamanho = 0;

  do {
    fgets(buffer, sizeof(buffer), stdin);
    tamanho += strlen(buffer);

    string = (char*) realloc(string, tamanho + 1);
    if (string == NULL) {
      printf("Erro de alocacao de memoria.\n");
      exit(EXIT_FAILURE);
    }

    strcat(string, buffer);
  } while (strlen(buffer) == sizeof(buffer) - 1 && buffer[sizeof(buffer) - 2] != '\n');

  // Remove o caractere '\n' do final da string
  string[strlen(string) - 1] = '\0';

  return string;
}
