/*******************************************************************************
 |                        USP-Universidade de São Paulo                        |
 |            ICMC-Instituto de Ciências Matemáticas e de Computação           |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                   2020/1                                    |
 |                                                                             |
 |                        Autor: Gabriela Satie (11892820)                     |
 *******************************************************************************
 Programa que realiza a impressão de dados em um gráfico de barras horizontais
 *******************************************************************************/

 #include <stdio.h> // Utilização das funções scanf() e printf()
 #include <stdlib.h> // Utilização da função malloc()

 int main(int argc, char *argv[]){
 	
	// Declaração e inicialização das variáveis barras, que guardará o número
	// de barras, e qtd, que guardará a quantidade de valores
	int barras = 0, qtd = 0;
	scanf("%d %d", &barras, &qtd);

	// Declaração e inicialização da variável valores, que registrará os
	// valores digitados pelo usuário
	int valores = 0;

	// Declaração do ponteiro frequencia, que irá apontar para uma região da
	// memória Heap com 4 bytes (int) vezes o tanto de barras e guadará
	// a frequência de cada valor digitado
	int *frequencia;
	frequencia = (int *) malloc(sizeof(int) * barras);

	// For que irá ler os valores digitados e registrar sua frequência,
	// somando 1 a cada aparição no index correspondente ao seu valor
	for (int i = 0; i < qtd; i++){
		scanf("%d", &valores);
		frequencia[valores]++;
	}
	
	// For que irá imprimir as barras em ordem crescente
	for (int j = 0; j < barras; j++){
		printf("%d - ", j);

		// For que irá imprimir o caractere # de acordo com a frequência
		// do valor
		for (int k = 0; k < frequencia[j]; k++){
			printf("#");
		}
		
		// Impressão da quebra de linha após o fim da impressão da barra de
		// cada valor
		printf("\n");
	}

	return 0;
 }
