#include "../headers/arvore_clientes.h"
#include <stdio.h>

// Clientes Pronto

int main() {
  ArvoreCliente *arvore = criarArvoreClientes();

  inserirCliente(arvore, "Guilherme Silva", "6239540002");
  printf("1 - Passou\n");

  inserirCliente(arvore, "Amelia Intra", "6239540002");
  printf("2 - Passou\n");

  inserirCliente(arvore, "Artelio Aires", "6324353239");
  printf("3 - Passou\n");

  inserirCliente(arvore, "Zelda Brien", "888888888");
  printf("4 - Passou\n");

  inserirCliente(arvore, "Mumbae Juyk", "99999999");
  printf("5 - Passou\n");

  inserirCliente(arvore, "Jacob Juyk", "99999999");
  printf("6 - Passou\n");

  inserirCliente(arvore, "Frank Autop", "939829839");
  printf("7 - Passou\n\n\n\n");

  percorrerClientesArvoreInOrdem(arvore);

  int altura = alturaArvoreClientes(arvore);
  printf("Altura da Arvore: %d\n\n", altura);

  NoCliente *resultado = buscarCliente(arvore, "Frank Autop");

  if (resultado != NULL)
    printf("%s\n", resultado->cliente.cpf);
}
