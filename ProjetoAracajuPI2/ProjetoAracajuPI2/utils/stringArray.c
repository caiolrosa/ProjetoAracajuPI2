#include <stdio.h>

typedef char string[]; 

int main(void) {
	char *estados[] = {"Rio Grande do Sul", "Santa Catarina", "Paran�", "S�o Paulo", "Mato Grosso do Sul",
	"Rio de Janeiro", "Minas Gerais", "Esp�rito Santo", "Goi�s", "Distrito Federal", "Mato Grosso", "Bahia",
	"Tocantins", "Rond�nia", "Acre", "Amazonas", "Roraima", "Par�", "Amap�", "Maranh�o", "Piau�", "Cear�",
	"Rio Grande do Norte", "Para�ba", "Pernambuco", "Alagoas", "sergipe"};
	char *siglas[] = {"RS", "SC", "PR", "SP", "MS", "RJ", "MG", "ES", "GO", "DF", "MT", "BA", "TO", "RO",
	"AC", "AM", "RR", "PA", "AP", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE"};
	char *capitais[] = {"Porto Alegre", "Florian�polis", "Curitiba", "S�o Paulo", "Campo Grande",
	"Rio de Janeiro", "Belo Horizonte", "Vit�ria", "Goi�nia", "Brasilia", "Cuiab�", "Salvador",
	"Palmas", "Porto Velho", "Rio Branco", "Manaus", "Boa Vista", "Bel�m", "Macap�", "S�o Luis", "Teresina",
	"Fortaleza", "Natal", "Jo�o Pessoa", "Recife", "Macei�", "Aracaju"};
	
	int i = 0;
	for(i = 0; i < 27; i++)
	{
		printf("%s - %s - %s\n", estados[i], siglas[i], capitais[i]);
	}
	
	return 0;
}