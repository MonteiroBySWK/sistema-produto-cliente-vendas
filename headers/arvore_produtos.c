#include "arvore_produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArvoreProduto *criarArvoreProdutos() {
  ArvoreProduto *arvore = (ArvoreProduto *)malloc(sizeof(ArvoreProduto));
  if (arvore != NULL)
    *arvore = NULL;

  return arvore;
}

void inserirProduto(ArvoreProduto *arvore, char *nomeProduto, int quantidade,
                    float valor) {
  if (arvore == NULL)
    return;

  NoProduto *novoProduto = (NoProduto *)malloc(sizeof(NoProduto));

  if (novoProduto == NULL) {
    printf("Erro Crítico: Falha de Alocação para novo cliente\n");
    return;
  }

  novoProduto->produto.nomeProduto = nomeProduto;
  novoProduto->produto.quantidade = quantidade;
  novoProduto->produto.valor = valor;

  if (*arvore == NULL)
    *arvore = novoProduto;

  else {
    NoProduto *atual = *arvore;
    NoProduto *anterior = NULL;

    while (atual != NULL) {
      anterior = atual;

      if (strcmp(novoProduto->produto.nomeProduto,
                 atual->produto.nomeProduto) == 0 &&
          novoProduto->produto.valor == atual->produto.valor) {
        printf("Produto Já Existe\n");
        atual->produto.quantidade += quantidade;
        free(novoProduto);
        return;
      }

      if (strcmp(novoProduto->produto.nomeProduto, atual->produto.nomeProduto) <
          0)
        atual = atual->esquerda;
      else
        atual = atual->direita;
    }

    if (strcmp(novoProduto->produto.nomeProduto,
               anterior->produto.nomeProduto) < 0)
      anterior->esquerda = novoProduto;
    else
      anterior->direita = novoProduto;
  }
}

int percorrerProdutosArvoreInOrdem(ArvoreProduto *arvore) {
  if (arvore == NULL)
    return 1;

  if (*arvore != NULL) {
    NoProduto *atual = *arvore;
    percorrerProdutosArvoreInOrdem(&(atual)->esquerda);
    printf("+-----------------------------+\n");
    printf("| Nome do Produto: %s\n", atual->produto.nomeProduto);
    printf("| Quantidade: %d\n", atual->produto.quantidade);
    printf("| Valor: %.2f\n", atual->produto.valor);
    printf("+-----------------------------+\n\n");
    percorrerProdutosArvoreInOrdem(&(atual)->direita);
  } else
    return 1;
  return 0;
}

NoProduto *buscarProduto(ArvoreProduto *arvore, char *nomeProduto) {
  if (arvore == NULL)
    return NULL;

  NoProduto *atual = *arvore;
  while (atual != NULL) {
    if (strcmp(atual->produto.nomeProduto, nomeProduto) == 0) {
      return atual;
    }

    if (strcmp(atual->produto.nomeProduto, nomeProduto) > 0)
      atual = atual->esquerda;
    else
      atual = atual->direita;
  }
  return atual;
}

NoProduto *excluirNoProduto(NoProduto *atual) {
  NoProduto *no1, *no2;

  // Caso de Não existência e Folha;
  if (atual->esquerda == NULL) {
    no2 = atual->direita;
    free(atual);
    return no2;
  }

  // Procura filho mais a direita na subarv esquerda;
  no1 = atual;
  no2 = atual->esquerda;

  while (no2->direita != NULL) {
    no1 = no2;
    no2 = no2->direita;
  }

  // Copia o filho mais a direita da subarv esq para o no removido;
  if (no1 != atual) {
    no1->direita = no2->esquerda;
    no2->esquerda = atual->esquerda;
  }

  no2->direita = atual->direita;
  free(atual);
  return no2;
}

void excluirProduto(ArvoreProduto *arvore, NoProduto *produto) {
  if (arvore == NULL)
    return;

  NoProduto *atual = *arvore;
  NoProduto *anterior = NULL;

  while (atual != NULL) {
    if (strcmp(atual->produto.nomeProduto, produto->produto.nomeProduto) == 0) {
      if (atual == *arvore)
        *arvore = excluirNoProduto(atual);
      else {
        if (anterior->esquerda == atual)
          anterior->esquerda = excluirNoProduto(atual);
        else
          anterior->direita = excluirNoProduto(atual);
      }
      return;
    }

    anterior = atual;
    if (strcmp(produto->produto.nomeProduto, atual->produto.nomeProduto) < 0)
      atual = atual->esquerda;
    else
      atual = atual->direita;
  }
}

NoProduto *produtoMaiorQuantidade(ArvoreProduto *arvore) {
  if (arvore == NULL || *arvore == NULL)
    return NULL;

  NoProduto *atual = *arvore;
  NoProduto *maior = atual;

  if (atual != NULL) {
    if (atual->produto.quantidade > maior->produto.quantidade) {
      maior = atual;
    }

    if (atual->esquerda != NULL) {
      NoProduto *esquerdaMaior = produtoMaiorQuantidade(&(atual->esquerda));
      if (esquerdaMaior != NULL &&
          esquerdaMaior->produto.quantidade > maior->produto.quantidade) {
        maior = esquerdaMaior;
      }
    }

    if (atual->direita != NULL) {
      NoProduto *direitaMaior = produtoMaiorQuantidade(&(atual->direita));
      if (direitaMaior != NULL &&
          direitaMaior->produto.quantidade > maior->produto.quantidade) {
        maior = direitaMaior;
      }
    }
  }
  return maior;
}

NoProduto *produtoMenorValor(ArvoreProduto *arvore) {
  if (arvore == NULL || *arvore == NULL)
    return NULL;

  NoProduto *atual = *arvore;
  NoProduto *menor = atual;

  if (atual != NULL) {
    if (atual->produto.valor < menor->produto.valor) {
      menor = atual;
    }

    if (atual->esquerda != NULL) {
      NoProduto *esquerdaMenor = produtoMenorValor(&(atual->esquerda));
      if (esquerdaMenor != NULL &&
          esquerdaMenor->produto.valor < menor->produto.valor) {
        menor = esquerdaMenor;
      }
    }

    if (atual->direita != NULL) {
      NoProduto *direitaMenor = produtoMenorValor(&(atual->direita));
      if (direitaMenor != NULL &&
          direitaMenor->produto.valor < menor->produto.valor) {
        menor = direitaMenor;
      }
    }
  }
  return menor;
}
