/* Programa para encriptar e desencriptar com Cifra de César */

#include <stdio.h> // Utilização das funções scanf() e printf()
#include <string.h> // Utilização da função strlen()
#include <stdlib.h> // Utilização da função malloc()

int main(){
	int escolha, chave;
	char *frase;
	frase = (char *) malloc(100);
	escolha = 0;
	chave = 0;
	
	scanf("%d", &escolha);
	scanf("%d", &chave);
	scanf(" %[^\n]", frase); // Máscara utilizada para ler espaços

	// Switch-case para encriptar(1) ou desencriptar(2)
	switch (escolha){
		case (1):
			// For para ler cada caractere da string (frase)
			for (int i = 0; i < strlen(frase); i++){
				// If para checar se todos os caracteres estão no alfabeto
				if (frase[i] >= 'a' && frase[i] <= 'z'){
					frase[i] += chave; // Somar a chave
					
					// If para voltar ao começo do alfabeto
					if (frase[i] > 'z'){
						frase[i] -= 26;
					}
				}
				// Casos em que há letra maiúscula
				if (frase[i] >= 'A' && frase[i] <= 'Z'){
					frase[i] += chave; // Somar a chave
					
					if (frase[i] > 'Z'){
						frase[i] -= 26;
					}
				}
			}
			break;
		case (2):
			// For para ler cada caractere da string (frase)
			for (int i = 0; i < strlen(frase); i++){
				// If para checar se todos os caracteres estão no alfabeto
				if (frase [i] >= 'a' && frase[i] <= 'z'){
					frase[i] -= chave; // Subtrair a chave
					
					// If para voltar ao final do alfabeto
					if (frase[i] < 'a'){
						frase[i] += 26;
					}
				}
				// Casos em que há letra maiúscula
				if (frase[i] >= 'A' && frase[i] <= 'Z'){
					frase[i] -= chave; // Subtrair a chave
					
					if (frase[i] < 'A'){
						frase[i] += 26;
					}
				}
			}
			break;
	}
	printf("%s\n", frase);

	free(frase);
	return 0;
}
