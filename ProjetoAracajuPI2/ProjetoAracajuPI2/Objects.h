#pragma region Jogador, Lista e Mapa

//Definir quantas posicoes estao mapeadas por estado
#pragma region DEFINICAO DE TAMANHO DO MAPEAMENTO DOS ESTADOS

#define acreIndexSize 14
#define alagoasIndexSize 3
#define amapaIndexSize 12
#define amazonasIndexSize 108
#define bahiaIndexSize 34
#define cearaIndexSize 13
#define distritoFederalIndexSize 4
#define espiritoSantoIndexSize 6
#define goiasIndexSize 17
#define maranhaoIndexSize 18	
#define matoGrossoIndexSize 55
#define matoGrossoDoSulIndexSize 26
#define minasGeraisIndexSize 39
#define paraIndexSize 87
#define paraibaIndexSize 4
#define paranaIndexSize 15
#define pernambucoIndexSize 7
#define piauiIndexSize 17
#define rioDeJaneiroIndexSize 6
#define rioGrandeDoNorteIndexSize 4
#define rioGrandeDoSulIndexSize 22
#define rondoniaIndexSize 16
#define roraimaIndexSize 18
#define santaCatarinaIndexSize 10
#define saoPauloIndexSize 22
#define sergipeIndexSize 2
#define tocantinsIndexSize 20

#pragma endregion

typedef struct Jogador {
	char nome[12];
	int acertoPorIndex[27];
	int indexEstadosPerdidos[5];
	int pontos;
	int vidas;
	int acertos;
	int combo;
	int erros;
	bool acertou;
	bool clicouErrado;
	bool clicouEstado;
	bool pronto;
} Jogador;

typedef struct Lista {
	int heightLista; // Altura do ultimo item da lista
	float velocidade; // Velocidade em que caem os estados, capitais e siglas
	int indexAtual;		// Recebe o index atual da palavra sorteada
	int indexAnterior;
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

typedef struct Ranking {
	char *nomesTxt[100];
	int pontosTxt[100];
	int totalLinhas;
} Ranking;

typedef struct ClickIndex {
	int i;
	int j;
}ClickIndex;

typedef struct EstadosPadrao {
	int myIndexPosition;
	ClickIndex index[amazonasIndexSize]; //rever depois
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

char *Estados[] = { "RIO GRANDE DO SUL", "SANTA CATARINA", u8"PARAN�", u8"S�O PAULO", 
"RIO DE JANEIRO", "MINAS GERAIS", u8"ESP�RITO SANTO", "MATO GROSSO DO SUL", u8"GOI�S", "DISTRITO FEDERAL", "MATO GROSSO", 
"TOCANTINS", u8"ROND�NIA", "ACRE", "AMAZONAS", "RORAIMA", u8"PAR�", u8"AMAP�", "BAHIA", u8"MARANH�O", u8"PIAU�", u8"CEAR�",
"RIO GRANDE DO NORTE", u8"PARA�BA", "PERNAMBUCO", "ALAGOAS", "SERGIPE" };

char *Siglas[] = { "RS", "SC", "PR", "SP", "RJ", "MG", "ES", "MS", "GO", "DF", "MT", "TO", "RO",
"AC", "AM", "RR", "PA", "AP", "BA", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE" };

char *Capitais[] = { "PORTO ALEGRE", u8"FLORIAN�POLIS", "CURITIBA", u8"S�O PAULO", "RIO DE JANEIRO", "BELO HORIZONTE", u8"VIT�RIA", 
"CAMPO GRANDE", u8"GOI�NIA", "BRASILIA", u8"CUIAB�", "PALMAS", "PORTO VELHO", "RIO BRANCO", "MANAUS", "BOA VISTA", u8"BEL�M", 
u8"MACAP�", "SALVADOR", u8"S�O LUIS", "TERESINA", "FORTALEZA", "NATAL", u8"JO�O PESSOA", "RECIFE", u8"MACEI�", "ARACAJU" };

#pragma endregion

