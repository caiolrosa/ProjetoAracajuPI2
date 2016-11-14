#pragma region Jogador, Lista e Mapa

//Definir quantas posicoes estao mapeadas por estado
#pragma region DEFINICAO DE TAMANHO DO MAPEAMENTO DOS ESTADOS

#define acreIndexSize 9
#define alagoasIndexSize 3
#define amapaIndexSize 0
#define amazonasIndexSize 0
#define bahiaIndexSize 34
#define cearaIndexSize 12
#define distritoFederalIndexSize 4
#define espiritoSantoIndexSize 3
#define goiasIndexSize 15
#define maranhaoIndexSize 18	
#define matoGrossoIndexSize 0
#define matoGrossoDoSulIndexSize 25
#define minasGeraisIndexSize 37
#define paraIndexSize 0
#define paraibaIndexSize 4
#define paranaIndexSize 15
#define pernambucoIndexSize 7
#define piauiIndexSize 16
#define rioDeJaneiroIndexSize 3
#define rioGrandeDoNorteIndexSize 3
#define rioGrandeDoSulIndexSize 23
#define rondoniaIndexSize 0
#define santaCatarinaIndexSize 8
#define saoPauloIndexSize 14
#define sergipeIndexSize 2
#define tocantinsIndexSize 0

#pragma endregion

typedef struct Jogador {
	int pontos;
	int vidas;
	int acertos;
	int erros;
	bool acertou;
	bool jogando;
	bool tutorial;
} Jogador;

typedef struct Lista {
	int heightLista; // Altura do ultimo item da lista
	int velocidade; // Velocidade em que caem os estados, capitais e siglas
	int randomNumber;	// Usado para escolher aleatoriamente um item da lista
	int indexAtual;		// Recebe o index atual da palavra sorteada
	char *palavraAtual;	// Recebe o texto atual
	ALLEGRO_COLOR cor; // Cor da palavra caindo na lista
	bool isMaxHeight;	// Verifica se a palavra chegou na altura maxima
} Lista;

typedef struct Mapa {
	int x;
	int y;
	int width;
	int height;
} Mapa;

typedef struct ClickIndex {
	int i;
	int j;
}ClickIndex;

typedef struct EstadosPadrao {
	int myIndexPosition;
	ClickIndex index[bahiaIndexSize]; //rever depois
} EstadosPadrao;

#pragma endregion

#pragma region Botoes
typedef struct BotaoJogar
{
	int boundXInicio;
	int boundXFinal;

	int boundYInicio;
	int boundYFinal;

}BotaoJogar;

typedef struct BotaoTutorial
{
	int boundXInicio;
	int boundXFinal;

	int boundYInicio;
	int boundYFinal;

}BotaoTutorial;
#pragma endregion

#pragma region Listas

char *Estados[] = { "Rio Grande do Sul", "Santa Catarina", u8"Paraná", u8"São Paulo", 
"Rio de Janeiro", "Minas Gerais", u8"Espírito Santo", "Mato Grosso do Sul", u8"Goiás", "Distrito Federal", "Mato Grosso", 
"Tocantins", u8"Rondônia", "Acre", "Amazonas", "Roraima", u8"Pará", u8"Amapá", "Bahia", u8"Maranhão", u8"Piauí", u8"Ceará",
"Rio Grande do Norte", u8"Paraíba", "Pernambuco", "Alagoas", "Sergipe" };

char *Siglas[] = { "RS", "SC", "PR", "SP", "RJ", "MG", "ES", "MS", "GO", "DF", "MT", "TO", "RO",
"AC", "AM", "RR", "PA", "AP", "BA", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE" };

char *Capitais[] = { "Porto Alegre", u8"Florianópolis", "Curitiba", u8"São Paulo", "Rio de Janeiro", "Belo Horizonte", u8"Vitória", 
"Campo Grande", u8"Goiânia", "Brasilia", u8"Cuiabá", "Palmas", "Porto Velho", "Rio Branco", "Manaus", "Boa Vista", u8"Belém", 
u8"Macapá", "Salvador", u8"São Luis", "Teresina","Fortaleza", "Natal", u8"João Pessoa", "Recife", u8"Maceió", "Aracaju" };

#pragma endregion

