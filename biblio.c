/*******************************************************************************
 |                        USP-Universidade de São Paulo                        |
 |            ICMC-Instituto de Ciências Matemáticas e de Computação           |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                   2020/1                                    |
 |                                                                             |
 |                        Autor: Gabriela Satie (11892820)                     |
 *******************************************************************************
 Programa que simula o funcionamento de uma biblioteca
 *******************************************************************************/

#include <stdio.h> // Utilização das funções scanf() e printf()
#include <stdlib.h> // Utilização das funções malloc(), realloc(), e atoi()
#include <string.h> // Utilização da função strcmp()

#define READLINE_BUFFER 4096

// Função que lerá os caracteres digitados
char *readLine(FILE *stream) {
	char *string = NULL;
	int i = 0;

	do {
		if (i % READLINE_BUFFER == 0) {
			string = (char *) realloc(string,(i / READLINE_BUFFER + 1) * READLINE_BUFFER);
		}
		string[i] = fgetc(stream);
		i++;
	} while (string[i-1] != '\n' && string[i-1] != EOF);

	if (i >= 2 && string[i - 2] == '\r') {
		string[i - 2] = '\0';
		string = (char* ) realloc(string, i-1);
	} else {
		string[i-1] = '\0';
		string = (char* ) realloc(string, i);
	}

	return string;
}

// Struct que define os livros, com o título e os dias para devolução
typedef struct {
	char *title;
	int days;
} Book;

// Função que aloca os livros
void allocBooks(int quantBooks, Book *books){
	for (int i = 0; i < quantBooks; i++){
		books[i].title = readLine(stdin);
		
		char *tempBookDays = readLine(stdin);
		books[i].days = atoi(tempBookDays); // Conversão de char* para int

		free(tempBookDays);
	}
}

// Função que realiza a operação um
void operationOne(int quantBooks, int *quantRented, Book *books, Book *rented){
	printf("Digite o livro que voce procura:\n");
	char *search = readLine(stdin);

	int index = -1; // Guardará a posição do livro procurado

	for (int i = 0; i < quantBooks; i++){
		if (strcmp(books[i].title, search) == 0){
			index = i;
		}
	}
	
	if(index == -1){
		printf("Livro nao encontrado na biblioteca\n");
		return;
	}

	if ((*quantRented) == 10){
			printf("Voce ja tem 10 livros alugados\n");
	} else {
		// Comparação dentro da lista de alugados
		for (int j = 0; j < *quantRented; j++){
			if (strcmp(search, rented[j].title) == 0){
				printf("Livro ja alugado\n");
				return;
			}
		}
		
		rented[*quantRented] = books[index]; // Adicionar o livro à lista de alugados
		printf("%s alugado com sucesso\n", search);
		(*quantRented) += 1;
	}
	
	free(search);
	return;
}

// Função que realiza a operação dois
void operationTwo(int quantRented, Book *rented){
	if (quantRented == 0){
		printf("Voce nao tem livros alugados\n");
		return;
	} else {
		printf("Voce tem %d livro(s) alugado(s)\n", quantRented);
		
		// Impressão da lista de alugados
		for (int i = 0; i < quantRented; i++){
			printf("Livro nome: %s\nDevolve-lo daqui %d dias\n", rented[i].title, rented[i].days);
		}
	}

	return;
}

// Função swap, que irá organizar os livros após sua devolução
void swap(Book *a, Book *b){
	Book t = *b;
	*a = *b;
	*b = t;
}

// Função que realiza a operação três
void operationThree(int *quantRented, Book *rented){
	printf("Digite o livro que deseja devolver:\n");
	char *search = readLine(stdin);
	
	int index = -1; // Guardará a posição do livro procurado

	for (int i = 0; i < *quantRented; i++){
		if (strcmp(rented[i].title, search) == 0){
			index = i;
		}
	}
	
	if (index == -1){
		printf("Voce nao possui esse livro\n");
		return;
	}

	// Organização dos livros de volta à ordem original (cronológica)
	for (int i = index; i < (*quantRented-1); i++){
		swap(&rented[i], &rented[i+1]);
	}

	*quantRented -= 1;
	printf("Livro %s foi devolvido com sucesso\n", search);
	
	free(search);
	return;
}

// Função que realizará a maior parte das desalocações
void freeLibrary(int quantBooks, Book *books, Book *rented, char *tempQuantBooks, char *tempOp){
	for (int i = 0; i < quantBooks; i++){
		free(books[i].title);
	}
	
	free(tempQuantBooks);
	free(tempOp);
	free(books);
	free(rented);
	
	return;
}

int main(int argc, char *argv[]){
	char *tempQuantBooks = readLine(stdin);
	int quantBooks = atoi(tempQuantBooks); // Conversão de char* para int

	int quantRented = 0;
	
	// Alocação da lista de livros
	Book *books = (Book *) malloc(sizeof(Book) * quantBooks); 
	allocBooks(quantBooks, books);

	// Alocação da lista de alugados
	Book *rented = (Book *) malloc(sizeof(Book) * 10);
	
	int op = 0; // Operação escolhida pelo usuário
	char *tempOp;

	do {
		tempOp = readLine(stdin);
		op = atoi(tempOp); // Conversão de char* para int
		
		switch(op){
			case 1:
				operationOne(quantBooks, &quantRented, books, rented);
				break;
			case 2:
				operationTwo(quantRented, rented);
				break;
			case 3:
				operationThree(&quantRented, rented);
				break;
		}
		
		free(tempOp);
	} while (op != 4);

	// Quando for digitado o número 4, a memória é liberada e o programa
	// é finalizado
	printf("Programa finalizado\n");
	
	freeLibrary(quantBooks, books, rented, tempQuantBooks, tempOp);

	return 0;
}
