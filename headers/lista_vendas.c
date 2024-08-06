#include "lista_vendas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noLista {
  NoProduto produtoLista;
  NoCliente *clienteLista;
  int quantidadeVendida;
  float valorVenda;
  struct noLista *proximo;
} NoLista;

typedef struct noLista *Lista;

Lista *criarListaVendas() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  if (lista == NULL) {
    printf("Erro Fatal: Falha de Alocação para Lista de Vendas\n");
    return NULL;
  }

  *lista = NULL;
  return lista;
}

int realizarVenda(Lista *lista, NoProduto *produto, NoCliente *cliente,
                  int quantidadeVendida) {
  if (lista == NULL) {
    return 0;
  }

  NoLista *venda = (NoLista *)malloc(sizeof(NoLista));
  if (venda == NULL) {
    return 0;
  }

  Lista Ln = *lista;
  *lista = venda;

  venda->produtoLista.direita = NULL;
  venda->produtoLista.esquerda = NULL;

  venda->clienteLista = cliente;
  venda->produtoLista.produto.nomeProduto = produto->produto.nomeProduto;
  venda->produtoLista.produto.valor = produto->produto.valor;
  venda->quantidadeVendida = quantidadeVendida;

  produto->produto.quantidade -= quantidadeVendida;

  venda->valorVenda = quantidadeVendida * produto->produto.valor;
  venda->proximo = Ln;

  return 1;
}

void consultarVendas(Lista *lista) {
  if (lista == NULL) {
    printf("Erro Fatal: Lista de Vendas Não Existe\n");
    return;
  }

  Lista Ln = *lista;
  while (Ln != NULL) {
    printf("+-----------------------------+\n");
    printf("| Nome do Cliente: %s\n", Ln->clienteLista->cliente.nomeCliente);
    printf("| CPF: %s\n", Ln->clienteLista->cliente.cpf);
    printf("+-----------------------------+\n");
    printf("| Nome do Produto: %s\n", Ln->produtoLista.produto.nomeProduto);
    printf("| Quantidade Vendida: %d\n", Ln->quantidadeVendida);
    printf("| Valor: %.2f\n", Ln->valorVenda);
    printf("+-----------------------------+\n\n");
    Ln = Ln->proximo;
  }
}

void trocarNosLista(NoLista *no1, NoLista *no2) {
  NoProduto tempProduto = no1->produtoLista;
  NoCliente *tempCliente = no1->clienteLista;
  int tempQuantidade = no1->quantidadeVendida;
  float tempValor = no1->valorVenda;

  no1->produtoLista = no2->produtoLista;
  no1->clienteLista = no2->clienteLista;
  no1->quantidadeVendida = no2->quantidadeVendida;
  no1->valorVenda = no2->valorVenda;

  no2->produtoLista = tempProduto;
  no2->clienteLista = tempCliente;
  no2->quantidadeVendida = tempQuantidade;
  no2->valorVenda = tempValor;
}

NoLista *partition(NoLista *primeiro, NoLista *ultimo) {
  NoLista *pivot = primeiro;
  NoLista *frente = primeiro;
  while (frente != NULL && frente != ultimo) {
    if (strcmp(frente->produtoLista.produto.nomeProduto,
               ultimo->produtoLista.produto.nomeProduto) < 0) {
      pivot = primeiro;

      trocarNosLista(primeiro, frente);

      primeiro = primeiro->proximo;
    }

    frente = frente->proximo;
  }

  trocarNosLista(primeiro, ultimo);
  return pivot;
}

void quickSort(NoLista *primeiro, NoLista *ultimo) {
  if (primeiro == ultimo) {
    return;
  }
  NoLista *pivot = partition(primeiro, ultimo);

  if (pivot != NULL && pivot->proximo != NULL) {
    quickSort(pivot->proximo, ultimo);
  }

  if (pivot != NULL && primeiro != pivot) {
    quickSort(primeiro, pivot);
  }
}

void quickSortMain(Lista *lista) {
  NoLista *ultimo = *lista;
  while (ultimo != NULL && ultimo->proximo != NULL) {
    ultimo = ultimo->proximo;
  }
  quickSort(*lista, ultimo);
  printf("\nLista Ordenada!\n");
}
