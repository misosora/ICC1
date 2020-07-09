/*******************************************************************************
 |                        USP-Universidade de São Paulo                        |
 |            ICMC-Instituto de Ciências Matemáticas e de Computação           |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                   2020/1                                    |
 |                                                                             |
 |                        Autor: Gabriela Satie (11892820)                     |
 *******************************************************************************
 Programa que executa um jogo da velha de acordo com comandos digitados
 *******************************************************************************/

#include <stdio.h> // Utilização das funções scanf() e printf()
#include <stdlib.h> // Utilização da função malloc()

// Função que irá alocar o espaço para a matriz
int **alocaMatriz(){
	int **matriz;
	matriz = (int **) malloc(3 * sizeof(int *));

	for (int i = 0; i < 3; i++){
		matriz[i] = (int *) malloc(3 * sizeof(int));
	}

	return matriz;
}

// Função que irá liberar o espaço alocado para a matriz
void liberaMatriz(int **matriz){
	for (int i = 0; i < 3; i++){
		free(matriz[i]);
	}
	
	free(matriz);
	return;
}

// Função que preencherá a matriz com números de 1 a 9
void preencheMatriz(int **matriz){
	
	// Variável aux (auxiliar) que começará no caractere 1
	int aux = '1';
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			matriz[i][j] = aux;
			++aux; // Incremento da variável aux
		}
	}
	
	return;
}

// Função que imprimirá a matriz com a formatação desejada
void imprimeMatriz(int **matriz){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			printf("%c   |", matriz[i][j]);
		}
		printf("\n----+----+-----\n");
	}

	return;
}

// Função que realizará a jogada, ou seja, substituirá o número na matriz
// (na posição lugar, escolhida pelo jogador) pelo dígito do jogador (X ou O)
int fazerJogada(int **matriz, int digito, int lugar){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (matriz[i][j] == lugar){
				matriz[i][j] = digito;
				return 1;
			}
		}
	}
	
	// Se não for encontrado o lugar digitado pelo usuário, a jogada
	// é inválida (ou já está preenchido, ou não está entre 1 e 9)
	printf("Jogada inválida! Escolha outra casa.\n");
	
	return 0;
}

// Função que verificará na horizontal se algum dos jogadores ganhou
int verificarHorizontal(int **matriz, int digito){
	
	// Variável auxiliar (aux), que receberá 0 se não houver ganhador
	// e 1 se houver ganhador (na horizontal)
	int aux;
	
	for (int j = 0; j < 3; j++){
		aux = 1;
		
		for (int i = 0; i < 3; i++){
			if (matriz[i][j] != digito) aux = 0;
		}
		
		if (aux == 1) return 1;	
	}
	
	return 0;
}

// Função que verificará na vertical se algum dos jogadores ganhou
int verificarVertical(int **matriz, int digito){
	
	// Variável auxiliar (aux), que receberá 0 se não houver ganhador
	// e 1 se houver ganhador (na vertical)
	int aux;
	
	for (int i = 0; i < 3; i++){
		aux = 1;
		
		for (int j = 0; j < 3; j++){
			if (matriz[i][j] != digito) aux = 0;
		}
		
		if (aux == 1) return 1;	
	}
	
	return 0;
}

// Função que verificará na diagonal se algum dos jogadores ganhou
int verificarDiagonal(int **matriz, int digito){
	
	// Variável auxiliar (aux), que receberá 1 inicialmente, recebendo 0
	// se não houver ganhador em alguma das diagonais
	int aux = 1;
	
	for (int i = 0; i < 3; i++){
		if (matriz[i][i] != digito) aux = 0;
	}
	
	if (aux == 1) return 1;
	aux = 1;

	for (int i = 0, j = 2; i < 3; i++, j--){
		if (matriz[i][j] != digito) aux = 0;
	}

	return aux;
}

// Função que verificará se houve ganhador em alguma das direções
int verificarJogo(int **matriz, int digito){
	
	// Variável venceu, que receberá o valor 1 se algum dos jogadores
	// tiver ganhado em alguma das direções
	int venceu = 0; 

	if (verificarHorizontal(matriz, digito) == 1) venceu = 1;
	if (verificarVertical(matriz, digito) == 1) venceu = 1;
	if (verificarDiagonal(matriz, digito) == 1) venceu = 1;
	
	// Se venceu for igual 1, algum dos jogadores ganhou e o jogo acaba
	if (venceu == 1){
		imprimeMatriz(matriz);
		printf("Fim do jogo! O jogador %c venceu!\n", digito);
	}

	return venceu;
}

// Função que irá executar o jogo da velha
void rodarJogo(int **matriz){
	
	// Variável que receberá o dígito atual do jogo, alternando entre
	// X e O
	int digitoatual = 'O';
	
	// Variável auxiliar (i)
	int i = -1;

	// Variável que receberá os lugares digitados pelos jogadores
	int lugar;
	
	do{
		// Incremento da variável auxiliar (começa do 0)
		i++;
		
		// Se i chegar a 9, não há mais jogadas (a matriz está completa)
		// e deu velha
		if (i >= 9){
			imprimeMatriz(matriz);
			printf("Deu velha!\n");
			
			return;
		}
		
		imprimeMatriz(matriz);
		
		// Primeira impressão da matriz
		if (i == 0) printf("Jogo da velha!\n");

		// Intercalação dos jogadores
		if (digitoatual == 'X') digitoatual = 'O';
		else digitoatual = 'X';
		
		// Leitura da casa escolhida pelo jogador atual (digitoatual)
		printf("Escolha um número para jogar, jogador %c!\n", digitoatual);
		scanf("%d", &lugar);

		while (fazerJogada(matriz, digitoatual, lugar+'0') == 0){
			// Escanear de novo, pois a jogada foi inválida
			scanf("%d", &lugar);
		}
	} while (verificarJogo(matriz, digitoatual) == 0); // Enquanto ninguém ganhar
	
	return;
}

int main(int argc, char *argv[]){
	
	// Alocação da matriz
	int **matriz = alocaMatriz();
	
	// Preenchimento da matriz com números de 1 a 9
	preencheMatriz(matriz);
	
	// Função que rodará todo o jogo da velha
	rodarJogo(matriz);

	// Liberação do espaço alocado para a matriz
	liberaMatriz(matriz);

	return 0;
}
