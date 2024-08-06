all: main

main: stdmain.o
	gcc main.c stdmain.o lista_vendas.o arvore_clientes.o arvore_produtos.o -o main.out && ./main.out

# Testes

produtos: arvore_produtos.o
	gcc  testes/teste_produtos.c arvore_produtos.o -o testes/testeProdutos.out && ./testes/testeProdutos.out

clientes: arvore_clientes.o
	gcc testes/teste_clientes.c arvore_clientes.o -o testes/testeClientes.out && ./testes/testeClientes.out

vendas: lista_vendas.o
	gcc testes/teste_vendas.c lista_vendas.o arvore_clientes.o arvore_produtos.o -o testes/testeVendas.out && ./testes/testeVendas.out

# Compilação

stdmain.o: lista_vendas.o
	gcc -c stdmain.c

lista_vendas.o: arvore_clientes.o arvore_produtos.o
	gcc -c headers/lista_vendas.c

arvore_clientes.o:
	gcc -c headers/arvore_clientes.c 

arvore_produtos.o:
	gcc -c headers/arvore_produtos.c

# Limpeza

clear:
	rm *.o 
