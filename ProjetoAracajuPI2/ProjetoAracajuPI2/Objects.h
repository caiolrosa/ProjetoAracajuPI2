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

char *Estados[] = { "Rio Grande do Sul", "Santa Catarina", u8"Paran�", u8"S�o Paulo", 
"Rio de Janeiro", "Minas Gerais", u8"Esp�rito Santo", "Mato Grosso do Sul", u8"Goi�s", "Distrito Federal", "Mato Grosso", 
"Tocantins", u8"Rond�nia", "Acre", "Amazonas", "Roraima", u8"Par�", u8"Amap�", "Bahia", u8"Maranh�o", u8"Piau�", u8"Cear�",
"Rio Grande do Norte", u8"Para�ba", "Pernambuco", "Alagoas", "Sergipe" };

char *Siglas[] = { "RS", "SC", "PR", "SP", "RJ", "MG", "ES", "MS", "GO", "DF", "MT", "TO", "RO",
"AC", "AM", "RR", "PA", "AP", "BA", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE" };

char *Capitais[] = { "Porto Alegre", u8"Florian�polis", "Curitiba", u8"S�o Paulo", "Rio de Janeiro", "Belo Horizonte", u8"Vit�ria", 
"Campo Grande", u8"Goi�nia", "Brasilia", u8"Cuiab�", "Palmas", "Porto Velho", "Rio Branco", "Manaus", "Boa Vista", u8"Bel�m", 
u8"Macap�", "Salvador", u8"S�o Luis", "Teresina","Fortaleza", "Natal", u8"Jo�o Pessoa", "Recife", u8"Macei�", "Aracaju" };

#pragma endregion

