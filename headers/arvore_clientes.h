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

ArvoreCliente *criarArvoreClientes();
int alturaArvoreClientes(ArvoreCliente *arvore);
void inserirCliente(ArvoreCliente *arvore, char *nomeCliente, char *cpf);
void percorrerClientesArvoreInOrdem(ArvoreCliente *arvore);
NoCliente *buscarCliente(ArvoreCliente *arvore, char *nomeCliente);
