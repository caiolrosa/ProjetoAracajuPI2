#pragma region Jogador, Lista e Mapa

typedef struct Jogador {
	int pontos;
	int vidas;
} Jogador;

// TODO: Verificar como vamos implementar a lista
typedef struct Lista {
	int heightLista; // Altura do ultimo item da lista
	int velocidade; // Velocidade em que caem os estados, capitais e siglas
	int posicao;
	bool isMaxHeight;
} Lista;

typedef struct Mapa {
	int x;
	int y;
	int width;
	int height;
} Mapa;

#pragma endregion
#pragma region Regiao Sul

// Estados regiao Sul
typedef struct RioGrandeDoSul {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} RioGrandeDoSul;

typedef struct SantaCatarina {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} SantaCatarina;

typedef struct Parana {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Parana;

#pragma endregion
#pragma region Regiao Sudeste

// Estados regiao Sudeste
typedef struct SaoPaulo {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} SaoPaulo;

typedef struct RioDeJaneiro {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} RioDeJaneiro;

typedef struct EspiritoSanto {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} EspiritoSanto;

typedef struct MinasGerais {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} MinasGerais;

#pragma endregion
#pragma region Regiao Centro-Oeste

// Estados regiao Centro-Oeste
typedef struct MatoGrossoDoSul {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} MatoGrossoDoSul;

typedef struct Goias {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Goias;

typedef struct MatoGrosso {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} MatoGrosso;

typedef struct DistritoFederal {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} DistritoFederal;

#pragma endregion
#pragma region Regiao Nordeste

// Estados regiao Nordeste
typedef struct Bahia {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Bahia;

typedef struct Sergipe {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Sergipe;

typedef struct Alagoas {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Alagoas;

typedef struct Pernambuco {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Pernambuco;

typedef struct Paraiba {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Paraiba;

typedef struct RioGrandeDoNorte {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} RioGrandeDoNorte;

typedef struct Ceara {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Ceara;

typedef struct Piaui {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Piaui;

typedef struct Maranhao {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Maranhao;

#pragma endregion
#pragma region Regiao Norte

// Estados regiao Norte
typedef struct Tocantins {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Tocantins;

typedef struct Para {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Para;

typedef struct Amapa {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Amapa;

typedef struct Roraima {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Roraima;

typedef struct Amazonas {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Amazonas;

typedef struct Rondonia {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Rondonia;

typedef struct Acre {
	char *nome;
	char *capital;
	int boundX;
	int boundY;
} Acre;

#pragma endregion
#pragma region Listas

char *Estados[] = { "Rio Grande do Sul", "Santa Catarina", u8"Paran�", u8"S�o Paulo", "Mato Grosso do Sul",
"Rio de Janeiro", "Minas Gerais", u8"Esp�rito Santo", u8"Goi�s", "Distrito Federal", "Mato Grosso", "Bahia",
"Tocantins", u8"Rond�nia", "Acre", "Amazonas", "Roraima", u8"Par�", u8"Amap�", u8"Maranh�o", u8"Piau�", u8"Cear�",
"Rio Grande do Norte", u8"Para�ba", "Pernambuco", "Alagoas", "Sergipe" };

char *Siglas[] = { "RS", "SC", "PR", "SP", "MS", "RJ", "MG", "ES", "GO", "DF", "MT", "BA", "TO", "RO",
"AC", "AM", "RR", "PA", "AP", "MA", "PI", "CE", "RN", "PB", "PE", "AL", "SE" };

char *Capitais[] = { "Porto Alegre", "Florian�polis", "Curitiba", u8"S�o Paulo", "Campo Grande",
"Rio de Janeiro", "Belo Horizonte", u8"Vit�ria", u8"Goi�nia", "Brasilia", u8"Cuiab�", "Salvador",
"Palmas", "Porto Velho", "Rio Branco", "Manaus", "Boa Vista", u8"Bel�m", u8"Macap�", u8"S�o Luis", "Teresina",
"Fortaleza", "Natal", u8"Jo�o Pessoa", "Recife", u8"Macei�", "Aracaju" };

#pragma endregion