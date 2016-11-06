#pragma region Jogador, Lista e Mapa

//Definir quantas posicoes estao mapeadas por estado
#pragma region DEFINICAO DE TAMANHO DO MAPEAMENTO DOS ESTADOS

#define acreIndexSize 9
#define alagoasIndexSize 3
#define amapaIndexSize 0
#define amazonasIndexSize 0
#define bahiaIndexSize 34
#define cearaIndexSize 12
#define distritoFederalIndexSize 0
#define espiritoSantoIndexSize 3
#define goiasIndexSize 0
#define maranhaoIndexSize 18	
#define matoGrossoIndexSize 0
#define matoGrossoDoSulIndexSize 0
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
} Jogador;

typedef struct Lista {
	int heightLista; // Altura do ultimo item da lista
	int velocidade; // Velocidade em que caem os estados, capitais e siglas
	int randomNumber;	// Usado para escolher aleatoriamente um item da lista
	char *palavraAtual;	// Recebe o texto atual 
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

#pragma region Listas

char *Estados[] = { "Rio Grande do Sul", "Santa Catarina", u8"Paran�", u8"S�o Paulo", "Mato Grosso do Sul",
"Rio de Janeiro", "Minas Gerais", u8"Esp�rito Santo", u8"Goi�s", "Distrito Federal", "Mato Grosso", "Bahia",
"Tocantins", u8"Rond�nia", "Acre", "Amazonas", "Roraima", u8"Par�", u8"Amap�", u8"Maranh�o", u8"Piau�", u8"Cear�",
"Rio Grande do Norte", u8"Para�ba", "Pernambuco", "Alagoas", "Sergipe" };

char *Siglas[] = { "RS", "SC", "PR", "SP", "MS", "RJ", "MG", "ES", "GO", "DF", "MT", "BA", "TO", "RO",
"AC", "AM", "RR", "PA", "AP", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE" };

char *Capitais[] = { "Porto Alegre", u8"Florian�polis", "Curitiba", u8"S�o Paulo", "Campo Grande",
"Rio de Janeiro", "Belo Horizonte", u8"Vit�ria", u8"Goi�nia", "Brasilia", u8"Cuiab�", "Salvador",
"Palmas", "Porto Velho", "Rio Branco", "Manaus", "Boa Vista", u8"Bel�m", u8"Macap�", u8"S�o Luis", "Teresina",
"Fortaleza", "Natal", u8"Jo�o Pessoa", "Recife", u8"Macei�", "Aracaju" };

#pragma endregion