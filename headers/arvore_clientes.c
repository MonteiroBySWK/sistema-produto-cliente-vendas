#include "arvore_clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArvoreCliente *criarArvoreClientes() {
  ArvoreCliente *arvore = (ArvoreCliente *)malloc(sizeof(ArvoreCliente));
  if (arvore != NULL)
    *arvore = NULL;

  return arvore;
}

int alturaArvoreClientes(ArvoreCliente *arvore) {
  if (arvore == NULL || *arvore == NULL)
    return 0;

  int alturaSubArvoreEsquerda = alturaArvoreClientes(&((*arvore)->esquerda));
  int alturaSubArvoreDireita = alturaArvoreClientes(&((*arvore)->direita));

  return (alturaSubArvoreEsquerda > alturaSubArvoreDireita)
             ? alturaSubArvoreEsquerda + 1
             : alturaSubArvoreDireita + 1;
}

void inserirCliente(ArvoreCliente *arvore, char *nomeCliente, char *cpf) {
  if (arvore == NULL)
    return;

  NoCliente *novoCliente = (NoCliente *)malloc(sizeof(NoCliente));

  if (novoCliente == NULL) {
    printf("Erro Crítico: Falha de Alocação para novo cliente\n");
    return;
  }

  novoCliente->cliente.nomeCliente = nomeCliente;
  novoCliente->cliente.cpf = cpf;
  novoCliente->esquerda = NULL;
  novoCliente->direita = NULL;

  if (*arvore == NULL)
    *arvore = novoCliente;

  else {
    NoCliente *atual = *arvore;
    NoCliente *anterior = NULL;

    while (atual != NULL) {
      anterior = atual;

      if (strcmp(novoCliente->cliente.cpf, atual->cliente.cpf) == 0) {
        printf("Cliente Já Existe\n");
        free(novoCliente);
        return;
      }

      if (strcmp(novoCliente->cliente.nomeCliente, atual->cliente.nomeCliente) <
          0)
        atual = atual->esquerda;
      else
        atual = atual->direita;
    }

    if (strcmp(novoCliente->cliente.nomeCliente,
               anterior->cliente.nomeCliente) < 0)
      anterior->esquerda = novoCliente;
    else
      anterior->direita = novoCliente;
  }
}

void percorrerClientesArvoreInOrdem(ArvoreCliente *arvore) {
  if (arvore == NULL)
    return;

  if (*arvore != NULL) {
    NoCliente *atual = *arvore;
    percorrerClientesArvoreInOrdem(&(*arvore)->esquerda);
    printf("~~~~~~~~~~~~~~\n%s\n%s\n\n", atual->cliente.nomeCliente,
           atual->cliente.cpf);
    percorrerClientesArvoreInOrdem(&(*arvore)->direita);
  }
}

NoCliente *buscarCliente(ArvoreCliente *arvore, char *nomeCliente) {
  if (arvore == NULL)
    return NULL;

  NoCliente *atual = *arvore;
  while (atual != NULL) {
    if (strcmp(atual->cliente.nomeCliente, nomeCliente) == 0) {
      return atual;
    }

    if (strcmp(atual->cliente.nomeCliente, nomeCliente) > 0)
      atual = atual->esquerda;
    else
      atual = atual->direita;
  }
  return atual;
}
