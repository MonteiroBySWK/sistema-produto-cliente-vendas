#include "arvore_clientes.h"
#include "arvore_produtos.h"

typedef struct noLista NoLista;
typedef struct noLista *Lista;

Lista *criarListaVendas();
int realizarVenda(Lista *lista, NoProduto *produto, NoCliente *cliente,
                  int quantidadeVendida);
void consultarVendas(Lista *lista);
void quickSortMain(Lista *lista);
