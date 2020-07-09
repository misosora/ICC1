/* Programa para transformar um binário em decimal */

#include <stdio.h> // Utlização das funções printf() e scanf()
#include <math.h> // Utilização da função pow()
#include <string.h> // Utilização da função strlen()
#include <stdlib.h> // Utilização da função malloc()

int main(){
	char *binario;
	binario = (char *) malloc(30);
	int i, decimal;
	i = 0;
	decimal = 0;

	scanf("%s", binario);
	
	// O for será utlizado para ler a string (binário) de trás para frente
	for (i = strlen(binario) - 1; i >= 0; i--){
		if (binario[i] == '1'){ // Se o caractere 1 for lido
			// O decimal será atualizado de acordo com a posição
			// Desse caractere na string
			decimal += pow(2, (strlen(binario) - 1 - i));
		}
	}
	printf("%d\n", decimal);
	free(binario);
	return 0;
}
