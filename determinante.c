/*******************************************************************************
 |                        USP-Universidade de São Paulo                        |
 |            ICMC-Instituto de Ciências Matemáticas e de Computação           |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                   2020/1                                    |
 |                                                                             |
 |                        Autor: Gabriela Satie (11892820)                     |
 *******************************************************************************
 Programa que calcula o determinante de matrizes (quadradas) de ordem 1, 2 e 3
 *******************************************************************************/

#include <stdio.h> // Utilização das funções scanf() e printf()
#include <stdlib.h> // Utilização da função malloc()

// Função que irá alocar o espaço para a matriz
int **alocaMatriz(int linhas, int colunas){
	int **matriz;
	matriz = (int **) malloc(linhas * sizeof(int *));

	for (int i = 0; i < linhas; i++){
		matriz[i] = (int *) malloc(colunas * sizeof(int));
	}

	return matriz;
}

// Função que irá liberar o espaço alocado para a matriz
void liberaMatriz(int **matriz, int linhas){
	for (int i = 0; i < linhas; i++){
		free(matriz[i]);
	}
	
	free(matriz);
	return;
}

// Função que irá ler a matriz digitada e registrá-la no espaço alocado
void lerMatriz(int **matriz, int linhas, int colunas){
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
			scanf("%d", &matriz[i][j]);
		}
	}
	
	return;
}

// Função que irá calcular o determinante
int calcDeterminante(int **matriz, int linhas, int colunas){
	
	// Declaração e inicialização da variável det, que receberá o valor
	// final do determinante
	int det = 0;
	
	// Se a ordem da matriz for 1, o determinante é o próprio termo dessa matriz
	if (linhas == 1){
		det = matriz[0][0];
	}
	
	// Se a ordem da matriz for 2, o determinante é a diagonal principal
	// menos a diagonal secundária
	if (linhas == 2){
		det = (matriz[0][0]*matriz[1][1] - matriz[0][1]*matriz[1][0]);
	}

	// Se a ordem da matriz for 3:
	if (linhas == 3){
		
		// Declaração e inicialização das variáveis positiva, que receberá
		// os valores positivos, e negativa, que receberá os negativos
		int positiva = 0, negativa = 0;

		// Declaração e inicialização das variáveis somar, que receberá a soma
		// dos valores positivos, e subtrair, que receberá dos negativos
    	int somar = 0, subtrair = 0;

		for(int i = 0; i < 3; i++){
        	positiva = 1;
        	negativa = 1;

        	// For que percorrerá as linhas da matriz de cima para baixo
			// (para os valores positivos) e de baixo para cima
			// (para os valores negativos)
			for(int j = 0, k = 2; j < 3; j++, k--){

				// Cálculo das multiplicações do determinante de acordo
				// com a fórmula de Laplace
            	positiva *= matriz[j][(i+j) % 3];
            	negativa *= matriz[k][(i+j) % 3];
        	}

        	// A variável somar recebe a soma dos valores positivos
			somar += positiva;
			
			// A variável subtrair recebe a soma dos valores negativos
        	subtrair += negativa;
    	}

		det = somar - subtrair;
	}

	return det;
}

int main(int argc, char *argv[]){
	
	// Declaração e inicialização das variáveis linhas, que receberá o
	// número de linhas, e colunas, que receberá o de colunas
	int linhas = 0, colunas = 0;
	scanf("%d %d", &linhas, &colunas);

	// If que checará se o número de linhas/colunas se encontra dentro
	// do intervalo [1,3]
	if (linhas == colunas){
		if (linhas < 1 || linhas > 3){
			printf("Entradas invalidas!\n");
			return 0;
		}
	// Se o número de linhas e colunas não for igual, não há determinante
	} else {
		printf("A matriz de entrada nao possui determinante!\n");
		return 0;
	}

	// Declaração do ponteiro duplo matriz, que receberá o espaço alocado
	// pela função alocaMatriz()
	int **matriz = alocaMatriz(linhas, colunas);

	// Função que lerá a matriz digitada
	lerMatriz(matriz, linhas, colunas);

	// Declaração da variável det, que receberá o valor final do determinante,
	// calculado pela função calcDeterminante()
	int det = calcDeterminante(matriz, linhas, colunas);
	
	// Impressão do determinante e da ordem da matriz
	printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", det, linhas);

	// Liberação do espaço alocado para a matriz
	liberaMatriz(matriz, linhas);

	return 0;
}
