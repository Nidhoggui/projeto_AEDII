#include <stdlib.h>
#include <stdio.h>
#include "ArvoreBinaria.h"

int main(int argc, char **argv)
{
  ArvBin* raiz = cria_ArvBin(); //a raiz e um ponteiro para ponteiro

  int vazia = estaVazia_ArvBin(raiz);
  int tamanho = altura_ArvBin(raiz);
  int quantidade = totalNo_ArvBin(raiz);

  preOrdem_ArvBin(raiz);
  emOrdem_ArvBin(raiz);
}
