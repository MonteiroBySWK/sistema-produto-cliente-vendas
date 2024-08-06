#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente {
  char *nomeCliente;
  char *cpf;
} Cliente;

typedef struct noCliente {
  Cliente cliente;
  struct noCliente *esquerda;
  struct noCliente *direita;
} NoCliente;

typedef struct noCliente *ArvoreCliente;

typedef struct produto {
  char *nomeProduto;
  int quantidade;
  float valor;
} Produto;

typedef struct noProduto {
  Produto produto;
  struct noProduto *esquerda;
  struct noProduto *direita;
} NoProduto;

typedef struct noProduto *ArvoreProduto;

typedef struct noLista {
  NoProduto produtoLista;
  NoCliente *clienteLista;
  int quantidadeVendida;
  float valorVenda;
  struct noLista *proximo;
} NoLista;

typedef struct noLista *Lista;

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
