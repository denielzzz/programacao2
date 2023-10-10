#include <stdio.h>
#include <string.h>

int main(){
	char string[101], separador [] = "-", *token;
	
	printf("Digite uma string: " );
	scanf("%100[^\n]", string);
	getchar();
	token = strtok(string, separador);
	
	do {
		printf("O token encontrado foi: %s\n", token);
		token = strtok(NULL, separador);
	} while(token);

	return 0;
}