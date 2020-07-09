/*******************************************************************************
 |                        USP-Universidade de São Paulo                        |
 |            ICMC-Instituto de Ciências Matemáticas e de Computação           |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                   2020/1                                    |
 |                                                                             |
 |                        Autor: Gabriela Satie (11892820)                     |
 *******************************************************************************
 Programa que realiza a substituição de palavras em frases
 *******************************************************************************/

#include <stdio.h> // Utilização das funções scanf() e printf()
#include <stdlib.h> // Utilização da função realloc()
#include <string.h> // Utilização das funções strlen() e strncmp()
#include <stdbool.h>

// Função que lê os caracteres digitados
char *readLine(FILE *input) {
	char *string = 0;
	int pos = -1;

	do {
		pos++;
		if (pos % 4096 == 0) {
			int i = (pos / 4096) + 1;
			string = (char *) realloc(string, i * 4096);
		}
		string[pos] = (char) fgetc(input);
	} while (string[pos] != '\n' && string[pos] != EOF);
	
	string[pos] = '\0';

	return string;
}

// Função que separa o input em strings para fins de comparação e substituição da palavra desejada
char **splitString(char *string, int *numWords) {
	int i = 0;
	char **listWords = NULL; // Lista de strings separadas
	char *newWord = NULL;
	
	for (int j = 0; j <= strlen(string); j++) {
		
		// Se chegou ao fim de uma palavra, adiciona ela na lista de strings
		if (string[j] == ' ' || string[j] == '\0') {
			listWords = (char**) realloc(listWords, ((*numWords) + 1) * sizeof(char*));
			newWord = (char*) realloc(newWord, j - i + 1);
			newWord[j-i] = '\0'; // Terminador de string
			listWords[*numWords] = newWord;
			(*numWords)++;
			i = j + 1;
			newWord = NULL;
		} else {
			newWord = (char*) realloc(newWord, j - i + 1);
			newWord[j-i] = string[j];
		}
	}
	
	return listWords;
}

//Função que checa se um caractere é uma pontuação 
bool isPonctuation(char c){
	if (c == '?' || c == '.' || c == '!' || c == ',') return true;
	return false;
}

// Função que substitui as palavras desejadas
void substWord(char **arrayWords, int numWords, char *newWord, char *oldWord){
	int size, oldSize;
	
	oldSize = strlen(oldWord);
	
	for (int i = 0; i < numWords; i++) {
		size = strlen(arrayWords[i]);
		
		// Se o último caractere da palavra é uma pontuação
		if (isPonctuation(arrayWords[i][size-1])) {
			
			// Checa se o tamanho relativo à palavra nova e velha (sem contar a pontuação)
			// é igual, se sim, checa se ambas são iguais
			if ((size - oldSize) == 1 && strncmp(arrayWords[i], oldWord, oldSize) == 0) {
				printf("%s%c", newWord, arrayWords[i][size-1]);
			} else {
				printf("%s", arrayWords[i]);
			}
		
		} else {
			
			// Checa se o tamanho de ambas é igual, se sim, checa se nova string e velha são iguais
			if ((size - oldSize) == 0 && strncmp(arrayWords[i], oldWord, oldSize) == 0) {
				printf("%s", newWord);
			} else {
				printf("%s", arrayWords[i]);
			}
		}
		
		// Evitando adicionar um espaço a mais no final do output
		if (i != numWords - 1) {
			printf(" ");
		}
	}
	
	printf("\n");
}

// Função que irá liberar o espaço alocado para a lista de palavras
void freeLista(char **arrayWords, int numWords){
	for (int i = 0; i < numWords; i++) {
		free(arrayWords[i]);
	}
	
	free(arrayWords);
}

int main(int argc, char *argv[]) {
	char *word, *newWord, *string;
	char **arrayWords;
	int numWords = 0;

	word = readLine(stdin);
	newWord = readLine(stdin);
	string = readLine(stdin);

	arrayWords = splitString(string, &numWords);
	substWord(arrayWords, numWords, newWord, word);

	// Desalocação de toda a memória (heap) utilizada
	free(word);
	free(newWord);
	free(string);
	freeLista(arrayWords, numWords);

	return 0;
}
