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

ArvoreProduto *criarArvoreProdutos();
void inserirProduto(ArvoreProduto *arvore, char *nomeProduto, int quantidade,
                    float valor);

int percorrerProdutosArvoreInOrdem(ArvoreProduto *arvore);
NoProduto *buscarProduto(ArvoreProduto *arvore, char *nomeProduto);
NoProduto *excluirNoProduto(NoProduto *atual);
void excluirProduto(ArvoreProduto *arvore, NoProduto *produto);
NoProduto *produtoMaiorQuantidade(ArvoreProduto *arvore);
NoProduto *produtoMenorValor(ArvoreProduto *arvore);
