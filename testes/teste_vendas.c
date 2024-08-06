#include "../headers/lista_vendas.h"

int main() {
  ArvoreCliente *clientes = criarArvoreClientes();
  inserirCliente(clientes, "Monteiro", "9238298424");
  inserirCliente(clientes, "Gabriel", "9384426872");
  inserirCliente(clientes, "Julia", "53257623");
  inserirCliente(clientes, "João", "656363463463");
  inserirCliente(clientes, "Maria", "235023570");

  percorrerClientesArvoreInOrdem(clientes);

  ArvoreProduto *produtos = criarArvoreProdutos();
  inserirProduto(produtos, "item1", 2, 199.99);
  inserirProduto(produtos, "item2", 2, 90.00);
  inserirProduto(produtos, "item3", 2, 29.99);
  inserirProduto(produtos, "item4", 2, 37.56);
  inserirProduto(produtos, "item4", 2, 56.50);

  percorrerProdutosArvoreInOrdem(produtos);

  Lista *lista = criarListaVendas();

  NoCliente *cliente1 = buscarCliente(clientes, "Monteiro");
  NoProduto *produto1 = buscarProduto(produtos, "item2");

  realizarVenda(lista, produto1, cliente1);

  consultarVendas(lista);

  return 0;
}
