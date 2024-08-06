#include "stdmain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções da Aplicação
void exibirMenu() {
  printf("[1] - Inserir Produto\n");
  printf("[2] - Buscar Produto\n");
  printf("[3] - Excluir Produto\n");
  printf("[4] - Exibir Estoque (In-Ordem)\n");
  printf("[5] - Alterar Produto\n");
  printf("[6] - Cadastrar Cliente\n");
  printf("[7] - Realizar Vendas\n");
  printf("[8] - Consultar Vendas\n");
  printf("[9] - Ordenar Vendas (QuickSort - Ordem Alfabetica de produtos)\n");
  printf("[10] - Retornar o Produto Com Maior Quantidade\n");
  printf("[11] - Retornar a Altura da Árvore de Clientes\n");
  printf("[12] - Retornar o produto de menor valor\n");
  printf("[99] - Sair\n\n\r");
}

void inserirProdutoMain(ArvoreProduto *produtos) {
  char *nomeProduto = (char *)malloc(512 * sizeof(char));
  int quantidade = -1;
  float valor = -1;

  printf("Nome do Produto: ");
  scanf("\r%511[^\n]", nomeProduto);
  fflush(stdin);

  while (quantidade < 0) {
    printf("Quantidade: ");
    scanf("%d", &quantidade);

    if (quantidade < 0) {
      printf("%d é uma quantidade invalida\n\n", quantidade);
    }
  }

  while (valor < 0) {
    printf("Valor: ");
    scanf("%f", &valor);

    if (valor < 0) {
      printf("%.2f é uma quantidade invalida\n\n", valor);
    }
  }

  printf("+-----------------------------+\n");
  printf("| Nome do Produto: %s\n", nomeProduto);
  printf("| Quantidade: %d\n", quantidade);
  printf("| Valor: %.2f\n", valor);
  printf("+-----------------------------+\n\n");

  int confirmar;
  printf("As informações estão corretas? [1 - Sim/0] ");
  fflush(stdin);
  scanf("%d", &confirmar);

  if (confirmar == 1) {
    inserirProduto(produtos, nomeProduto, quantidade, valor);
    printf("\nProduto Inserido\n\n");
  } else
    printf("\nProduto não inserido\n\n");
}

NoProduto *buscarProdutoMain(ArvoreProduto *produtos) {
  char *nomeProduto = (char *)malloc(512 * sizeof(char));

  printf("Nome do Produto: ");
  scanf("\r%511[^\n]", nomeProduto);
  fflush(stdin);

  NoProduto *resultado = buscarProduto(produtos, nomeProduto);

  if (resultado != NULL) {
    printf("+-----------------------------+\n");
    printf("| Nome do Produto: %s\n", resultado->produto.nomeProduto);
    printf("| Quantidade: %d\n", resultado->produto.quantidade);
    printf("| Valor: %.2f\n", resultado->produto.valor);
    printf("+-----------------------------+\n\n");
  } else {
    printf("\nProduto não encontrado\n\n");
  }

  return resultado;
}

void excluirProdutoMain(ArvoreProduto *produtos) {
  NoProduto *aExcluir = buscarProdutoMain(produtos);

  if (aExcluir != NULL) {
    int confirmar;
    printf("Deseja excluir produto? [1 - Sim/0] ");
    scanf("%d", &confirmar);

    excluirProduto(produtos, aExcluir);
    printf("\nProduto excluido\n\n");
  }
}

void percorrerEstoque(ArvoreProduto *produtos) {
  if (percorrerProdutosArvoreInOrdem(produtos))
    printf("Não há produtos\n\n");
}

void alterarProdutoMain(ArvoreProduto *produtos) {
  NoProduto *aAlterar = buscarProdutoMain(produtos);

  if (aAlterar == NULL)
    return;

  int confirmar;
  printf("Deseja Alterar produto? [1 - Sim/0] ");
  scanf("%d", &confirmar);

  int sair = 0;
  int escolha;
  do {
    printf("[1] - Alterar Nome\n");
    printf("[2] - Alterar Quantidade\n");
    printf("[3] - Alterar Valor\n");
    printf("[99] - Encerrar Alterações\n");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("Novo Nome de Produto: ");
      scanf("\r%511[^\n]", aAlterar->produto.nomeProduto);
      break;
    case 2:
      printf("Nova Quantidade: ");
      scanf("%d", &aAlterar->produto.quantidade);
      break;
    case 3:
      printf("Novo Valor: ");
      scanf("%f", &aAlterar->produto.valor);
      break;
    case 99:
      sair = 1;
    }
  } while (!sair);
}

void cadastrarCliente(ArvoreCliente *clientes) {
  char *nomeCliente = (char *)malloc(256 * sizeof(char));
  char *cpf = (char *)malloc(12 * sizeof(char));

  printf("Nome do Cliente: ");
  fflush(stdin);
  scanf("\r%255[^\n]", nomeCliente);
  printf("CPF: ");
  fflush(stdin);
  scanf("\r%11[^\n]", cpf);

  printf("+-----------------------------+\n");
  printf("| Nome do Cliente: %s\n", nomeCliente);
  printf("| CPF: %s\n", cpf);
  printf("+-----------------------------+\n\n");

  int confirmar;
  printf("As informações estão corretas? [1 - Sim/0] ");
  fflush(stdin);
  scanf("%d", &confirmar);

  if (confirmar == 1)
    inserirCliente(clientes, nomeCliente, cpf);
  else
    printf("Cliente não inserido\n\n");
}

