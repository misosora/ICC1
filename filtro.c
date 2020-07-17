/*************************************************************************************************
(                _                USP-Universidade de São Paulo                 _                )
(    __   ___.--'_`.  ICMC-Instituto de Ciências Matemáticas e de Computação  .'_`--.___   __    )
(   ( _`.'. -   'o` ) ====================================================== ( 'o`   - .`.'_ )   )
(   _\.'_'      _.-'           Bacharelado em Ciências de Computação          `-._      `_`./_   )
(  ( \`. )    //\`                            2020/1                            '/\\    ( .'/ )  )
(   \_`-'`---'\\__, ========================================================== ,__//`---'`-'_/   )
(    \`        `-\           __    __                                           /-´        ´/    )
(     `                     ( 0)__( 0)  Gabriela Satie Faria Nishimi                       ´     )
(                           /   ''   \     ____________________                                  )
(                          ( ´´  3 ´´ )  < Número USP: 11892820)                                 )
(                           \        /                                                           )
(                           /___>o<__\                                                           )
(                           uuu    uuu                                                           )
( Programa: Filtro de Foto                                                                       )
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READLINE_BUFFER 4096

// Função que lerá os caracteres digitados pelo usuário
char *readLine(FILE *stream) {
	char *string = NULL;
	int i = 0;

	do {
		if (i % READLINE_BUFFER == 0) {
			string = (char *) realloc(string, (i / READLINE_BUFFER + 1)*READLINE_BUFFER);
		}
		string[i] = fgetc(stream);
		i++;
	} while (string[i-1] != '\n' && string[i-1] != EOF);

	if (i >= 2 && string[i-2] == '\r') {
		string[i-2] = '\0';
		string = (char *) realloc(string, i-1);
	} else {
		string[i-1] = '\0';
		string = (char *) realloc(string, i);
	}

	return string;
}

// Função que checará a existência do arquivo e o seu tipo
int checkFile(FILE *fp, char *file){
	char *format = strrchr(file, '.');

	if(fp == NULL){
		printf("Erro no arquivo\n");
		return 0;
	}
	
	// Leitura da assinatura do arquivo
	char signature[3] = {0};
	fread(signature, 2, 1, fp);
	signature[2] = '\0';
	
	if(strcmp(".bmp", format) || strcmp("BM", signature)){
		printf("Arquivo nao eh do formato BMP\n");
		fclose(fp);
		return 0;
	}
	
	return 1;
}

// Função que renomeará o novo arquivo de acordo com a opção escolhida
void renameFile(char *file, char *newFile, int op){
	char *token = strtok(file, ".");
	strcpy(newFile, token);

	if(op == 1){
		strcat(newFile, "Negativo.bmp");
		newFile[strlen(newFile)+1] = '\0';
	}else{
		strcat(newFile, "PretoBranco.bmp");
		newFile[strlen(newFile)+1] = '\0';
	}
	
	return;
}

// Função que copiará o cabeçalho do arquivo original no novo arquivo
void copyFile(FILE *fp, FILE *new, int **palette){
	rewind(fp);

	char signature[2] = {0};
	fread(signature, 2, 1, fp);
	fwrite(signature, 1, 2, new);

	int buffer = 0;
	for(int i = 0; i < 52; i++){
		fread(&buffer, 1, 1, fp);
		fwrite(&buffer, 1, 1, new);
	}
	
	// Leitura da paleta de cores em uma matriz auxiliar
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 4; j++){
			fread(&buffer, 1, 1, fp);
			palette[i][j] = buffer;
		}
	}
	
	return;
}

// Função que imprimirá o cabeçalho original e a paleta de cores respectiva
void printOriginal(FILE *fp, int *height, int *width){
	rewind(fp);
	
	char signature[3] = {0};
	fread(signature, 2, 1, fp);
	signature[2] = '\0';
	printf("CABECALHO:\n");
	printf("Iniciais: %s\n", signature);
	
	int buffer = 0;
	fread(&buffer, 4, 1, fp);
	printf("Tamanho do arquivo: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Reservado: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Deslocamento, em bytes, para o inicio da area de dados: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Tamanho em bytes do segundo cabecalho: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Resolucao: %d x ", buffer);
	*width = buffer; // Salvar o tamanho da largura
	fread(&buffer, 4, 1, fp);
	printf("%d\n", buffer);
	*height = buffer; // Salvar o tamanho da altura
	fread(&buffer, 2, 1, fp);
	printf("Numero de planos: %d\n", buffer);
	fread(&buffer, 2, 1, fp);
	printf("Bits por pixel: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Compressao usada: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Tamanho imagem: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Resolucao horizontal: %d pixel por metro\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Resolucao Vertical: %d pixel por metro\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Numero de cores usadas: %d\n", buffer);
	fread(&buffer, 4, 1, fp);
	printf("Numero de cores importantes: %d\n", buffer);

	int red = 0, green = 0, blue = 0;
	printf("PALETA ORIGINAL:\n");
	for(int i = 0; i < 256; i++){
		fread(&blue, 1, 1, fp);
		fread(&green, 1, 1, fp);
		fread(&red, 1, 1, fp);
		fread(&buffer, 1, 1, fp);

		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, red, green, blue);
	}

	return;
}

// Função que copiará a matriz original para o novo arquivo e
// imprimirá a soma das linhas
void lineSum(FILE *fp, FILE *new, int height, int width){
	int trash = (width%4 != 0) ? (4 - width%4) : 0; // Quantificação do lixo no arquivo

	int **matrix = (int **) calloc(height, sizeof(int *));
	for(int i = 0; i < height; i++){
		matrix[i] = (int *) calloc(width+trash, sizeof(int));
	}

	for(int i = height-1; i >= 0; i--){
		for(int j = 0; j < width+trash; j++){
			fread(&matrix[i][j], 1, 1, fp);
			fwrite(&matrix[i][j], 1, 1, new);
		}
	}

	long long sum;
	for(int i = 0; i < height; i++){
		sum = 0;
		
		for(int j = 0; j < width; j++){
			sum += matrix[i][j];
		}
		sum -= trash; // Subtração da quantidade de lixo

		printf("Soma linha %d: %lld\n", i, sum);
		free(matrix[i]);
	}

	free(matrix);
	return;
}

// Função que transformará a imagem original em negativa
void negativePhoto(FILE *fp, FILE *new, int **palette){
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 4; j++){
			palette[i][j] -= 255;
			if(j == 4){
				palette[i][j] = 0; // Caractere reservado
			}
			if(palette[i][j] < 0){
				palette[i][j] *= -1; // Tratamento de casos negativos
			}
			fwrite(&palette[i][j], 1, 1, new);
		}
	}
	
	int height, width;
	printOriginal(fp, &height, &width);

	printf("PALETA NOVA:\n");
	for(int i = 0; i < 256; i++){
		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, palette[i][2], palette[i][1], palette[i][0]);
	}
	lineSum(fp, new, height, width);

	return;
}

// Função que transformará a imagem original em preta e branca
void blackWhitePhoto(FILE *fp, FILE *new, int **palette){
	for(int i = 0; i < 256; i++){
		palette[i][0] = (palette[i][0]+palette[i][1]+palette[i][2])/3; // Média das cores
		palette[i][1] = palette[i][0];
		palette[i][2] = palette[i][0];
		
		for(int j = 0; j < 4; j++){
			fwrite(&palette[i][j], 1, 1, new);
		}
	}
	
	int height, width;
	printOriginal(fp, &height, &width);

	printf("PALETA NOVA:\n");
	for(int i = 0; i < 256; i++){
		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, palette[i][2], palette[i][1], palette[i][0]);
	}
	lineSum(fp, new, height, width);

	return;
}

void freeProgram(char *file, char *option, char *newFile, int **palette){
	free(file);
	free(option);
	free(newFile);
	for(int i = 0; i < 256; i++){
		free(palette[i]);
	}
	free(palette);

	return;
}

int main(int argc, char *argv[]){
	char *file = readLine(stdin); // Nome do arquivo original
	char *option = readLine(stdin); // Opção escolhida pelo usuário
	int op = atoi(option);
	
	FILE *fp;
	fp = fopen(file, "rb");

	char *newFile = (char *) malloc((strlen(file)+16)*sizeof(char)); // Nome do arquivo novo
	int **palette = (int **) malloc(256*sizeof(int *)); // Paleta original
	for(int i = 0; i < 256; i++){
		palette[i] = (int *) malloc(4*sizeof(int));
	}

	if(checkFile(fp, file)){
		renameFile(file, newFile, op);
		
		FILE *new;
		new = fopen(newFile, "wb");
		copyFile(fp, new, palette);

		switch(op){
			case 1:
				negativePhoto(fp, new, palette);
				break;
			case 2:
				blackWhitePhoto(fp, new, palette);
				break;
		}
		printf("%s\n", newFile);
		fclose(new);
		fclose(fp);
	}

	freeProgram(file, option, newFile, palette);
	return 0;
}
