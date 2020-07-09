/*******************************************************************************
 |                        USP-Universidade de São Paulo                        |
 |            ICMC-Instituto de Ciências Matemáticas e de Computação           |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                   2020/1                                    |
 |                                                                             |
 |                        Autor: Gabriela Satie (11892820)                     |
 *******************************************************************************
 Prova de ICC1
 Professor: Rodrigo Mello
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define READLINE_BUFFER 4096

// Função que lerá os caracteres digitados e encontrados nos arquivos
char *readLine(FILE *stream){
	char *string = 0;
	int i = 0;

	do{
		if(i % READLINE_BUFFER == 0){
			string = (char *) realloc(string,(i / READLINE_BUFFER + 1)*READLINE_BUFFER);
		}
		string[i] = fgetc(stream);
		i++;
	} while(string[i-1] != '\n' && string[i-1] != EOF);
	
	if(i >= 2 && string[i-2] == '\r'){ // Caso encontre um '\r', substitui por '\0'
		string[i-2] = '\0';
		string = (char *) realloc(string, i-1);
	} else {
		string[i-1] = '\0';
	}

	return string;
}

// Função que contará o número de palavras no arquivo e imprimirá
// a quantidade encontrada
void findNumberOfWords(FILE *fp){
	char character = fgetc(fp);
	int numberOfWords = 0;

	do{ // Se encontrar um espaço ou '\n', significa que é uma palavra nova
		if(character == ' ' || character == '\n'){
			numberOfWords++;
		}
		character = fgetc(fp);
	} while(character != EOF);
	
	printf("%d\n", numberOfWords);

	return;
}

// Função que encontrará a menor palavra no arquivo e a imprimirá
void findShortestWord(FILE *fp){
	rewind(fp);
	
	char *tempString = readLine(fp);
	char *shortestWord = (char *) malloc(50*sizeof(char));
	
	// Assumindo a primeira palavra do arquivo como a menor para comparação
	strcpy(shortestWord, tempString);
	free(tempString);

	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Comparação do tamanho das strings, guardando a menor (não nula)
		if(strlen(tempString) < strlen(shortestWord) && tempString[0] != '\0'){
			strcpy(shortestWord, tempString);
		}
		
		free(tempString);
	}

	printf("%s\n", shortestWord);
	free(shortestWord);
	
	return;
}

// Função que encontrará a maior palavra do arquivo e a imprimirá
void findLongestWord(FILE *fp){
	rewind(fp);
	
	char *tempString = readLine(fp);
	char *longestWord = (char *) malloc(50*sizeof(char));
	
	// Assumindo a primeira palavra do arquivo como a maior para comparação
	strcpy(longestWord, tempString);
	free(tempString);

	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Comparação do tamanho das strings, guardando a maior
		if(strlen(tempString) > strlen(longestWord)){
			strcpy(longestWord, tempString);
		}
		
		free(tempString);
	}

	printf("%s\n", longestWord);
	free(longestWord);
	
	return;
}

// Função que encontrará e contará ocorrências do primeiro padrão,
// imprimindo a quantidade encontrada
void findFirstPatternOccurrences(FILE *fp, char *firstPattern){
	rewind(fp);

	char *tempString;
	int firstPatternOccurrences = 0;
	
	// Criação do padrão
	regex_t regex;
	int pattern = regcomp(&regex, firstPattern, REG_EXTENDED);

	while(!feof(fp)){
		tempString = readLine(fp);
	
		// Comparação do padrão
		pattern = regexec(&regex, tempString, 0, NULL, 0);
		if(!pattern){
			firstPatternOccurrences++;
		}

		free(tempString);
	}

	printf("%d\n", firstPatternOccurrences);
	regfree(&regex);

	return;
}

// Função que verificará se a palavra é um palíndromo
int isPalindrome(char *tempString){
	for(int i = 0; i < strlen(tempString); i++){	
		// Se for diferente em algum caso, retorna 0
		if(tempString[i] != tempString[strlen(tempString)-i-1]){
			return 0;
		}
	}
	// Se não, é um palíndromo
	return 1;
}

// Função que encontrará e contará o número de palíndromos,
// imprimindo a quantidade encontrada
void findNumberOfPalindromes(FILE *fp){
	rewind(fp);
	
	char *tempString;
	int numberOfPalindromes = 0;

	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Checagem de palíndromos utilizando a função isPalindrome(),
		// descartando strings nulas
		if(isPalindrome(tempString) && tempString[0] != '\0'){
			numberOfPalindromes++;
		}

		free(tempString);
	}

	printf("%d\n", numberOfPalindromes);

	return;
}

// Função que encontrará ocorrências do segundo padrão e imprimirá
// a maior destas
void findLongestSecondPatternWord(FILE *fp, char *secondPattern){
	rewind(fp);

	char *tempString = readLine(fp);
	char *longestSecondPatternWord = (char *) malloc(50*sizeof(char));
	
	// Assumindo a primeira palavra do arquivo como a maior para comparação
	strcpy(longestSecondPatternWord, tempString);
	free(tempString);

	// Criação do padrão
	regex_t regex;
	int pattern = regcomp(&regex, secondPattern, REG_EXTENDED);

	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Comparação do padrão e do tamanho das strings, guardando a maior
		pattern = regexec(&regex, tempString, 0, NULL, 0);
		if(!pattern && strlen(tempString) > strlen(longestSecondPatternWord)){
			strcpy(longestSecondPatternWord, tempString);
		}
		
		free(tempString);
	}

	printf("%s\n", longestSecondPatternWord);
	free(longestSecondPatternWord);
	regfree(&regex);

	return;
}

// Comparador utilizado na função qsort()
int comparator(const void *a, const void *b){
	const char **ia = (const char **) a;
	const char **ib = (const char **) b;

	return strcmp(*ia, *ib);
}

// Função que encontrará e contará ocorrências do terceiro padrão, imprimindo-as
void findThirdPatternWords(FILE *fp, char *thirdPattern){
	rewind(fp);

	char *tempString;
	int numberOfWords = 0;

	// Criação do padrão
	regex_t regex;
	int pattern = regcomp(&regex, thirdPattern, REG_EXTENDED);

	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Comparação do padrão
		pattern = regexec(&regex, tempString, 0, NULL, 0);
		if(!pattern && tempString[0] != '\0'){
			numberOfWords++;
		}

		free(tempString);
	}
	
	// Matriz que guardará as strings com o terceiro padrão
	char **thirdPatternWords = (char **) malloc(numberOfWords*sizeof(char *));
	
	int i = 0;

	rewind(fp);
	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Comparação do padrão, adicionando a string na matriz se for encontrado e
		// descartando strings nulas
		pattern = regexec(&regex, tempString, 0, NULL, 0);
		if(!pattern && tempString[0] != '\0'){
			thirdPatternWords[i++] = tempString;
		} else {
			free(tempString);
		}
	}
	
	// Ordenação alfabética
	qsort(thirdPatternWords, numberOfWords, sizeof(char *), comparator);

	for(int j = 0; j < numberOfWords; j++){
		printf("%s\n", thirdPatternWords[j]);
		free(thirdPatternWords[j]);
	}
	free(thirdPatternWords);
	regfree(&regex);

	return;
}

// Função que alocará uma matriz nula
int **allocArray(int rows, int columns){
	int **array = (int **) calloc(rows, sizeof(int *));

	for (int i = 0; i < rows; i++){
		array[i] = (int *) calloc(columns, sizeof(int));
	}

	return array;
}

// Função que liberará a matriz alocada
void freeArray(int **array, int rows){
	for (int i = 0; i < rows; i++){
		free(array[i]);
	}
	free(array);
	
	return;
}

// Função que comparará strings, avaliando seu grau de similaridade
int compareStrings(char *tempString, char *wordW){	
	int wordWLen = strlen(wordW);
	int tempStringLen = strlen(tempString);

	int **array = allocArray(wordWLen, tempStringLen);
	
	int similarity = 0;

	// Percorrendo todos os caracteres de ambas strings
	for(int i = 0; i < wordWLen; i++){
		for(int j = 0; j < tempStringLen; j++){
			if(wordW[i] == tempString[j]){
				if(i == 0 || j == 0){ // Tratando os casos das extremidades
					array[i][j] = 1;
				} else {
					array[i][j] = array[i-1][j-1] + 1; // Soma 1 ao valor da diagonal anterior
				}
			} else if(wordW[i] != tempString[j] && i != 0 && j != 0){
				array[i][j] = array[i-1][j-1]; // Cópia da diagonal anterior
			}
			
			if(array[i][j] > similarity){
				similarity = array[i][j]; // Atualização da similaridade
			}
		}
	}

	freeArray(array, wordWLen);
	return similarity;
}

// Função que encontrará e imprimirá a palavra mais próxima da palavra W
void findClosestWordToW(FILE *fp, char *wordW){
	rewind(fp);
	
	char *tempString;
	char *closestWordToW = (char *) malloc(50*sizeof(char));

	int tempSimilarity = 0;
	int highestSimilarity = 0;

	while(!feof(fp)){
		tempString = readLine(fp);
		
		// Encontrará a similaridade entre as duas strings,
		// utilizando a função compareStrings()
		tempSimilarity = compareStrings(tempString, wordW);
		
		// Se a similaridade for maior que a anterior, atualiza 
		// a maior similaridade e a string mais parecida
		if(tempSimilarity > highestSimilarity){
			strcpy(closestWordToW, tempString);
			highestSimilarity = tempSimilarity;
		} else if(tempSimilarity == highestSimilarity){
			// Se a similaridade for igual, preza pela menor string
			if(strlen(tempString) < strlen(closestWordToW)){
				strcpy(closestWordToW, tempString);
			}
		}
		
		free(tempString);
	}

	printf("%s\n", closestWordToW);
	free(closestWordToW);

	return;
}

// Função que desalocará o espaço para as variáveis principais
void freeProgram(char *fileName, char *firstPattern, char *secondPattern, char *thirdPattern, char *wordW){
	free(fileName);
	free(firstPattern);
	free(secondPattern);
	free(thirdPattern);
	free(wordW);

	return;
}

int main(int argc, char *argv[]){
	// Leitura das variáveis principais
	char *fileName = readLine(stdin);
	char *firstPattern = readLine(stdin);
	char *secondPattern = readLine(stdin);
	char *thirdPattern = readLine(stdin);
	char *wordW = readLine(stdin);
	
	// Abertura do arquivo
	FILE *fp;
	fp = fopen(fileName, "r");
	
	// Chamada das funções principais
	findNumberOfWords(fp);
	findShortestWord(fp);
	findLongestWord(fp);
	findFirstPatternOccurrences(fp, firstPattern);
	findNumberOfPalindromes(fp);
	findLongestSecondPatternWord(fp, secondPattern);
	findThirdPatternWords(fp, thirdPattern);
	findClosestWordToW(fp, wordW);

	// Desalocação das variáveis principais e fechamento do arquivo
	freeProgram(fileName, firstPattern, secondPattern, thirdPattern, wordW);	
	fclose(fp);

	return 0;
}
