#include <stdio.h>

typedef char string[]; 

int main(void) {
	char *estados[] = {"Rio Grande do Sul", "Santa Catarina", "Paraná", "São Paulo", "Mato Grosso do Sul",
	"Rio de Janeiro", "Minas Gerais", "Espírito Santo", "Goiás", "Distrito Federal", "Mato Grosso", "Bahia",
	"Tocantins", "Rondônia", "Acre", "Amazonas", "Roraima", "Pará", "Amapá", "Maranhão", "Piauí", "Ceará",
	"Rio Grande do Norte", "Paraíba", "Pernambuco", "Alagoas", "sergipe"};
	char *siglas[] = {"RS", "SC", "PR", "SP", "MS", "RJ", "MG", "ES", "GO", "DF", "MT", "BA", "TO", "RO",
	"AC", "AM", "RR", "PA", "AP", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE"};
	char *capitais[] = {"Porto Alegre", "Florianópolis", "Curitiba", "São Paulo", "Campo Grande",
	"Rio de Janeiro", "Belo Horizonte", "Vitória", "Goiânia", "Brasilia", "Cuiabá", "Salvador",
	"Palmas", "Porto Velho", "Rio Branco", "Manaus", "Boa Vista", "Belém", "Macapá", "São Luis", "Teresina",
	"Fortaleza", "Natal", "João Pessoa", "Recife", "Maceió", "Aracaju"};
	
	int i = 0;
	for(i = 0; i < 27; i++)
	{
		printf("%s - %s - %s\n", estados[i], siglas[i], capitais[i]);
	}
	
	return 0;
}