void realizarVendaMain(Lista *vendas, ArvoreProduto *produtos,
                       ArvoreCliente *clientes) {

  char *nomeCliente = (char *)malloc(256 * sizeof(char));
  char *nomeProduto = (char *)malloc(512 * sizeof(char));

  // Buscar Produto

  printf("Nome do Produto: ");
  fflush(stdin);
  scanf("\r%511[^\n]", nomeProduto);

  NoProduto *resultadoProduto = buscarProduto(produtos, nomeProduto);

  if (resultadoProduto == NULL) {
    printf("\nProduto Não Encontrado\n\n");
    return;
  }

  printf("\n+-----------------------------+\n");
  printf("| Nome do Produto: %s\n", resultadoProduto->produto.nomeProduto);
  printf("| Quantidade: %d\n", resultadoProduto->produto.quantidade);
  printf("| Valor: %.2f\n", resultadoProduto->produto.valor);
  printf("+-----------------------------+\n\n");

  int confirmar;
  printf("As informações estão corretas? [1 - Sim/0] ");
  fflush(stdin);
  scanf("%d", &confirmar);

  if (confirmar != 1)
    return;

  int quantidadeVenda;
  printf("Quantidade a ser vendida: ");
  fflush(stdin);
  scanf("%d", &quantidadeVenda);

  if (quantidadeVenda > resultadoProduto->produto.quantidade) {
    printf("\nNão há produtos suficientes para a vendas\n\n");
    return;
  }

  // Buscar Cliente

  printf("Nome do Cliente: ");
  fflush(stdin);
  scanf("\r%255[^\n]", nomeCliente);

  NoCliente *resultadoCliente = buscarCliente(clientes, nomeCliente);

  if (resultadoProduto == NULL) {
    printf("\nCliente Não Cadastrado\n\n");
    return;
  }

  printf("\n+-----------------------------+\n");
  printf("| Nome do Cliente: %s\n", resultadoCliente->cliente.nomeCliente);
  printf("| CPF: %s\n", resultadoCliente->cliente.cpf);
  printf("+-----------------------------+\n\n");

  printf("As informações estão corretas? [1 - Sim/0] ");
  fflush(stdin);
  scanf("%d", &confirmar);

  if (confirmar != 1)
    return;

  int status = realizarVenda(vendas, resultadoProduto, resultadoCliente,
                             quantidadeVenda);
  if (status) {
    if (resultadoProduto->produto.quantidade == 0) {
      excluirProduto(produtos, resultadoProduto);
    }
    printf("\nVenda Realizada\n\n");
  } else
    printf("\nOcorreu algum Erro\n\n");
}

void retornarProdutoMenorValor(ArvoreProduto *produtos) {
  if (produtos == NULL || *produtos == NULL) {
    printf("\nSem Produtos\n\n");
    return;
  }

  NoProduto *produto = produtoMenorValor(produtos);
  printf("\nProduto de menor Valor");
  printf("\n+-----------------------------+\n");
  printf("| Nome do Produto: %s\n", produto->produto.nomeProduto);
  printf("| Quantidade: %d\n", produto->produto.quantidade);
  printf("| Valor: %.2f\n", produto->produto.valor);
  printf("+-----------------------------+\n\n");
}

void retornarProdutoMaiorQuantidade(ArvoreProduto *produtos) {
  if (produtos == NULL || *produtos == NULL) {
    printf("\nSem Produtos\n\n");
    return;
  }

  NoProduto *produto = produtoMaiorQuantidade(produtos);
  printf("\nProduto de maior Quantidade\n");
  printf("\n+-----------------------------+\n");
  printf("| Nome do Produto: %s\n", produto->produto.nomeProduto);
  printf("| Quantidade: %d\n", produto->produto.quantidade);
  printf("| Valor: %.2f\n", produto->produto.valor);
  printf("+-----------------------------+\n\n");
}

int main() {
  // Entidades Principais do Programa
  ArvoreCliente *clientes = criarArvoreClientes();
  ArvoreProduto *produtos = criarArvoreProdutos();
  Lista *vendas = criarListaVendas();

  int escolhaDoMenu, sair = 0;
  while (!sair) {
    exibirMenu();
    printf("Escolha>> ");
    fflush(stdin);
    scanf("%d", &escolhaDoMenu);
    printf("\n");

    switch (escolhaDoMenu) {
    case 1: // Pronto
      inserirProdutoMain(produtos);
      break;
    case 2: // Pronto
      buscarProdutoMain(produtos);
      break;
    case 3: // Pronto
      excluirProdutoMain(produtos);
      break;
    case 4: // Pronto
      percorrerEstoque(produtos);
      break;
    case 5: // Pronto *Falta verificação de igualdade*
      alterarProdutoMain(produtos);
      break;
    case 6: // Pronto
      cadastrarCliente(clientes);
      break;
    case 7: // Pronto
      realizarVendaMain(vendas, produtos, clientes);
      break;
    case 8: // Pronto
      consultarVendas(vendas);
      break;
    case 9: // Pronto
      quickSortMain(vendas);
      break;
    case 10: // Pronto
      retornarProdutoMaiorQuantidade(produtos);
      break;
    case 11: // Pronto
      printf("\nA Altura da Arvore de CLientes é: %d\n\n",
             alturaArvoreClientes(clientes));
      break;
    case 12: // Pronto
      retornarProdutoMenorValor(produtos);
      break;
    case 99:
      sair = 1;
    }
  }
  return 0;
}
