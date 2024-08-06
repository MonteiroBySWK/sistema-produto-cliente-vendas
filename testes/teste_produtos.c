#include "../headers/arvore_produtos.h"
#include <stdio.h>

int main() {
  ArvoreProduto *arvore = criarArvoreProdutos();

  inserirProduto(arvore, "", 2, 23.99);
  printf("1 - Passou\n");

  inserirProduto(arvore, "", 2, 23.99);
  printf("2 - Passou\n");

  inserirProduto(arvore, "item3", 2, 23.99);
  printf("3 - Passou\n");

  inserirProduto(arvore, "item4", 2, 89.6);
  printf("4 - Passou\n\n\n\n");

  percorrerProdutosArvoreInOrdem(arvore);

  NoProduto *resultado = buscarProduto(arvore, "item3");

  if (resultado != NULL)
    printf("Busca Funciona:: %s\n", resultado->produto.nomeProduto);

  excluirProduto(arvore, resultado);

  percorrerProdutosArvoreInOrdem(arvore);
}
