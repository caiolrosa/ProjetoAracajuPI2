#pragma region Jogador, Lista e Mapa

//Definir quantas posicoes estao mapeadas por estado
#pragma region DEFINICAO DE TAMANHO DO MAPEAMENTO DOS ESTADOS

#define acreIndexSize 9
#define alagoasIndexSize 3
#define amapaIndexSize 12
#define amazonasIndexSize 87
#define bahiaIndexSize 34
#define cearaIndexSize 13
#define distritoFederalIndexSize 4
#define espiritoSantoIndexSize 7
#define goiasIndexSize 17
#define maranhaoIndexSize 18	
#define matoGrossoIndexSize 53
#define matoGrossoDoSulIndexSize 25
#define minasGeraisIndexSize 39
#define paraIndexSize 86
#define paraibaIndexSize 4
#define paranaIndexSize 14
#define pernambucoIndexSize 7
#define piauiIndexSize 17
#define rioDeJaneiroIndexSize 6
#define rioGrandeDoNorteIndexSize 4
#define rioGrandeDoSulIndexSize 22
#define rondoniaIndexSize 20
#define roraimaIndexSize 20 //diego adicionou
#define santaCatarinaIndexSize 10
#define saoPauloIndexSize 20
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

char *Estados[] = { "RIO GRANDE DO SUL", "SANTA CATARINA", u8"PARANÁ", u8"SÃO PAULO", 
"RIO DE JANEIRO", "MINAS GERAIS", u8"ESPÍRITO SANTO", "MATO GROSSO DO SUL", u8"GOIÁS", "DISTRITO FEDERAL", "MATO GROSSO", 
"TOCANTINS", u8"RONDÔNIA", "ACRE", "AMAZONAS", "RORAIMA", u8"PARÁ", u8"AMAPÁ", "BAHIA", u8"MARANHÃO", u8"PIAUÍ", u8"CEARÁ",
"RIO GRANDE DO NORTE", u8"PARAÍBA", "PERNAMBUCO", "ALAGOAS", "SERGIPE" };

char *Siglas[] = { "RS", "SC", "PR", "SP", "RJ", "MG", "ES", "MS", "GO", "DF", "MT", "TO", "RO",
"AC", "AM", "RR", "PA", "AP", "BA", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE" };

char *Capitais[] = { "PORTO ALEGRE", u8"FLORIANÓPOLIS", "CURITIBA", u8"SÃO PAULO", "RIO DE JANEIRO", "BELO HORIZONTE", u8"VITÓRIA", 
"CAMPO GRANDE", u8"GOIÂNIA", "BRASILIA", u8"CUIABÁ", "PALMAS", "PORTO VELHO", "RIO BRANCO", "MANAUS", "BOA VISTA", u8"BELÉM", 
u8"MACAPÁ", "SALVADOR", u8"SÃO LUIS", "TERESINA", "FORTALEZA", "NATAL", u8"JOÃO PESSOA", "RECIFE", u8"MACEIÓ", "ARACAJU" };

#pragma endregion

