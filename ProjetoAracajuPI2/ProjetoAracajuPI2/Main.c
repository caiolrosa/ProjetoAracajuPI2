#pragma region Include

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "Objects.h"

#pragma endregion

enum TELAS{MENU, CREDITS, GAME, PAUSE, ENDGAME}currentScreen; //Enum define em qual tela o jogo esta

// Variaveis globais
const int WIDTH = 1280;
const int HEIGHT = 720;
const int WIDTHMAPA = 650;
const int HEIGHTMAPA = 650;
const int HEIGHTCINZA = 650;
const int WIDTHCINZA = 650;

bool finished = false;
bool isGameOver = false;
bool isInMenu = true;
bool redraw = true;
bool musicaTocando = true;
bool jogadorJogando = false;
bool clicouRanking = false;
bool clicouPause = false;
bool clicouTutorial = false;
bool clicouCreditos = false;
bool chegouFinalLista = false;
bool mostraFeedback = false;
bool perdeuEstado = false;
bool digitouNome = false;
bool salvouPontuacao = false;

// Variaveis globais Allegro
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *piscaTimer = NULL;
ALLEGRO_COLOR WHITE;
ALLEGRO_COLOR BLACK;
ALLEGRO_COLOR BLUE;
ALLEGRO_COLOR GREEN;
ALLEGRO_COLOR PINK;
ALLEGRO_COLOR PURPLE;
ALLEGRO_COLOR ORANGE;
ALLEGRO_SAMPLE *menuAudioSample = NULL;
ALLEGRO_SAMPLE *jogoAudioSample = NULL;
ALLEGRO_SAMPLE *acertoAudioSample = NULL;
ALLEGRO_SAMPLE *erroAudioSample = NULL;
ALLEGRO_SAMPLE_INSTANCE *jogoAudioInstance = NULL;
ALLEGRO_SAMPLE_INSTANCE *menuAudioInstance = NULL;
ALLEGRO_SAMPLE_INSTANCE *acertoAudioInstance = NULL;
ALLEGRO_SAMPLE_INSTANCE *erroAudioInstance = NULL;

//variaveis da matriz
const int TOTAL_DE_LINHAS = 36;
const int TOTAL_DE_COLUNAS = 36;
const int OFFSET_X = 15;
const int OFFSET_Y = 30;

// Prototipos
void InitJogador(Jogador *jogador);
void InitLista(Lista *lista);
void InitBotaoJogar(BotaoJogar *botaoJogar);
void InitBotaoTutorial(BotaoTutorial *botaoTutorial);
void InitEstadosCores(char *estadosCinzaPath[], char *estadosVerdesPath[], char *estadosVermelhosPath[], ALLEGRO_BITMAP *estadosCinza[], ALLEGRO_BITMAP *estadosVerdes[], ALLEGRO_BITMAP *estadosVermelhos[]);
void CreateMatrix(float lines[], float columns[], int totalLines, int totalColumns, int offsetX, int offsetY);
void InitEstados(EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *Roraima, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins);

void ResetJogador(Jogador *jogador, bool resetNome);
void ResetLista(Lista * lista);

void UpdateLista(ALLEGRO_FONT *fontLista, Jogador *jogador, Lista *lista);
void GetColor(Lista *lista, int pontos);
void TiraEstado(Jogador *jogador);
void ConcatenaLista(char *s1, char *s2, Lista *lista);

void GetUserInput(Jogador *jogador, ALLEGRO_EVENT ev);
void SalvaPontuacao(FILE *rankingData, Jogador *jogador);
void GetPontuacao(FILE *rankingData, Ranking *ranking);
int GetTotalLinhas(FILE * rankingData);
char *GetFolderPath(char *path);

void SortPalavra(Jogador *jogador, Lista *lista);
void SortPontos(Ranking * ranking, int size);

void JogadorAcertou(Jogador *jogador, Lista *lista, int pontuacao);
void JogadorErrou(Jogador *jogador, Lista * lista);

void FreeNomeJogadores(Ranking * ranking);
void FreeEstadosPaths(char *estadosCinzaPath[], char *estadosVerdesPath[], char *estadosVermelhosPath[], ALLEGRO_BITMAP *estadosCinza[], ALLEGRO_BITMAP *estadosVerdes[], ALLEGRO_BITMAP *estadosVermelhos[]);

void DesenhaEstrelas(int pontos, ALLEGRO_BITMAP *estrela);
void DesenhaCoracoes(ALLEGRO_BITMAP *coracaoVazio, ALLEGRO_BITMAP *coracaoMetade, ALLEGRO_BITMAP *coracaoCheio, Jogador *jogador);
void DesenhaBtnPause(ALLEGRO_BITMAP *pauseBtn);
void DesenhaBtnMusica(ALLEGRO_BITMAP *musicaOn, ALLEGRO_BITMAP *musicaOff, int posX, int posY, bool musicaTocando);
void DesenhaPontuacaoRanking(ALLEGRO_FONT *fontLista, Ranking *ranking);
void DesenhaEstadosCinza(ALLEGRO_BITMAP *estadosCinza[], Jogador *jogador);
void DesenhaEstadosFeedBack(ALLEGRO_BITMAP *estadosVerdes[], ALLEGRO_BITMAP *estadosVermelhos[], Jogador *jogador, Lista * lista);

ClickIndex CheckClickPosition(float lines[], float columns[], int totalLines, int totalColumns, ALLEGRO_EVENT ev);
void TestaEstados(Jogador *jogador, Lista *lista, ClickIndex index, EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *Roraima, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins);

int main() {
	// Tipos Primitivos
	const int FPS = 60;
	float mLines[36];
	float mColumns[36];

	// Variaveis de objeto
	Jogador jogador;
	Lista lista;
	ClickIndex clickIndex;
	BotaoJogar botaoJogar;
	BotaoTutorial botaoTutorial;
	Ranking ranking;
	FILE *rankingData = NULL;

	//INICIALIZA�AO DOS ESTADOS
#pragma region INIT ESTADOS
	EstadosPadrao *_Acre, *_Alagoas, *_Amapa, *_Amazonas, *_Bahia, *_Ceara, *_DistritoFederal, *_EspiritoSanto, *_Goias, *_Maranhao,
		*_MatoGrosso, *_MatoGrossoDoSul, *_MinasGerais, *_Para, *_Paraiba, *_Parana, *_Pernambuco, *_Piaui, *_RioDeJaneiro, *_RioGrandeDoNorte,
		*_RioGrandeDoSul, *_Rondonia, *_Roraima, *_SantaCatarina, *_SaoPaulo, *_Sergipe, *_Tocantins;

	_Acre = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Alagoas = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Amapa = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Amazonas = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Bahia = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Ceara = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_DistritoFederal = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_EspiritoSanto = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Goias = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Maranhao = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_MatoGrosso = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_MatoGrossoDoSul = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_MinasGerais = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Para = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Paraiba = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Parana = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Pernambuco = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Piaui = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_RioDeJaneiro = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_RioGrandeDoNorte = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_RioGrandeDoSul = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Rondonia = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Roraima = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_SantaCatarina = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_SaoPaulo = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Sergipe = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Tocantins = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
#pragma endregion
	
	// Variaveis do Allegro
	ALLEGRO_BITMAP *mapaBrasil = NULL;
	ALLEGRO_BITMAP *menu = NULL;
	ALLEGRO_BITMAP *nomeJogadorTela = NULL;
	ALLEGRO_BITMAP *jogoBG = NULL;
	ALLEGRO_BITMAP *pauseBtn = NULL;
	ALLEGRO_BITMAP *gameOver = NULL;
	ALLEGRO_BITMAP *rankingTela = NULL;
	ALLEGRO_BITMAP *creditosTela = NULL;
	ALLEGRO_BITMAP *pauseTela = NULL;
	ALLEGRO_BITMAP *estrelaPontos = NULL;
	ALLEGRO_BITMAP *coracaoVazio = NULL;
	ALLEGRO_BITMAP *coracaoMetade = NULL;
	ALLEGRO_BITMAP *coracaoCheio = NULL;
	ALLEGRO_BITMAP *closeBtn = NULL;
	ALLEGRO_BITMAP *musicaOn = NULL;
	ALLEGRO_BITMAP *musicaOff = NULL;
	//ALLEGRO_BITMAP *jogarBotaoNormal = NULL;
	//ALLEGRO_BITMAP *jogarBotaoOver = NULL;
	ALLEGRO_BITMAP *estadosCinza[27];
	ALLEGRO_BITMAP *estadosVerdes[27];
	ALLEGRO_BITMAP *estadosVermelhos[27];
	ALLEGRO_BITMAP *tutorialTela = NULL;
	ALLEGRO_BITMAP *tocantins = NULL;
	ALLEGRO_FONT *fontLista = NULL;
	ALLEGRO_FONT *comboFont = NULL;
	ALLEGRO_FONT *combo10Font = NULL;

	// Inicializa o Allegro
	if (!al_init())
	{
		return -1;
	}

	// Inicializa o display
	display = al_create_display(WIDTH, HEIGHT);					// Inicializa o display
	if (!display)												// Caso nao inicializar o display retorna -1 para o SO
	{
		return -1;
	}
	al_set_window_title(display, "Clica Brasil");				// Coloca o titulo da janela "Clica Brasil"

	// Addons e instala��es do allegro
	al_install_mouse();											// Possibilita o uso do mouse
	al_install_keyboard();
	al_install_audio();											// Possibilita o uso de sons
	al_init_acodec_addon();										// Possibilita diferentes formatos
	al_init_font_addon();										// Possibilita escrever na tela
	al_init_ttf_addon();										// Possibilita usar formato ttf
	al_init_image_addon();										// Possibilita usar varios formatos de imagem
	al_init_primitives_addon();									// Possibilita usar formas geometricas

	// Carrega os bitmaps

	// Carrega Bitmaps dos Estados
	char *estadosCinzaPath[] = { GetFolderPath("/imgs/EstadosCinzas/RioGrandeDoSul.png"), GetFolderPath("/imgs/EstadosCinzas/SantaCatarina.png"), 
		GetFolderPath("/imgs/EstadosCinzas/Parana.png"), GetFolderPath("/imgs/EstadosCinzas/SaoPaulo.png"), GetFolderPath("/imgs/EstadosCinzas/RioDeJaneiro.png"), 
		GetFolderPath("/imgs/EstadosCinzas/MinasGerais.png"),  GetFolderPath("/imgs/EstadosCinzas/EspiritoSanto.png"), 
		GetFolderPath("/imgs/EstadosCinzas/MatoGrossoDoSul.png"), GetFolderPath("/imgs/EstadosCinzas/Goias.png"), GetFolderPath("/imgs/EstadosCinzas/DistritoFederal.png"), 
		GetFolderPath("/imgs/EstadosCinzas/MatoGrosso.png"), GetFolderPath("/imgs/EstadosCinzas/Tocantins.png"), GetFolderPath("/imgs/EstadosCinzas/Rondonia.png"), 
		GetFolderPath("/imgs/EstadosCinzas/Acre.png"), GetFolderPath("/imgs/EstadosCinzas/Amazonas.png"), GetFolderPath("/imgs/EstadosCinzas/Roraima.png"), GetFolderPath("/imgs/EstadosCinzas/Para.png"),
		GetFolderPath("/imgs/EstadosCinzas/Amapa.png"), GetFolderPath("/imgs/EstadosCinzas/Bahia.png"), GetFolderPath("/imgs/EstadosCinzas/Maranhao.png"), 
		GetFolderPath("/imgs/EstadosCinzas/Piaui.png"), GetFolderPath("/imgs/EstadosCinzas/Ceara.png"), GetFolderPath("/imgs/EstadosCinzas/RioGrandeDoNorte.png"), 
		GetFolderPath("/imgs/EstadosCinzas/Paraiba.png"), GetFolderPath("/imgs/EstadosCinzas/Pernambuco.png"), GetFolderPath("/imgs/EstadosCinzas/Alagoas.png"), 
		GetFolderPath("/imgs/EstadosCinzas/Sergipe.png") };

	char *estadosVerdesPath[] = { GetFolderPath("/imgs/EstadosVerdes/RioGrandeDoSul.png"), GetFolderPath("/imgs/EstadosVerdes/SantaCatarina.png"),
		GetFolderPath("/imgs/EstadosVerdes/Parana.png"), GetFolderPath("/imgs/EstadosVerdes/SaoPaulo.png"), GetFolderPath("/imgs/EstadosVerdes/RioDeJaneiro.png"),
		GetFolderPath("/imgs/EstadosVerdes/MinasGerais.png"),  GetFolderPath("/imgs/EstadosVerdes/EspiritoSanto.png"),
		GetFolderPath("/imgs/EstadosVerdes/MatoGrossoDoSul.png"), GetFolderPath("/imgs/EstadosVerdes/Goias.png"), GetFolderPath("/imgs/EstadosVerdes/DistritoFederal.png"),
		GetFolderPath("/imgs/EstadosVerdes/MatoGrosso.png"), GetFolderPath("/imgs/EstadosVerdes/Tocantins.png"), GetFolderPath("/imgs/EstadosVerdes/Rondonia.png"),
		GetFolderPath("/imgs/EstadosVerdes/Acre.png"), GetFolderPath("/imgs/EstadosVerdes/Amazonas.png"), GetFolderPath("/imgs/EstadosVerdes/Roraima.png"), GetFolderPath("/imgs/EstadosVerdes/Para.png"),
		GetFolderPath("/imgs/EstadosVerdes/Amapa.png"), GetFolderPath("/imgs/EstadosVerdes/Bahia.png"), GetFolderPath("/imgs/EstadosVerdes/Maranhao.png"),
		GetFolderPath("/imgs/EstadosVerdes/Piaui.png"), GetFolderPath("/imgs/EstadosVerdes/Ceara.png"), GetFolderPath("/imgs/EstadosVerdes/RioGrandeDoNorte.png"),
		GetFolderPath("/imgs/EstadosVerdes/Paraiba.png"), GetFolderPath("/imgs/EstadosVerdes/Pernambuco.png"), GetFolderPath("/imgs/EstadosVerdes/Alagoas.png"),
		GetFolderPath("/imgs/EstadosVerdes/Sergipe.png") };

	char *estadosVermelhosPath[] = { GetFolderPath("/imgs/EstadosVermelhos/RioGrandeDoSul.png"), GetFolderPath("/imgs/EstadosVermelhos/SantaCatarina.png"),
		GetFolderPath("/imgs/EstadosVermelhos/Parana.png"), GetFolderPath("/imgs/EstadosVermelhos/SaoPaulo.png"), GetFolderPath("/imgs/EstadosVermelhos/RioDeJaneiro.png"),
		GetFolderPath("/imgs/EstadosVermelhos/MinasGerais.png"),  GetFolderPath("/imgs/EstadosVermelhos/EspiritoSanto.png"),
		GetFolderPath("/imgs/EstadosVermelhos/MatoGrossoDoSul.png"), GetFolderPath("/imgs/EstadosVermelhos/Goias.png"), GetFolderPath("/imgs/EstadosVermelhos/DistritoFederal.png"),
		GetFolderPath("/imgs/EstadosVermelhos/MatoGrosso.png"), GetFolderPath("/imgs/EstadosVermelhos/Tocantins.png"), GetFolderPath("/imgs/EstadosVermelhos/Rondonia.png"),
		GetFolderPath("/imgs/EstadosVermelhos/Acre.png"), GetFolderPath("/imgs/EstadosVermelhos/Amazonas.png"), GetFolderPath("/imgs/EstadosVermelhos/Roraima.png"), GetFolderPath("/imgs/EstadosVermelhos/Para.png"),
		GetFolderPath("/imgs/EstadosVermelhos/Amapa.png"), GetFolderPath("/imgs/EstadosVermelhos/Bahia.png"), GetFolderPath("/imgs/EstadosVermelhos/Maranhao.png"),
		GetFolderPath("/imgs/EstadosVermelhos/Piaui.png"), GetFolderPath("/imgs/EstadosVermelhos/Ceara.png"), GetFolderPath("/imgs/EstadosVermelhos/RioGrandeDoNorte.png"),
		GetFolderPath("/imgs/EstadosVermelhos/Paraiba.png"), GetFolderPath("/imgs/EstadosVermelhos/Pernambuco.png"), GetFolderPath("/imgs/EstadosVermelhos/Alagoas.png"),
		GetFolderPath("/imgs/EstadosVermelhos/Sergipe.png") };
	
	InitEstadosCores(estadosCinzaPath, estadosVerdesPath, estadosVermelhosPath, estadosCinza, estadosVerdes, estadosVermelhos);

	// Bitmap do menu do jogo
	char *menuPath = GetFolderPath("/imgs/Telas/telaInicial.jpg");
	menu = al_load_bitmap(menuPath);

	// Bitmap do popup de input de nome do jogador
	char *inputPopupPath = GetFolderPath("/imgs/Telas/nomeJogador.png");
	nomeJogadorTela = al_load_bitmap(inputPopupPath);

	// Bitmap do mapa do jogo
	char *mapaPath = GetFolderPath("/imgs/Mapas/mapaEscuro1.png");
	mapaBrasil = al_load_bitmap(mapaPath);	 // bmp de testes para encontrar o indice correto
	int mapaWidth = al_get_bitmap_width(mapaBrasil);			 // Recebe o tamanho X da imagem
	int mapaHeight = al_get_bitmap_height(mapaBrasil);			 // Recebe o tamanho Y da imagem
	
	// Bitmap teste do fundo
	char *jogoBGPath = GetFolderPath("/imgs/Telas/mapa-bg.jpg");
	jogoBG = al_load_bitmap(jogoBGPath);

	// Bitmap botao de pause
	char *pauseBtnPath = GetFolderPath("/imgs/Botoes/pause.png");
	pauseBtn = al_load_bitmap(pauseBtnPath);

	char *closeBtnPath = GetFolderPath("/imgs/HUDItens/close.png");
	closeBtn = al_load_bitmap(closeBtnPath);

	// Bitmaps dos botoes de musicaOn e musicaOff
	char *musicOnPath = GetFolderPath("/imgs/Botoes/music.png");
	char *musicOffPath = GetFolderPath("/imgs/Botoes/mute.png");
	musicaOn = al_load_bitmap(musicOnPath);
	musicaOff = al_load_bitmap(musicOffPath);

	//Bitmap Coracoes
	char *coracaoVazioPath = GetFolderPath("/imgs/HUDItens/heartempty.png");
	char *coracaoMetadePath = GetFolderPath("/imgs/HUDItens/hearthalf.png");
	char *coracaoCheioPath = GetFolderPath("/imgs/HUDItens/heartfull.png");
	coracaoVazio = al_load_bitmap(coracaoVazioPath);
	coracaoMetade = al_load_bitmap(coracaoMetadePath);
	coracaoCheio = al_load_bitmap(coracaoCheioPath);

	// Bitmap da tela de Game Over
	char *gameOverPath = GetFolderPath("/imgs/Telas/gameover.png");
	gameOver = al_load_bitmap(gameOverPath);

	// Bitmap da tela de creditos
	char *creditosTelaPath = GetFolderPath("/imgs/Telas/creditos.png");
	creditosTela = al_load_bitmap(creditosTelaPath);

	// Bitmap da tela de ranking
	char *rankingTelaPath = GetFolderPath("/imgs/Telas/ranking.png");
	rankingTela = al_load_bitmap(rankingTelaPath);

	// Bitmap da tela de pause
	char *pauseTelaPath = GetFolderPath("/imgs/Telas/pause.png");
	pauseTela = al_load_bitmap(pauseTelaPath);

	//bitmap do tutorial do jogo
	char *tutorialPath = GetFolderPath("/imgs/Telas/tutorial.png");
	tutorialTela = al_load_bitmap(tutorialPath);

	// Bitmap da estrelas de pontuação
	char *estrelaPontosPath = GetFolderPath("/imgs/HUDItens/star.png");
	estrelaPontos = al_load_bitmap(estrelaPontosPath);

	// Carrega as fonts
	char *fontListaPath = GetFolderPath("/fonts/Florsn33.ttf");
	fontLista = al_load_font(fontListaPath, 20, 0);

	char *fontComboPath = GetFolderPath("/fonts/Space Comics.ttf");
	comboFont = al_load_font(fontComboPath, 35, 0);

	// Inicializa cores
	WHITE = al_map_rgb(255, 255, 255);
	BLACK = al_map_rgb(0, 0, 0);
	BLUE = al_map_rgb(45, 103, 151);
	GREEN = al_map_rgb(110, 156, 45);
	PINK = al_map_rgb(163, 9, 81);
	PURPLE = al_map_rgb(123, 71, 144);
	ORANGE = al_map_rgb(167, 98, 5);

	// Inicializa sons
	al_reserve_samples(2);		// Quantidade de "canais" de audio ( 1 para cada audio )

	// Audio do menu
	char *menuAudioSamplePath = GetFolderPath("/audio/Audio.wav");
	menuAudioSample = al_load_sample(menuAudioSamplePath);
	menuAudioInstance = al_create_sample_instance(menuAudioSample);
	al_attach_sample_instance_to_mixer(menuAudioInstance, al_get_default_mixer());

	// Audio do fundo do jogo
	char *jogoAudioSamplePath = GetFolderPath("/audio/AudioJazz.wav");
	jogoAudioSample = al_load_sample(jogoAudioSamplePath);
	jogoAudioInstance = al_create_sample_instance(jogoAudioSample);
	al_attach_sample_instance_to_mixer(jogoAudioInstance, al_get_default_mixer());
	al_set_sample_instance_gain(jogoAudioInstance, 0.3);

	// Audio de acerto
	char *acertoAudioSamplePath = GetFolderPath("/audio/AcertoAudio.wav");
	acertoAudioSample = al_load_sample(acertoAudioSamplePath);
	acertoAudioInstance = al_create_sample_instance(acertoAudioSample);
	al_attach_sample_instance_to_mixer(acertoAudioInstance, al_get_default_mixer());

	// Audio de erro
	char *erroAudioSamplePath = GetFolderPath("/audio/ErroAudio.wav");
	erroAudioSample = al_load_sample(erroAudioSamplePath);
	erroAudioInstance = al_create_sample_instance(erroAudioSample);
	al_attach_sample_instance_to_mixer(erroAudioInstance, al_get_default_mixer());

	// Inicializacao dos nossos objetos
	CreateMatrix(mLines, mColumns, TOTAL_DE_LINHAS, TOTAL_DE_COLUNAS, OFFSET_X, OFFSET_Y);
	InitJogador(&jogador);

	InitEstados(_Acre, _Alagoas, _Amapa, _Amazonas, _Bahia, _Ceara, _DistritoFederal, _EspiritoSanto, _Goias, _Maranhao,
		_MatoGrosso, _MatoGrossoDoSul, _MinasGerais, _Para, _Paraiba, _Parana, _Pernambuco, _Piaui, _RioDeJaneiro, _RioGrandeDoNorte,
		_RioGrandeDoSul, _Rondonia, _Roraima, _SantaCatarina, _SaoPaulo, _Sergipe, _Tocantins);

	InitLista(&lista);

	//Inicializacao dos Bot�es do Menu
	InitBotaoJogar(&botaoJogar);
	InitBotaoTutorial(&botaoTutorial);

	event_queue = al_create_event_queue();						// Cria "lista" de eventos

	timer = al_create_timer(1.0 / FPS);							// Inicializa o timer para que tenhamos 60 fps
	piscaTimer = al_create_timer(0.3);							// Inicializa o timer para contar segundos para piscar

	// Registro de eventos para a lista de eventos
	al_register_event_source(event_queue, al_get_mouse_event_source());			// Registra o mouse na lista de eventos
	al_register_event_source(event_queue, al_get_keyboard_event_source());		// Registra o teclado na lista de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(timer));			// Registra o timer na lista de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(piscaTimer));			// Registra o timer na lista de eventos
	al_register_event_source(event_queue, al_get_display_event_source(display));			// Registra o display na lista de eventos

	al_start_timer(timer);										// Inicia o timer

	// Looping Principal
	while (!finished) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		// � invocado a cada frame "Fun��o de update" 
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// Caso a quantidade de vidas do jogador for menor que zero
			// isGameOver � falso para podermos mostrar a tela de pontua��o
			if (jogador.vidas <= 0)
			{
				isGameOver = true;
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	// Permite fechar a janela pelo X
		{
			finished = true;
		}	

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && isInMenu) //verifica se o jogador clicou em jogar
		{
			// Verifica se o click esta dentro dos bounds do botao jogar, caso esteja a variavel jogador.jogando é verdadeira
			if (ev.mouse.x >= botaoJogar.boundXInicio && ev.mouse.x <= botaoJogar.boundXFinal && ev.mouse.y >= botaoJogar.boundYInicio &&  ev.mouse.y <= botaoJogar.boundYFinal)
			{
				jogador.pronto = true;
			}

			//Verifica se o click est� dentro dos bounds do bot�o tutorial, caso esteja variavel jogador.tutorial é verdadeira 
			if (ev.mouse.x >= botaoTutorial.boundXInicio && ev.mouse.x <= botaoTutorial.boundXFinal && ev.mouse.y >= botaoTutorial.boundYInicio &&  ev.mouse.y <= botaoTutorial.boundYFinal)
			{
				clicouTutorial = true;
			}

			//Verifica se o click est� dentro dos bounds do bot�o ranking
			if (ev.mouse.x >= 1090 && ev.mouse.x <= 1163 && ev.mouse.y >= 622 && ev.mouse.y <= 891)
			{
				clicouRanking = true;
			}

			//Verifica se o click est� dentro dos bounds do bot�o creditos
			if (ev.mouse.x >= 1171 && ev.mouse.x <= 1245 && ev.mouse.y >= 622 && ev.mouse.y <= 891)
			{
				clicouCreditos = true;
			}

			//Verifica se o click est� dentro dos bounds do continuar para verificar se o jogador digitou o nome, caso tenha digitado a variavel digitouNome é verdadeira 
			if (ev.mouse.x >= 743 && ev.mouse.x <= 905 && ev.mouse.y >= 446 && ev.mouse.y <= 486 && strlen(jogador.nome) >= 1)
			{
				digitouNome = true;
			}

			// Verifica se o click esta dentro dos bounds do botao de fechar nos popups ranking, creditos e digitar o nome
			if (ev.mouse.x >= 1235 && ev.mouse.x <= 1256 && ev.mouse.y >= 14 && ev.mouse.y <= 35)
			{
				if (clicouRanking)
				{
					clicouRanking = false;
				}

				if (clicouCreditos)
				{
					clicouCreditos = false;
				}

				if (clicouTutorial)
				{
					clicouTutorial = false;
				}

				if (jogador.pronto)
				{
					jogador.pronto = false;
				}
			}

			//Verifica se o click est� dentro dos bounds do bot�o musica, dependendo do estado da musica atual musicaTocando assume diferentes valores
			if (ev.mouse.x >= 1006 && ev.mouse.x <= 1075 && ev.mouse.y >= 623 && ev.mouse.y <= 890)
			{
				if (musicaTocando)
				{
					musicaTocando = false;
				}
				else {
					musicaTocando = true;
				}
			}
		}

		// TODO: Arrumar o erro que quando o jogador clica em JOGAR ja conta um acerto
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && jogador.pronto && !isGameOver && digitouNome && !clicouPause) // Verifica se houve input de click no bot�o jogar
		{
			ClickIndex t = CheckClickPosition(mLines, mColumns, TOTAL_DE_LINHAS, TOTAL_DE_COLUNAS, ev); //checa se o click foi no mapa
			//printf("index %d, %d\n", t.i, t.j);

			//TESTA o click para ver qual estado foi clicado
			TestaEstados(&jogador, &lista, t, _Acre, _Alagoas, _Amapa, _Amazonas, _Bahia, _Ceara, _DistritoFederal, _EspiritoSanto, _Goias, _Maranhao,
				_MatoGrosso, _MatoGrossoDoSul, _MinasGerais, _Para, _Paraiba, _Parana, _Pernambuco, _Piaui, _RioDeJaneiro, _RioGrandeDoNorte,
				_RioGrandeDoSul, _Rondonia, _Roraima, _SantaCatarina, _SaoPaulo, _Sergipe, _Tocantins);

			

			// Verifica se jogador clicou no pause
			if (ev.mouse.x >= 1164 && ev.mouse.x <= 1238 && ev.mouse.y >= 33 && ev.mouse.y <= 101 && !clicouPause)
			{
				clicouPause = true;
			}

			// Inicia o timer de piscar os estados
			al_start_timer(piscaTimer);
			jogadorJogando = true;
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && isGameOver)
		{
			if (ev.mouse.x >= 852 && ev.mouse.x <= 896 && ev.mouse.y >= 446 && ev.mouse.y <= 490)
			{				
				al_stop_sample_instance(jogoAudioInstance);
				isInMenu = true;
				digitouNome = false;
				jogadorJogando = false;
				ResetJogador(&jogador, true);
				isGameOver = false;
			}
		}

		// Verifica em qual botao do menu de pause o jogador clicou
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && clicouPause)
		{ 
			// Caso clicou no menu devemos Resetar variaveis globais, o jogador e mudar musica
			if (ev.mouse.x >= 462 && ev.mouse.x <= 536 && ev.mouse.y >= 367 && ev.mouse.y <= 434)
			{
				al_stop_sample_instance(jogoAudioInstance);
				ResetJogador(&jogador, true);
				isInMenu = true;
				clicouPause = false;
				digitouNome = false;
				jogadorJogando = false;
			}

			// Caso clicou no icone de musica devemos parar a musica caso esteja tocando e vice versa
			if (ev.mouse.x >= 558 && ev.mouse.x <= 631 && ev.mouse.y >= 367 && ev.mouse.y <= 434)
			{
				if (musicaTocando)
				{
					musicaTocando = false;
				}
				else {
					musicaTocando = true;
				}
			}

			// Caso clicou no botao de voltar ao jogo devemos tirar do menu de pause
			if (ev.mouse.x >= 653 && ev.mouse.x <= 727 && ev.mouse.y >= 367 && ev.mouse.y <= 434)
			{
				clicouPause = false;
			}

			// Caso clicou em restart devemos resetar os dados do jogador
			if (ev.mouse.x >= 748 && ev.mouse.x <= 822 && ev.mouse.y >= 367 && ev.mouse.y <= 434)
			{
				ResetJogador(&jogador, false);
				clicouPause = false;
			}
		}

		// Verifica se o jogador apertou alguma tecla do teclado na tela de digitar o nome
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && !digitouNome && jogador.pronto)
		{
			GetUserInput(&jogador, ev);
		}

		if (redraw && al_is_event_queue_empty(event_queue))			// Permite saber quando podemos redesenhar na tela
		{
			redraw = false;

			if (jogador.pronto && digitouNome)   //verifica se o jogador passou a jogar
			{
				isInMenu = false;
				al_stop_sample_instance(menuAudioInstance);

				// Verifica o estado da musica (tocando ou nao)
				if (musicaTocando)
				{
					al_play_sample_instance(jogoAudioInstance);
				}
				else {
					al_stop_sample_instance(jogoAudioInstance);
				}

				al_flip_display();

				// Desenha o mapa e o bg do jogo na tela
				al_draw_bitmap(jogoBG, 0, 0, 0);

				// Desenha estados cinza caso haja, o botão de pause, os corações de acordo com as vidas do jogador,
				// os pontos e combo caso necessário
				DesenhaEstadosCinza(estadosCinza, &jogador);
				DesenhaBtnPause(pauseBtn);
				DesenhaCoracoes(coracaoVazio, coracaoMetade, coracaoCheio, &jogador);
				al_draw_textf(fontLista, BLACK, 1028, 36, 0, "%d", jogador.pontos);

				if (jogador.combo >= 5)
				{
					al_draw_textf(comboFont, BLACK, 130, 550, 0, "X%d", jogador.combo);
				}

				// Se o jogador nao clicou pause e nao terminou o jogo devemos fazer o update da lista
				// e desenhar os estados vermelhos e verdes de acordo com o acertou ou erro
				// caso o jogador pause o jogo devemos desenhar a tela de pause.
				if (!clicouPause && !isGameOver)
				{
					UpdateLista(fontLista, &jogador, &lista);
					DesenhaEstadosFeedBack(estadosVerdes, estadosVermelhos, &jogador, &lista);
				}
				else if (clicouPause && !isGameOver) {
					al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 40, 40, 220));
					al_draw_bitmap(pauseTela, WIDTH / 2 - 290, HEIGHT / 2 - 157, 0);
					DesenhaBtnMusica(musicaOn, musicaOff, 554, 363, musicaTocando);
				}

				// Se o jogo acabou devemos desenhar a tela de gameover, as estrelas e a pontuação do jogador
				// e devemos também salvar a pontuação no txt
				if (isGameOver)
				{		
					al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 40, 40, 220));
					al_draw_bitmap(gameOver, WIDTH / 2 - 290, HEIGHT / 2 - 157, 0);
					DesenhaEstrelas(jogador.pontos, estrelaPontos);
					al_draw_textf(fontLista, WHITE, WIDTH / 2 + 10, (HEIGHT / 2) - 4, ALLEGRO_ALIGN_CENTER, "%d", jogador.pontos);
					al_draw_textf(fontLista, WHITE, WIDTH / 2 + 10, (HEIGHT / 2) + 23, ALLEGRO_ALIGN_CENTER, "%d", jogador.acertos);
					al_draw_textf(fontLista, WHITE, WIDTH / 2 + 10, (HEIGHT / 2) + 52, ALLEGRO_ALIGN_CENTER, "%d", jogador.erros);

					if (!salvouPontuacao)
					{
						SalvaPontuacao(rankingData, &jogador);
						salvouPontuacao = true;
					}
				}	
			}
			else
			{
				// Caso estejamos no menu, devemos verificar o estado da musica (tocando ou nao)
				if (musicaTocando)
				{
					al_play_sample_instance(menuAudioInstance);
				}
				else {
					al_stop_sample_instance(menuAudioInstance);
				}

				al_draw_bitmap(menu, 0, 0, 0);		//coloca o menu na tela
				DesenhaBtnMusica(musicaOn, musicaOff, 1000, 617, musicaTocando); // Desenha o botao de musica de acordo com seu estado atual

				// Caso jogador clicou em jogar e nao digitou o nome devemos mostrar a tela para digitar o nome de jogador
				if (jogador.pronto && !digitouNome)
				{
					al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 40, 40, 220));
					al_draw_bitmap(nomeJogadorTela, WIDTH / 2 - 290, HEIGHT / 2 - 157, 0);
					al_draw_bitmap(closeBtn, 1220, 0, 0);
					al_draw_textf(fontLista, BLACK, 645, 363, ALLEGRO_ALIGN_CENTER, "%s", jogador.nome);
				}

				if (clicouTutorial)
				{
					al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 40, 40, 220));
					al_draw_bitmap(tutorialTela, 0, 0, 0);
					al_draw_bitmap(closeBtn, 1220, 0, 0);
				}

				// Caso o jogador clicou no botao dos creditos
				if (clicouCreditos)
				{
					al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 40, 40, 220));
					al_draw_bitmap(creditosTela, WIDTH / 2 - 290, HEIGHT / 2 - 157, 0);
					al_draw_bitmap(closeBtn, 1220, 0, 0);
				}

				// Caso o jogador clicou no botao do ranking, devemos pegar as pontuações salvas e exibir na tela
				if (clicouRanking)
				{
					al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(40, 40, 40, 220));
					al_draw_bitmap(rankingTela, WIDTH / 2 - 290, HEIGHT / 2 - 157, 0);
					al_draw_bitmap(closeBtn, 1220, 0, 0);
					GetPontuacao(rankingData, &ranking);
					DesenhaPontuacaoRanking(fontLista, &ranking);
				}
				al_flip_display();			// Muda para o back buffer
			}
		}
	}

	// Libera memoria dos paths utilizados
#pragma region Libera memoria paths
	free(menuPath);
	free(inputPopupPath);
	free(mapaPath);
	free(jogoBGPath);
	free(gameOverPath);
	free(rankingTelaPath);
	free(creditosTelaPath);
	free(pauseTelaPath);
	free(pauseBtnPath);
	free(tutorialPath);
	free(closeBtnPath);
	free(musicOnPath);
	free(musicOffPath);
	free(coracaoVazioPath);
	free(coracaoMetadePath);
	free(coracaoCheioPath);
	free(estrelaPontosPath);
	free(fontListaPath);
	free(fontComboPath);
	free(menuAudioSamplePath);
	free(jogoAudioSamplePath);
	free(acertoAudioSamplePath);
	free(erroAudioSamplePath);
	FreeNomeJogadores(&ranking);
	FreeEstadosPaths(estadosCinzaPath, estadosVerdesPath, estadosVermelhosPath, estadosCinza, estadosVerdes, estadosVermelhos);
#pragma endregion

	// Libera a memoria alocada para variaveis Allegro
#pragma region Libera memoria variaveis Allegro
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(mapaBrasil);
	al_destroy_bitmap(menu);
	al_destroy_bitmap(nomeJogadorTela);
	al_destroy_bitmap(jogoBG);
	al_destroy_bitmap(gameOver);
	al_destroy_bitmap(rankingTela);
	al_destroy_bitmap(creditosTela);
	al_destroy_bitmap(pauseTela);
	al_destroy_bitmap(closeBtn);
	al_destroy_bitmap(musicaOn);
	al_destroy_bitmap(musicaOff);
	al_destroy_bitmap(coracaoVazio);
	al_destroy_bitmap(coracaoMetade);
	al_destroy_bitmap(coracaoCheio);
	al_destroy_bitmap(estrelaPontos);
	al_destroy_bitmap(tutorialTela);
	al_destroy_font(fontLista);
	al_destroy_font(comboFont);
	al_destroy_sample(menuAudioSample);
	al_destroy_sample(jogoAudioSample);
	al_destroy_sample(acertoAudioSample);
	al_destroy_sample(erroAudioSample);
	al_destroy_sample_instance(menuAudioInstance);
	al_destroy_sample_instance(jogoAudioInstance);
	al_destroy_sample_instance(acertoAudioInstance);
	al_destroy_sample_instance(erroAudioInstance);
#pragma endregion

	return 0;
}

// Definicao de funcoes

// Inicializa o jogador
void InitJogador(Jogador * jogador)
{
	strcpy(jogador->nome, "");
	jogador->pontos = 0;
	jogador->vidas = 12;
	jogador->acertos = 0;
	jogador->erros = 0;
	jogador->combo = 0;
	jogador->acertou = false;
	jogador->pronto = false;

	int i;
	for (i = 0; i < 27; i++)
	{
		jogador->acertoPorIndex[i] = -1;
	}

	for (i = 0; i < 5; i++)
	{
		jogador->indexEstadosPerdidos[i] = -1;
	}
}
void InitLista(Lista * lista)
{
	lista->velocidade = 1.0f;
	lista->heightLista = 0;
	lista->palavraAtual = NULL;
	lista->isMaxHeight = false;
	lista->indexAtual = -1;
	lista->indexAnterior = -1;
}
void InitBotaoJogar(BotaoJogar * botaoJogar)
{
	botaoJogar->boundXInicio = 435;
	botaoJogar->boundXFinal = 850;

	botaoJogar->boundYInicio = 420;
	botaoJogar->boundYFinal = 485;
}
void InitBotaoTutorial(BotaoTutorial * botaoTutorial)
{

	botaoTutorial->boundXInicio = 431;
	botaoTutorial->boundXFinal = 850;

	botaoTutorial->boundYInicio = 500;
	botaoTutorial->boundYFinal = 570;
}
void CreateMatrix(float lines[], float columns[], int totalLines, int totalColumns, int offsetX, int offsetY)
{
	float pixelW = WIDTHMAPA / (float)totalLines; //dividir o width pelo numero de linhas me da o tamanho em pixel de cada quadrado
	float pixelH = HEIGHTMAPA / (float)totalColumns; // mesma coisa de cima

	int i = 0, j = 0;
	for (i = 0; i < totalLines; i++)
	{
		lines[i] = (pixelH + pixelH * i) + offsetY; // adiciono o valor em pixels onde ira comecar a matriz de Linhas
	}
	for (j = 0; j < totalColumns; j++)
	{
		columns[j] = (pixelW + pixelW * j) + offsetX; // adiciono o valor em pixels onde ira comecar a matriz de colunas
	}
}
void InitEstadosCores(char *estadosCinzaPath[], char *estadosVerdesPath[], char *estadosVermelhosPath[], ALLEGRO_BITMAP *estadosCinza[], ALLEGRO_BITMAP *estadosVerdes[], ALLEGRO_BITMAP *estadosVermelhos[])
{
	int i;
	for (i = 0; i < 27; i++)
	{
		estadosCinza[i] = al_load_bitmap(estadosCinzaPath[i]);
		estadosVerdes[i] = al_load_bitmap(estadosVerdesPath[i]);
		estadosVermelhos[i] = al_load_bitmap(estadosVermelhosPath[i]);
	}
}
void InitEstados(EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *Roraima, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins) //diego adicionou Roraima
{
#pragma region DISTRITO FEDERAL
	DistritoFederal->myIndexPosition = 9; //posicao no vetor ESTADOS de nomes na classe objects.h
	DistritoFederal->index[0].i = 18; DistritoFederal->index[0].j = 23;
	DistritoFederal->index[1].i = 18; DistritoFederal->index[1].j = 24;
	DistritoFederal->index[2].i = 19; DistritoFederal->index[2].j = 23;
	DistritoFederal->index[3].i = 19; DistritoFederal->index[3].j = 24;
#pragma endregion

#pragma region GOIAS
	Goias->myIndexPosition = 8; //posicao no vetor ESTADOS de nomes na classe objects.h
	Goias->index[0].i = 17; Goias->index[0].j = 25;
	Goias->index[1].i = 17; Goias->index[1].j = 24;
	Goias->index[2].i = 17; Goias->index[2].j = 23;
	Goias->index[3].i = 17; Goias->index[3].j = 22;
	Goias->index[4].i = 18; Goias->index[4].j = 21;
	Goias->index[5].i = 18; Goias->index[5].j = 22;
	Goias->index[6].i = 19; Goias->index[6].j = 22;
	Goias->index[7].i = 19; Goias->index[7].j = 21;
	Goias->index[8].i = 19; Goias->index[8].j = 20;
	Goias->index[9].i = 20; Goias->index[9].j = 20;
	Goias->index[10].i = 20; Goias->index[10].j = 24;
	Goias->index[11].i = 20; Goias->index[11].j = 23;
	Goias->index[12].i = 20; Goias->index[12].j = 22;
	Goias->index[13].i = 20; Goias->index[13].j = 21;
	Goias->index[14].i = 20; Goias->index[14].j = 20;
	Goias->index[15].i = 21; Goias->index[15].j = 20;
	Goias->index[16].i = 21; Goias->index[16].j = 21;
	Goias->index[17].i = 18; Goias->index[17].j = 22;

#pragma endregion

#pragma region ACRE
	Acre->myIndexPosition = 13; //posicao no vetor ESTADOS de nomes na classe objects.h
	Acre->index[0].i = 11; Acre->index[0].j = 1;
	Acre->index[1].i = 12; Acre->index[1].j = 1;
	Acre->index[2].i = 12; Acre->index[2].j = 2;
	Acre->index[3].i = 12; Acre->index[3].j = 3;
	Acre->index[4].i = 12; Acre->index[4].j = 4;
	Acre->index[5].i = 13; Acre->index[5].j = 2;
	Acre->index[6].i = 13; Acre->index[6].j = 3;
	Acre->index[7].i = 13; Acre->index[7].j = 4;
	Acre->index[8].i = 13; Acre->index[8].j = 5;
	Acre->index[9].i = 13; Acre->index[9].j = 6;
	Acre->index[10].i = 14; Acre->index[10].j = 4;
	Acre->index[11].i = 14; Acre->index[11].j = 5;
	Acre->index[12].i = 14; Acre->index[12].j = 6;
	Acre->index[13].i = 14; Acre->index[13].j = 7;

#pragma endregion

#pragma region SANTA CATARINA
	SantaCatarina->myIndexPosition = 1;
	SantaCatarina->index[0].i = 29; SantaCatarina->index[0].j = 19;
	SantaCatarina->index[1].i = 29; SantaCatarina->index[1].j = 20;
	SantaCatarina->index[2].i = 29; SantaCatarina->index[2].j = 21;
	SantaCatarina->index[3].i = 29; SantaCatarina->index[3].j = 22;
	SantaCatarina->index[4].i = 29; SantaCatarina->index[4].j = 23;
	SantaCatarina->index[5].i = 30; SantaCatarina->index[5].j = 21;
	SantaCatarina->index[6].i = 30; SantaCatarina->index[6].j = 22;
	SantaCatarina->index[7].i = 30; SantaCatarina->index[7].j = 23;
	SantaCatarina->index[8].i = 31; SantaCatarina->index[8].j = 22;
	SantaCatarina->index[9].i = 31; SantaCatarina->index[9].j = 23;
#pragma endregion

#pragma region RIO GRANDE DO NORTE
	RioGrandeDoNorte->myIndexPosition = 22; //posicao no vetor ESTADOS de nomes na classe objects.h
	RioGrandeDoNorte->index[0].i = 9; RioGrandeDoNorte->index[0].j = 33;
	RioGrandeDoNorte->index[1].i = 10; RioGrandeDoNorte->index[1].j = 33;
	RioGrandeDoNorte->index[2].i = 10; RioGrandeDoNorte->index[2].j = 34;
	RioGrandeDoNorte->index[3].i = 10; RioGrandeDoNorte->index[3].j = 35;
#pragma endregion

#pragma region CEARA
	Ceara->myIndexPosition = 21; //posicao no vetor ESTADOS de nomes na classe objects.h
	Ceara->index[0].i = 7; Ceara->index[0].j = 30;
	Ceara->index[1].i = 7; Ceara->index[1].j = 31;
	Ceara->index[2].i = 8; Ceara->index[2].j = 30;
	Ceara->index[3].i = 8; Ceara->index[3].j = 31;
	Ceara->index[4].i = 8; Ceara->index[4].j = 32;
	Ceara->index[5].i = 9; Ceara->index[5].j = 30;
	Ceara->index[6].i = 9; Ceara->index[6].j = 31;
	Ceara->index[7].i = 9; Ceara->index[7].j = 32;
	Ceara->index[8].i = 10; Ceara->index[8].j = 30;
	Ceara->index[9].i = 10; Ceara->index[9].j = 31;
	Ceara->index[10].i = 10; Ceara->index[10].j = 32;
	Ceara->index[11].i = 11; Ceara->index[11].j = 30;
	Ceara->index[12].i = 11; Ceara->index[12].j = 31;
#pragma endregion

#pragma region PARAIBA
	Paraiba->myIndexPosition = 23; //posicao no vetor ESTADOS de nomes na classe objects.h
	Paraiba->index[0].i = 11; Paraiba->index[0].j = 32;
	Paraiba->index[1].i = 11; Paraiba->index[1].j = 33;
	Paraiba->index[2].i = 11; Paraiba->index[2].j = 34;
	Paraiba->index[3].i = 11; Paraiba->index[3].j = 35;
#pragma endregion

#pragma region PERNAMBUCO
	Pernambuco->myIndexPosition = 24;
	Pernambuco->index[0].i = 12; Pernambuco->index[0].j = 30;
	Pernambuco->index[1].i = 12; Pernambuco->index[1].j = 31;
	Pernambuco->index[2].i = 12; Pernambuco->index[2].j = 32;
	Pernambuco->index[3].i = 12; Pernambuco->index[3].j = 33;
	Pernambuco->index[4].i = 12; Pernambuco->index[4].j = 34;
	Pernambuco->index[5].i = 12; Pernambuco->index[5].j = 35;
	Pernambuco->index[6].i = 13; Pernambuco->index[6].j = 30;
	//Pernambuco->index[7].i = 13; Pernambuco->index[7].j = 33;
	//Pernambuco->index[8].i = 13; Pernambuco->index[8].j = 34;
#pragma endregion

#pragma region ALAGOAS
	Alagoas->myIndexPosition = 25; //posicao no vetor ESTADOS de nomes na classe objects.h
	Alagoas->index[0].i = 13; Alagoas->index[0].j = 33;
	Alagoas->index[1].i = 13; Alagoas->index[1].j = 34;
	Alagoas->index[2].i = 14; Alagoas->index[2].j = 34;
#pragma endregion

#pragma region SERGIPE
	Sergipe->myIndexPosition = 26; //posicao no vetor ESTADOS de nomes na classe objects.h
	Sergipe->index[0].i = 14; Sergipe->index[0].j = 33;
	Sergipe->index[1].i = 15; Sergipe->index[1].j = 33;
#pragma endregion

#pragma region BAHIA
	Bahia->myIndexPosition = 18; //posicao no vetor ESTADOS de nomes na classe objects.h
	Bahia->index[0].i = 13;   Bahia->index[0].j = 29;
	Bahia->index[1].i = 13;   Bahia->index[1].j = 31;
	Bahia->index[2].i = 13;   Bahia->index[2].j = 32;
	Bahia->index[3].i = 14;   Bahia->index[3].j = 28;
	Bahia->index[4].i = 14;   Bahia->index[4].j = 29;
	Bahia->index[5].i = 14;   Bahia->index[5].j = 30;
	Bahia->index[6].i = 14;   Bahia->index[6].j = 31;
	Bahia->index[7].i = 14;   Bahia->index[7].j = 32;
	Bahia->index[8].i = 15;   Bahia->index[8].j = 26;
	Bahia->index[9].i = 15;   Bahia->index[9].j = 27;
	Bahia->index[10].i = 15;  Bahia->index[10].j = 28;
	Bahia->index[11].i = 15;  Bahia->index[11].j = 29;
	Bahia->index[12].i = 15;  Bahia->index[12].j = 30;
	Bahia->index[13].i = 15;  Bahia->index[13].j = 31;
	Bahia->index[14].i = 15;  Bahia->index[14].j = 32;
	Bahia->index[15].i = 16;  Bahia->index[15].j = 26;
	Bahia->index[16].i = 16;  Bahia->index[16].j = 27;
	Bahia->index[17].i = 16;  Bahia->index[17].j = 28;
	Bahia->index[18].i = 16;  Bahia->index[18].j = 29;
	Bahia->index[19].i = 16;  Bahia->index[19].j = 30;
	Bahia->index[20].i = 16;  Bahia->index[20].j = 31;
	Bahia->index[21].i = 16;  Bahia->index[21].j = 32;
	Bahia->index[22].i = 17;  Bahia->index[22].j = 26;
	Bahia->index[23].i = 17;  Bahia->index[23].j = 27;
	Bahia->index[24].i = 17;  Bahia->index[24].j = 28;
	Bahia->index[25].i = 17;  Bahia->index[25].j = 29;
	Bahia->index[26].i = 17;  Bahia->index[26].j = 30;
	Bahia->index[27].i = 17;  Bahia->index[27].j = 31;
	Bahia->index[28].i = 18;  Bahia->index[28].j = 29;
	Bahia->index[29].i = 18;  Bahia->index[29].j = 30;
	Bahia->index[30].i = 18;  Bahia->index[30].j = 31;
	Bahia->index[31].i = 19;  Bahia->index[31].j = 31;
	Bahia->index[32].i = 20;  Bahia->index[32].j = 30;
	Bahia->index[33].i = 20;  Bahia->index[33].j = 31;
#pragma endregion

#pragma region PIAUI
	Piaui->myIndexPosition = 20; //posicao no vetor ESTADOS de nomes na classe objects.h
	Piaui->index[0].i = 8;   Piaui->index[0].j = 29;
	Piaui->index[1].i = 9;   Piaui->index[1].j = 28;
	Piaui->index[2].i = 9;   Piaui->index[2].j = 29;
	Piaui->index[3].i = 10;  Piaui->index[3].j = 28;
	Piaui->index[4].i = 10;  Piaui->index[4].j = 29;
	Piaui->index[5].i = 11;  Piaui->index[5].j = 27;
	Piaui->index[6].i = 11;  Piaui->index[6].j = 28;
	Piaui->index[7].i = 11;  Piaui->index[7].j = 29;
	Piaui->index[8].i = 12;  Piaui->index[8].j = 26;
	Piaui->index[9].i = 12;  Piaui->index[9].j = 27;
	Piaui->index[10].i = 12; Piaui->index[10].j = 28;
	Piaui->index[11].i = 12; Piaui->index[11].j = 29;
	Piaui->index[12].i = 13; Piaui->index[12].j = 26;
	Piaui->index[13].i = 13; Piaui->index[13].j = 27;
	Piaui->index[14].i = 13; Piaui->index[14].j = 28;
	Piaui->index[15].i = 14; Piaui->index[15].j = 26;
	Piaui->index[16].i = 14; Piaui->index[16].j = 27;
#pragma endregion

#pragma region MARANHAO
	Maranhao->myIndexPosition = 19; //posicao no vetor ESTADOS de nomes na classe objects.h
	Maranhao->index[0].i = 7;   Maranhao->index[0].j = 26;
	Maranhao->index[1].i = 7;   Maranhao->index[1].j = 27;
	Maranhao->index[2].i = 7;   Maranhao->index[2].j = 28;
	Maranhao->index[3].i = 8;   Maranhao->index[3].j = 25;
	Maranhao->index[4].i = 8;   Maranhao->index[4].j = 26;
	Maranhao->index[5].i = 8;   Maranhao->index[5].j = 27;
	Maranhao->index[6].i = 8;   Maranhao->index[6].j = 28;
	Maranhao->index[7].i = 9;   Maranhao->index[7].j = 24;
	Maranhao->index[8].i = 9;   Maranhao->index[8].j = 25;
	Maranhao->index[9].i = 9;   Maranhao->index[9].j = 26;
	Maranhao->index[10].i = 9;  Maranhao->index[10].j = 27;
	Maranhao->index[11].i = 10; Maranhao->index[11].j = 25;
	Maranhao->index[12].i = 10; Maranhao->index[12].j = 26;
	Maranhao->index[13].i = 10; Maranhao->index[13].j = 27;
	Maranhao->index[14].i = 11; Maranhao->index[14].j = 25;
	Maranhao->index[15].i = 11; Maranhao->index[15].j = 26;
	Maranhao->index[16].i = 12; Maranhao->index[16].j = 25;
	Maranhao->index[17].i = 13; Maranhao->index[17].j = 25;
#pragma endregion

#pragma region ESPIRITO SANTO
	EspiritoSanto->myIndexPosition = 6; //posicao no vetor ESTADOS de nomes na classe objects.h
	EspiritoSanto->index[0].i = 21; EspiritoSanto->index[0].j = 30;
	EspiritoSanto->index[1].i = 22; EspiritoSanto->index[1].j = 30;
	EspiritoSanto->index[2].i = 22; EspiritoSanto->index[2].j = 31;
	EspiritoSanto->index[3].i = 23; EspiritoSanto->index[3].j = 29;
	EspiritoSanto->index[4].i = 23; EspiritoSanto->index[4].j = 30;
	EspiritoSanto->index[5].i = 24; EspiritoSanto->index[5].j = 30;
#pragma endregion

#pragma region RIO DE JANEIRO
	RioDeJaneiro->myIndexPosition = 4; //posicao no vetor ESTADOS de nomes na classe objects.h
	RioDeJaneiro->index[0].i = 24; RioDeJaneiro->index[0].j = 27;
	RioDeJaneiro->index[1].i = 24; RioDeJaneiro->index[1].j = 28;
	RioDeJaneiro->index[2].i = 24; RioDeJaneiro->index[2].j = 29;
	RioDeJaneiro->index[3].i = 25; RioDeJaneiro->index[3].j = 27;
	RioDeJaneiro->index[4].i = 25; RioDeJaneiro->index[4].j = 28;
	RioDeJaneiro->index[5].i = 25; RioDeJaneiro->index[5].j = 29;
#pragma endregion

#pragma region MINAS GERAIS
	MinasGerais->myIndexPosition = 5; //posicao no vetor ESTADOS de nomes na classe objects.h
	MinasGerais->index[0].i = 18;   MinasGerais->index[0].j = 25;
	MinasGerais->index[1].i = 18;   MinasGerais->index[1].j = 26;
	MinasGerais->index[2].i = 18;   MinasGerais->index[2].j = 27;
	MinasGerais->index[3].i = 18;   MinasGerais->index[3].j = 28;
	MinasGerais->index[4].i = 19;   MinasGerais->index[4].j = 25;
	MinasGerais->index[5].i = 19;   MinasGerais->index[5].j = 26;
	MinasGerais->index[6].i = 19;   MinasGerais->index[6].j = 27;
	MinasGerais->index[7].i = 19;   MinasGerais->index[7].j = 28;
	MinasGerais->index[8].i = 19;   MinasGerais->index[8].j = 29;
	MinasGerais->index[9].i = 19;   MinasGerais->index[9].j = 30;
	MinasGerais->index[10].i = 20;  MinasGerais->index[10].j = 25;
	MinasGerais->index[11].i = 20;  MinasGerais->index[11].j = 26;
	MinasGerais->index[12].i = 20;  MinasGerais->index[12].j = 27;
	MinasGerais->index[13].i = 20;  MinasGerais->index[13].j = 28;
	MinasGerais->index[14].i = 20;  MinasGerais->index[14].j = 29;
	MinasGerais->index[15].i = 21;  MinasGerais->index[15].j = 22;
	MinasGerais->index[16].i = 21;  MinasGerais->index[16].j = 23;
	MinasGerais->index[17].i = 21;  MinasGerais->index[17].j = 24;
	MinasGerais->index[18].i = 21;  MinasGerais->index[18].j = 25;
	MinasGerais->index[19].i = 21;  MinasGerais->index[19].j = 26;
	MinasGerais->index[20].i = 21;  MinasGerais->index[20].j = 27;
	MinasGerais->index[21].i = 21;  MinasGerais->index[21].j = 28;
	MinasGerais->index[22].i = 21;  MinasGerais->index[22].j = 29;
	MinasGerais->index[23].i = 22;  MinasGerais->index[23].j = 22;
	MinasGerais->index[24].i = 22;  MinasGerais->index[24].j = 23;
	MinasGerais->index[25].i = 22;  MinasGerais->index[25].j = 24;
	MinasGerais->index[26].i = 22;  MinasGerais->index[26].j = 25;
	MinasGerais->index[27].i = 22;  MinasGerais->index[27].j = 26;
	MinasGerais->index[28].i = 22;  MinasGerais->index[28].j = 27;
	MinasGerais->index[29].i = 22;  MinasGerais->index[29].j = 28;
	MinasGerais->index[30].i = 22;  MinasGerais->index[30].j = 29;
	MinasGerais->index[31].i = 23;  MinasGerais->index[31].j = 25;
	MinasGerais->index[32].i = 23;  MinasGerais->index[32].j = 26;
	MinasGerais->index[33].i = 23;  MinasGerais->index[33].j = 27;
	MinasGerais->index[34].i = 23;  MinasGerais->index[34].j = 28;
	MinasGerais->index[35].i = 24;  MinasGerais->index[35].j = 25;
	MinasGerais->index[36].i = 24;  MinasGerais->index[36].j = 26;
	MinasGerais->index[37].i = 24;  MinasGerais->index[37].j = 28;
	MinasGerais->index[38].i = 25;  MinasGerais->index[38].j = 26;
#pragma endregion

#pragma region SAO PAULO
	SaoPaulo->myIndexPosition = 3; //posicao no vetor ESTADOS de nomes na classe objects.h
	SaoPaulo->index[0].i = 23;   SaoPaulo->index[0].j = 21;
	SaoPaulo->index[1].i = 23;   SaoPaulo->index[1].j = 22;
	SaoPaulo->index[2].i = 23;   SaoPaulo->index[2].j = 23;
	SaoPaulo->index[3].i = 23;   SaoPaulo->index[3].j = 24;
	SaoPaulo->index[4].i = 24;   SaoPaulo->index[4].j = 20;
	SaoPaulo->index[5].i = 24;   SaoPaulo->index[5].j = 21;
	SaoPaulo->index[6].i = 24;   SaoPaulo->index[6].j = 22;
	SaoPaulo->index[7].i = 24;   SaoPaulo->index[7].j = 23;
	SaoPaulo->index[8].i = 24;   SaoPaulo->index[8].j = 24;
	SaoPaulo->index[9].i = 25;   SaoPaulo->index[9].j = 20;
	SaoPaulo->index[10].i = 25; SaoPaulo->index[10].j = 21;
	SaoPaulo->index[11].i = 25; SaoPaulo->index[11].j = 22;
	SaoPaulo->index[12].i = 25; SaoPaulo->index[12].j = 23;
	SaoPaulo->index[13].i = 25; SaoPaulo->index[13].j = 24;
	SaoPaulo->index[14].i = 25; SaoPaulo->index[14].j = 25;
	SaoPaulo->index[15].i = 26; SaoPaulo->index[15].j = 22;
	SaoPaulo->index[16].i = 26; SaoPaulo->index[16].j = 23;
	SaoPaulo->index[17].i = 26; SaoPaulo->index[17].j = 24;
	SaoPaulo->index[18].i = 26; SaoPaulo->index[18].j = 25;
	SaoPaulo->index[19].i = 26; SaoPaulo->index[19].j = 26;
	SaoPaulo->index[20].i = 27; SaoPaulo->index[20].j = 23;
	SaoPaulo->index[21].i = 27; SaoPaulo->index[21].j = 24;
#pragma endregion

#pragma region PARANA
	Parana->myIndexPosition = 2; //posicao no vetor ESTADOS de nomes na classe objects.h
	Parana->index[0].i = 26;   Parana->index[0].j = 19;
	Parana->index[1].i = 26;   Parana->index[1].j = 19;
	Parana->index[2].i = 26;   Parana->index[2].j = 20;
	Parana->index[3].i = 26;   Parana->index[3].j = 21;
	Parana->index[4].i = 27;   Parana->index[4].j = 18;
	Parana->index[5].i = 27;   Parana->index[5].j = 19;
	Parana->index[6].i = 27;   Parana->index[6].j = 20;
	Parana->index[7].i = 27;   Parana->index[7].j = 21;
	Parana->index[8].i = 27;   Parana->index[8].j = 22;
	Parana->index[9].i = 28;   Parana->index[9].j = 18;
	Parana->index[10].i = 28;   Parana->index[10].j = 19;
	Parana->index[11].i = 28;   Parana->index[11].j = 20;
	Parana->index[12].i = 28;   Parana->index[12].j = 21;
	Parana->index[13].i = 28;   Parana->index[13].j = 22;
	Parana->index[14].i = 28;   Parana->index[14].j = 23;
#pragma endregion	

#pragma region RIO GRAND DO SUL
	RioGrandeDoSul->myIndexPosition = 0; //posicao no vetor ESTADOS de nomes na classe objects.h
	RioGrandeDoSul->index[0].i = 30;   RioGrandeDoSul->index[0].j = 18;
	RioGrandeDoSul->index[1].i = 30;   RioGrandeDoSul->index[1].j = 19;
	RioGrandeDoSul->index[2].i = 30;   RioGrandeDoSul->index[2].j = 20;
	RioGrandeDoSul->index[3].i = 31;   RioGrandeDoSul->index[3].j = 17;
	RioGrandeDoSul->index[4].i = 31;   RioGrandeDoSul->index[4].j = 18;
	RioGrandeDoSul->index[5].i = 31;   RioGrandeDoSul->index[5].j = 19;
	RioGrandeDoSul->index[6].i = 31;   RioGrandeDoSul->index[6].j = 20;
	RioGrandeDoSul->index[7].i = 31;   RioGrandeDoSul->index[7].j = 21;
	RioGrandeDoSul->index[8].i = 32;   RioGrandeDoSul->index[8].j = 16;
	RioGrandeDoSul->index[9].i = 32;   RioGrandeDoSul->index[9].j = 17;
	RioGrandeDoSul->index[10].i = 32;   RioGrandeDoSul->index[10].j = 18;
	RioGrandeDoSul->index[11].i = 32;   RioGrandeDoSul->index[11].j = 19;
	RioGrandeDoSul->index[12].i = 32;   RioGrandeDoSul->index[12].j = 20;
	RioGrandeDoSul->index[13].i = 32;   RioGrandeDoSul->index[13].j = 21;
	RioGrandeDoSul->index[14].i = 33;   RioGrandeDoSul->index[14].j = 17;
	RioGrandeDoSul->index[15].i = 33;   RioGrandeDoSul->index[15].j = 18;
	RioGrandeDoSul->index[16].i = 33;   RioGrandeDoSul->index[16].j = 19;
	RioGrandeDoSul->index[17].i = 33;   RioGrandeDoSul->index[17].j = 20;
	RioGrandeDoSul->index[18].i = 33;   RioGrandeDoSul->index[18].j = 21;
	RioGrandeDoSul->index[19].i = 34;   RioGrandeDoSul->index[19].j = 18;
	RioGrandeDoSul->index[20].i = 34;   RioGrandeDoSul->index[20].j = 19;
	RioGrandeDoSul->index[21].i = 34;   RioGrandeDoSul->index[21].j = 20;
#pragma endregion

#pragma region TOCANTINS
	Tocantins->myIndexPosition = 11; //posicao no vetor ESTADOS de nomes na classe objects.h
	Tocantins->index[0].i = 10;   Tocantins->index[0].j = 24;
	Tocantins->index[1].i = 11;   Tocantins->index[1].j = 23;
	Tocantins->index[2].i = 11;   Tocantins->index[2].j = 24;
	Tocantins->index[3].i = 12;   Tocantins->index[3].j = 23;
	Tocantins->index[4].i = 12;   Tocantins->index[4].j = 24;
	Tocantins->index[5].i = 13;   Tocantins->index[5].j = 22;
	Tocantins->index[6].i = 13;   Tocantins->index[6].j = 23;
	Tocantins->index[7].i = 13;   Tocantins->index[7].j = 24;
	Tocantins->index[8].i = 14;   Tocantins->index[8].j = 22;
	Tocantins->index[9].i = 14;   Tocantins->index[9].j = 23;
	Tocantins->index[10].i = 14;   Tocantins->index[10].j = 24;
	Tocantins->index[11].i = 14;   Tocantins->index[11].j = 25;
	Tocantins->index[12].i = 15;   Tocantins->index[12].j = 22;
	Tocantins->index[13].i = 15;   Tocantins->index[13].j = 23;
	Tocantins->index[14].i = 15;   Tocantins->index[14].j = 24;
	Tocantins->index[15].i = 15;   Tocantins->index[15].j = 25;
	Tocantins->index[16].i = 16;   Tocantins->index[16].j = 22;
	Tocantins->index[17].i = 16;   Tocantins->index[17].j = 23;
	Tocantins->index[18].i = 16;   Tocantins->index[18].j = 24;
	Tocantins->index[19].i = 16;   Tocantins->index[19].j = 25;
#pragma endregion

#pragma region RONDONIA
	Rondonia->myIndexPosition = 12; //posicao no vetor ESTADOS de nomes na classe objects.h
	Rondonia->index[0].i = 12;   Rondonia->index[0].j = 11;
	Rondonia->index[1].i = 13;   Rondonia->index[1].j = 9;
	Rondonia->index[2].i = 13;   Rondonia->index[2].j = 10;
	Rondonia->index[3].i = 13;   Rondonia->index[3].j = 11;
	Rondonia->index[4].i = 14;   Rondonia->index[4].j = 9;
	Rondonia->index[5].i = 14;   Rondonia->index[5].j = 10;
	Rondonia->index[6].i = 14;   Rondonia->index[6].j = 11;
	Rondonia->index[7].i = 15;   Rondonia->index[7].j = 9;
	Rondonia->index[8].i = 15;   Rondonia->index[8].j = 10;
	Rondonia->index[9].i = 15;   Rondonia->index[9].j = 11;
	Rondonia->index[10].i = 15;   Rondonia->index[10].j = 12;
	Rondonia->index[11].i = 15;   Rondonia->index[11].j = 13;
	Rondonia->index[12].i = 16;   Rondonia->index[12].j = 10;
	Rondonia->index[13].i = 16;   Rondonia->index[13].j = 11;
	Rondonia->index[14].i = 16;   Rondonia->index[14].j = 12;
	Rondonia->index[15].i = 16;   Rondonia->index[15].j = 13;

#pragma endregion

#pragma region RORAIMA
	Roraima->myIndexPosition = 15; //posicao no vetor ESTADOS de nomes na classe objects.h
	Roraima->index[0].i = 0;    Roraima->index[0].j = 13;
	Roraima->index[1].i = 1;    Roraima->index[1].j = 10;
	Roraima->index[2].i = 1;    Roraima->index[2].j = 11;
	Roraima->index[3].i = 1;    Roraima->index[3].j = 12;
	Roraima->index[4].i = 1;    Roraima->index[4].j = 13;
	Roraima->index[5].i = 2;    Roraima->index[5].j = 10;
	Roraima->index[6].i = 2;    Roraima->index[6].j = 11;
	Roraima->index[7].i = 2;    Roraima->index[7].j = 12;
	Roraima->index[8].i = 2;    Roraima->index[8].j = 13;
	Roraima->index[9].i = 3;    Roraima->index[9].j = 11;
	Roraima->index[10].i = 3;   Roraima->index[10].j = 12;
	Roraima->index[11].i = 3;   Roraima->index[11].j = 13;
	Roraima->index[12].i = 3;   Roraima->index[12].j = 14;
	Roraima->index[13].i = 4;   Roraima->index[13].j = 11;
	Roraima->index[14].i = 4;   Roraima->index[14].j = 12;
	Roraima->index[15].i = 4;   Roraima->index[15].j = 13;
	Roraima->index[16].i = 4;   Roraima->index[16].j = 14;
	Roraima->index[17].i = 5;   Roraima->index[17].j = 11;

#pragma endregion

#pragma region AMAPA
	Amapa->myIndexPosition = 17; //posicao no vetor ESTADOS de nomes na classe objects.h
	Amapa->index[0].i = 1; Amapa->index[0].j = 20;
	Amapa->index[1].i = 1; Amapa->index[1].j = 21;
	Amapa->index[2].i = 2; Amapa->index[2].j = 18;
	Amapa->index[3].i = 2; Amapa->index[3].j = 19;
	Amapa->index[4].i = 2; Amapa->index[4].j = 20;
	Amapa->index[5].i = 2; Amapa->index[5].j = 21;
	Amapa->index[6].i = 3; Amapa->index[6].j = 20;
	Amapa->index[7].i = 3; Amapa->index[7].j = 21;
	Amapa->index[8].i = 4; Amapa->index[8].j = 20;
	Amapa->index[9].i = 4; Amapa->index[9].j = 21;
	Amapa->index[10].i = 4; Amapa->index[10].j = 22;
	Amapa->index[11].i = 5; Amapa->index[11].j = 20;
#pragma endregion

#pragma region MATO GROSSO DO SUL
	MatoGrossoDoSul->myIndexPosition = 7; //posicao no vetor ESTADOS de nomes na classe objects.h
	MatoGrossoDoSul->index[0].i = 20; 		MatoGrossoDoSul->index[0].j = 17;
	MatoGrossoDoSul->index[1].i = 20; 		MatoGrossoDoSul->index[1].j = 18;
	MatoGrossoDoSul->index[2].i = 21; 		MatoGrossoDoSul->index[2].j = 16;
	MatoGrossoDoSul->index[3].i = 21; 		MatoGrossoDoSul->index[3].j = 17;
	MatoGrossoDoSul->index[4].i = 21; 		MatoGrossoDoSul->index[4].j = 18;
	MatoGrossoDoSul->index[5].i = 21; 		MatoGrossoDoSul->index[5].j = 19;
	MatoGrossoDoSul->index[6].i = 22; 		MatoGrossoDoSul->index[6].j = 16;
	MatoGrossoDoSul->index[7].i = 22; 		MatoGrossoDoSul->index[7].j = 17;
	MatoGrossoDoSul->index[8].i = 22; 		MatoGrossoDoSul->index[8].j = 18;
	MatoGrossoDoSul->index[9].i = 22; 		MatoGrossoDoSul->index[9].j = 19;
	MatoGrossoDoSul->index[10].i = 22; 		MatoGrossoDoSul->index[10].j = 20;
	MatoGrossoDoSul->index[11].i = 22; 		MatoGrossoDoSul->index[11].j = 21;
	MatoGrossoDoSul->index[12].i = 23; 		MatoGrossoDoSul->index[12].j = 15;
	MatoGrossoDoSul->index[13].i = 23; 		MatoGrossoDoSul->index[13].j = 15;
	MatoGrossoDoSul->index[14].i = 23; 		MatoGrossoDoSul->index[14].j = 16;
	MatoGrossoDoSul->index[15].i = 23; 		MatoGrossoDoSul->index[15].j = 17;
	MatoGrossoDoSul->index[16].i = 23; 		MatoGrossoDoSul->index[16].j = 18;
	MatoGrossoDoSul->index[17].i = 23; 		MatoGrossoDoSul->index[17].j = 19;
	MatoGrossoDoSul->index[18].i = 23; 		MatoGrossoDoSul->index[18].j = 20;
	MatoGrossoDoSul->index[19].i = 24; 		MatoGrossoDoSul->index[19].j = 15;
	MatoGrossoDoSul->index[20].i = 24; 		MatoGrossoDoSul->index[20].j = 16;
	MatoGrossoDoSul->index[21].i = 24; 		MatoGrossoDoSul->index[21].j = 17;
	MatoGrossoDoSul->index[22].i = 24; 		MatoGrossoDoSul->index[22].j = 18;
	MatoGrossoDoSul->index[23].i = 24; 		MatoGrossoDoSul->index[23].j = 19;
	MatoGrossoDoSul->index[24].i = 25; 		MatoGrossoDoSul->index[24].j = 18;
	MatoGrossoDoSul->index[25].i = 26; 		MatoGrossoDoSul->index[25].j = 18;

#pragma endregion

#pragma region MATO GROSSO
	MatoGrosso->myIndexPosition = 10; //posicao no vetor ESTADOS de nomes na classe objects.h
	MatoGrosso->index[0].i = 13; 		MatoGrosso->index[0].j = 13;
	MatoGrosso->index[1].i = 13; 		MatoGrosso->index[1].j = 14;
	MatoGrosso->index[2].i = 13; 		MatoGrosso->index[2].j = 15;
	MatoGrosso->index[3].i = 13; 		MatoGrosso->index[3].j = 16;
	MatoGrosso->index[4].i = 14; 		MatoGrosso->index[4].j = 13;
	MatoGrosso->index[5].i = 14; 		MatoGrosso->index[5].j = 14;
	MatoGrosso->index[6].i = 14; 		MatoGrosso->index[6].j = 15;
	MatoGrosso->index[7].i = 14; 		MatoGrosso->index[7].j = 16;
	MatoGrosso->index[8].i = 14; 		MatoGrosso->index[8].j = 17;
	MatoGrosso->index[9].i = 14; 		MatoGrosso->index[9].j = 18;
	MatoGrosso->index[10].i = 14; 		MatoGrosso->index[10].j = 19;
	MatoGrosso->index[11].i = 14; 		MatoGrosso->index[11].j = 20;
	MatoGrosso->index[12].i = 14; 		MatoGrosso->index[12].j = 21;
	MatoGrosso->index[13].i = 15; 		MatoGrosso->index[13].j = 14;
	MatoGrosso->index[14].i = 15; 		MatoGrosso->index[14].j = 15;
	MatoGrosso->index[15].i = 15; 		MatoGrosso->index[15].j = 16;
	MatoGrosso->index[16].i = 15; 		MatoGrosso->index[16].j = 17;
	MatoGrosso->index[17].i = 15; 		MatoGrosso->index[17].j = 18;
	MatoGrosso->index[18].i = 15; 		MatoGrosso->index[18].j = 19;
	MatoGrosso->index[19].i = 15; 		MatoGrosso->index[19].j = 20;
	MatoGrosso->index[20].i = 15; 		MatoGrosso->index[20].j = 21;
	MatoGrosso->index[21].i = 16; 		MatoGrosso->index[21].j = 14;
	MatoGrosso->index[22].i = 16; 		MatoGrosso->index[22].j = 15;
	MatoGrosso->index[23].i = 16; 		MatoGrosso->index[23].j = 16;
	MatoGrosso->index[24].i = 16; 		MatoGrosso->index[24].j = 17;
	MatoGrosso->index[25].i = 16; 		MatoGrosso->index[25].j = 18;
	MatoGrosso->index[26].i = 16; 		MatoGrosso->index[26].j = 19;
	MatoGrosso->index[27].i = 16; 		MatoGrosso->index[27].j = 20;
	MatoGrosso->index[28].i = 16; 		MatoGrosso->index[28].j = 21;
	MatoGrosso->index[29].i = 17; 		MatoGrosso->index[29].j = 14;
	MatoGrosso->index[30].i = 17; 		MatoGrosso->index[30].j = 15;
	MatoGrosso->index[31].i = 17; 		MatoGrosso->index[31].j = 16;
	MatoGrosso->index[32].i = 17; 		MatoGrosso->index[32].j = 17;
	MatoGrosso->index[33].i = 17; 		MatoGrosso->index[33].j = 18;
	MatoGrosso->index[34].i = 17; 		MatoGrosso->index[34].j = 19;
	MatoGrosso->index[35].i = 17; 		MatoGrosso->index[35].j = 20;
	MatoGrosso->index[36].i = 17; 		MatoGrosso->index[36].j = 21;
	MatoGrosso->index[37].i = 18; 		MatoGrosso->index[37].j = 14;
	MatoGrosso->index[38].i = 18; 		MatoGrosso->index[38].j = 15;
	MatoGrosso->index[39].i = 18; 		MatoGrosso->index[39].j = 16;
	MatoGrosso->index[40].i = 18; 		MatoGrosso->index[40].j = 17;
	MatoGrosso->index[41].i = 18; 		MatoGrosso->index[41].j = 18;
	MatoGrosso->index[42].i = 18; 		MatoGrosso->index[42].j = 19;
	MatoGrosso->index[43].i = 18; 		MatoGrosso->index[43].j = 20;
	MatoGrosso->index[44].i = 19; 		MatoGrosso->index[44].j = 14;
	MatoGrosso->index[45].i = 19; 		MatoGrosso->index[45].j = 15;
	MatoGrosso->index[46].i = 19; 		MatoGrosso->index[46].j = 16;
	MatoGrosso->index[47].i = 19; 		MatoGrosso->index[47].j = 17;
	MatoGrosso->index[48].i = 19; 		MatoGrosso->index[48].j = 18;
	MatoGrosso->index[49].i = 19; 		MatoGrosso->index[49].j = 19;
	MatoGrosso->index[50].i = 20; 		MatoGrosso->index[50].j = 15;
	MatoGrosso->index[51].i = 20; 		MatoGrosso->index[51].j = 16;
	MatoGrosso->index[52].i = 20; 		MatoGrosso->index[52].j = 19;

	MatoGrosso->index[53].i = 13; 		MatoGrosso->index[53].j = 12;
	MatoGrosso->index[54].i = 14; 		MatoGrosso->index[54].j = 12;
#pragma endregion

#pragma region PARA
	Para->myIndexPosition = 16; //posicao no vetor ESTADOS de nomes na classe objects.h
	Para->index[0].i = 2; 		Para->index[0].j = 17;
	Para->index[1].i = 3; 		Para->index[1].j = 15;
	Para->index[2].i = 3; 		Para->index[2].j = 16;
	Para->index[3].i = 3; 		Para->index[3].j = 17;
	Para->index[4].i = 3; 		Para->index[4].j = 18;
	Para->index[5].i = 3; 		Para->index[5].j = 19;
	Para->index[6].i = 4; 		Para->index[6].j = 15;
	Para->index[7].i = 4; 		Para->index[7].j = 16;
	Para->index[8].i = 4; 		Para->index[8].j = 17;
	Para->index[9].i = 4; 		Para->index[9].j = 18;
	Para->index[10].i = 4; 		Para->index[10].j = 19;
	Para->index[11].i = 4; 		Para->index[11].j = 21;
	Para->index[12].i = 4; 		Para->index[12].j = 22;
	Para->index[13].i = 5; 		Para->index[13].j = 15;
	Para->index[14].i = 5; 		Para->index[14].j = 16;
	Para->index[15].i = 5; 		Para->index[15].j = 17;
	Para->index[16].i = 5; 		Para->index[16].j = 18;
	Para->index[17].i = 5; 		Para->index[17].j = 19;
	Para->index[18].i = 5; 		Para->index[18].j = 21;
	Para->index[19].i = 5; 		Para->index[19].j = 22;
	Para->index[20].i = 5; 		Para->index[20].j = 23;
	Para->index[21].i = 6; 		Para->index[21].j = 15;
	Para->index[22].i = 6; 		Para->index[22].j = 16;
	Para->index[23].i = 6; 		Para->index[23].j = 17;
	Para->index[24].i = 6; 		Para->index[24].j = 18;
	Para->index[25].i = 6; 		Para->index[25].j = 19;
	Para->index[26].i = 6; 		Para->index[26].j = 20;
	Para->index[27].i = 6; 		Para->index[27].j = 21;
	Para->index[28].i = 6; 		Para->index[28].j = 22;
	Para->index[29].i = 6; 		Para->index[29].j = 23;
	Para->index[30].i = 6; 		Para->index[30].j = 24;
	Para->index[31].i = 6; 		Para->index[31].j = 25;
	Para->index[32].i = 7; 		Para->index[32].j = 17;
	Para->index[33].i = 7; 		Para->index[33].j = 18;
	Para->index[34].i = 7; 		Para->index[34].j = 19;
	Para->index[35].i = 7; 		Para->index[35].j = 20;
	Para->index[36].i = 7; 		Para->index[36].j = 21;
	Para->index[37].i = 7; 		Para->index[37].j = 22;
	Para->index[38].i = 7; 		Para->index[38].j = 23;
	Para->index[39].i = 7; 		Para->index[39].j = 24;
	Para->index[40].i = 7; 		Para->index[40].j = 25;
	Para->index[41].i = 8; 		Para->index[41].j = 17;
	Para->index[42].i = 8; 		Para->index[42].j = 18;
	Para->index[43].i = 8; 		Para->index[43].j = 19;
	Para->index[44].i = 8; 		Para->index[44].j = 20;
	Para->index[45].i = 8; 		Para->index[45].j = 21;
	Para->index[46].i = 8; 		Para->index[46].j = 22;
	Para->index[47].i = 8; 		Para->index[47].j = 23;
	Para->index[48].i = 8; 		Para->index[48].j = 24;
	Para->index[49].i = 9; 		Para->index[49].j = 16;
	Para->index[50].i = 9; 		Para->index[50].j = 17;
	Para->index[51].i = 9; 		Para->index[51].j = 18;
	Para->index[52].i = 9; 		Para->index[52].j = 19;
	Para->index[53].i = 9; 		Para->index[53].j = 20;
	Para->index[54].i = 9; 		Para->index[54].j = 21;
	Para->index[55].i = 9; 		Para->index[55].j = 22;
	Para->index[56].i = 9; 		Para->index[56].j = 23;
	Para->index[57].i = 10; 	Para->index[57].j = 16;
	Para->index[58].i = 10; 	Para->index[58].j = 17;
	Para->index[59].i = 10; 	Para->index[59].j = 18;
	Para->index[60].i = 10; 	Para->index[60].j = 19;
	Para->index[61].i = 10; 	Para->index[61].j = 20;
	Para->index[62].i = 10;		Para->index[62].j = 21;
	Para->index[63].i = 10;		Para->index[63].j = 22;
	Para->index[64].i = 10; 	Para->index[64].j = 23;
	Para->index[65].i = 11; 	Para->index[65].j = 15;
	Para->index[66].i = 11; 	Para->index[66].j = 16;
	Para->index[67].i = 11; 	Para->index[67].j = 17;
	Para->index[68].i = 11; 	Para->index[68].j = 18;
	Para->index[69].i = 11; 	Para->index[69].j = 19;
	Para->index[70].i = 11; 	Para->index[70].j = 20;
	Para->index[71].i = 11; 	Para->index[71].j = 21;
	Para->index[72].i = 11; 	Para->index[72].j = 22;
	Para->index[73].i = 12; 	Para->index[73].j = 16;
	Para->index[74].i = 12; 	Para->index[74].j = 17;
	Para->index[75].i = 12; 	Para->index[75].j = 18;
	Para->index[76].i = 12; 	Para->index[76].j = 19;
	Para->index[77].i = 12; 	Para->index[77].j = 20;
	Para->index[78].i = 12; 	Para->index[78].j = 21;
	Para->index[79].i = 12; 	Para->index[79].j = 22;
	Para->index[80].i = 13; 	Para->index[80].j = 16;
	Para->index[81].i = 13; 	Para->index[81].j = 17;
	Para->index[82].i = 13; 	Para->index[82].j = 18;
	Para->index[83].i = 13; 	Para->index[83].j = 19;
	Para->index[84].i = 13; 	Para->index[84].j = 20;
	Para->index[85].i = 13; 	Para->index[85].j = 21;

	Para->index[86].i = 10; 	Para->index[86].j = 15;
#pragma endregion

#pragma region AMAZONAS
	Amazonas->myIndexPosition = 14; //posicao no vetor ESTADOS de nomes na classe objects.h
	Amazonas->index[0].i = 3; 		Amazonas->index[0].j = 4;
	Amazonas->index[1].i = 3; 		Amazonas->index[1].j = 5;
	Amazonas->index[2].i = 3; 		Amazonas->index[2].j = 6;
	Amazonas->index[3].i = 3; 		Amazonas->index[3].j = 7;
	Amazonas->index[4].i = 3; 		Amazonas->index[4].j = 8;
	Amazonas->index[5].i = 3; 		Amazonas->index[5].j = 9;
	Amazonas->index[6].i = 3; 		Amazonas->index[6].j = 10;
	Amazonas->index[7].i = 4; 		Amazonas->index[7].j = 5;
	Amazonas->index[8].i = 4; 		Amazonas->index[8].j = 6;
	Amazonas->index[9].i = 4; 		Amazonas->index[9].j = 7;
	Amazonas->index[10].i = 4; 		Amazonas->index[10].j = 8;
	Amazonas->index[11].i = 4; 		Amazonas->index[11].j = 9;
	Amazonas->index[12].i = 4; 		Amazonas->index[12].j = 10;
	Amazonas->index[13].i = 5; 		Amazonas->index[13].j = 5;
	Amazonas->index[14].i = 5; 		Amazonas->index[14].j = 6;
	Amazonas->index[15].i = 5; 		Amazonas->index[15].j = 7;
	Amazonas->index[16].i = 5; 		Amazonas->index[16].j = 8;
	Amazonas->index[17].i = 5; 		Amazonas->index[17].j = 9;
	Amazonas->index[18].i = 5; 		Amazonas->index[18].j = 10;
	Amazonas->index[19].i = 5; 		Amazonas->index[19].j = 12;
	Amazonas->index[20].i = 5; 		Amazonas->index[20].j = 13;
	Amazonas->index[21].i = 5; 		Amazonas->index[21].j = 14;
	Amazonas->index[22].i = 6; 		Amazonas->index[22].j = 5;
	Amazonas->index[23].i = 6; 		Amazonas->index[23].j = 6;
	Amazonas->index[24].i = 6; 		Amazonas->index[24].j = 7;
	Amazonas->index[25].i = 6; 		Amazonas->index[25].j = 8;
	Amazonas->index[26].i = 6; 		Amazonas->index[26].j = 9;
	Amazonas->index[27].i = 6; 		Amazonas->index[27].j = 10;
	Amazonas->index[28].i = 6; 		Amazonas->index[28].j = 11;
	Amazonas->index[29].i = 6; 		Amazonas->index[29].j = 12;
	Amazonas->index[30].i = 6; 		Amazonas->index[30].j = 13;
	Amazonas->index[31].i = 6; 		Amazonas->index[31].j = 14;
	Amazonas->index[32].i = 6; 		Amazonas->index[32].j = 15;
	Amazonas->index[33].i = 7; 		Amazonas->index[33].j = 5;
	Amazonas->index[34].i = 7; 		Amazonas->index[34].j = 6;
	Amazonas->index[35].i = 7; 		Amazonas->index[35].j = 7;
	Amazonas->index[36].i = 7; 		Amazonas->index[36].j = 8;
	Amazonas->index[37].i = 7; 		Amazonas->index[37].j = 9;
	Amazonas->index[38].i = 7; 		Amazonas->index[38].j = 10;
	Amazonas->index[39].i = 7; 		Amazonas->index[39].j = 11;
	Amazonas->index[40].i = 7; 		Amazonas->index[40].j = 12;
	Amazonas->index[41].i = 7; 		Amazonas->index[41].j = 13;
	Amazonas->index[42].i = 7; 		Amazonas->index[42].j = 14;
	Amazonas->index[43].i = 7;  	Amazonas->index[43].j = 15;
	Amazonas->index[44].i = 7;  	Amazonas->index[44].j = 16;
	Amazonas->index[45].i = 8;  	Amazonas->index[45].j = 4;
	Amazonas->index[46].i = 8;  	Amazonas->index[46].j = 5;
	Amazonas->index[47].i = 8;  	Amazonas->index[47].j = 6;
	Amazonas->index[48].i = 8;		Amazonas->index[48].j = 7;
	Amazonas->index[49].i = 8;		Amazonas->index[49].j = 8;
	Amazonas->index[50].i = 8; 	    Amazonas->index[50].j = 9;
	Amazonas->index[51].i = 8;		Amazonas->index[51].j = 10;
	Amazonas->index[52].i = 8;		Amazonas->index[52].j = 11;
	Amazonas->index[53].i = 8;		Amazonas->index[53].j = 12;
	Amazonas->index[54].i = 8; 		Amazonas->index[54].j = 13;
	Amazonas->index[55].i = 8;		Amazonas->index[55].j = 14;
	Amazonas->index[56].i = 8;		Amazonas->index[56].j = 15;
	Amazonas->index[57].i = 9;		Amazonas->index[57].j = 2;
	Amazonas->index[58].i = 9;		Amazonas->index[58].j = 3;
	Amazonas->index[59].i = 9;		Amazonas->index[59].j = 4;
	Amazonas->index[60].i = 9;		Amazonas->index[60].j = 5;
	Amazonas->index[61].i = 9;		Amazonas->index[61].j = 6;
	Amazonas->index[62].i = 9;		Amazonas->index[62].j = 7;
	Amazonas->index[63].i = 9;		Amazonas->index[63].j = 8;
	Amazonas->index[64].i = 9;		Amazonas->index[64].j = 9;
	Amazonas->index[65].i = 9;		Amazonas->index[65].j = 10;
	Amazonas->index[66].i = 9;	 	Amazonas->index[66].j = 11;
	Amazonas->index[67].i = 9;		Amazonas->index[67].j = 12;
	Amazonas->index[68].i = 9;		Amazonas->index[68].j = 13;
	Amazonas->index[69].i = 9;		Amazonas->index[69].j = 14;
	Amazonas->index[70].i = 9;		Amazonas->index[70].j = 15;
	Amazonas->index[71].i = 10; 	Amazonas->index[71].j = 2;
	Amazonas->index[72].i = 10; 	Amazonas->index[72].j = 3;
	Amazonas->index[73].i = 10; 	Amazonas->index[73].j = 4;
	Amazonas->index[74].i = 10; 	Amazonas->index[74].j = 5;
	Amazonas->index[75].i = 10; 	Amazonas->index[75].j = 6;
	Amazonas->index[76].i = 10; 	Amazonas->index[76].j = 7;
	Amazonas->index[77].i = 10; 	Amazonas->index[77].j = 8;
	Amazonas->index[78].i = 10; 	Amazonas->index[78].j = 9;
	Amazonas->index[79].i = 10; 	Amazonas->index[79].j = 10;
	Amazonas->index[80].i = 10; 	Amazonas->index[80].j = 11;
	Amazonas->index[81].i = 10; 	Amazonas->index[81].j = 12;
	Amazonas->index[82].i = 10; 	Amazonas->index[82].j = 13;
	Amazonas->index[83].i = 10; 	Amazonas->index[83].j = 14;
	Amazonas->index[84].i = 11; 	Amazonas->index[84].j = 2;
	Amazonas->index[85].i = 11; 	Amazonas->index[85].j = 3;
	Amazonas->index[86].i = 11; 	Amazonas->index[86].j = 4;
	Amazonas->index[87].i = 11; 	Amazonas->index[87].j = 5;
	Amazonas->index[88].i = 11; 	Amazonas->index[88].j = 6;
	Amazonas->index[89].i = 11; 	Amazonas->index[89].j = 7;
	Amazonas->index[90].i = 11; 	Amazonas->index[90].j = 8;
	Amazonas->index[91].i = 11; 	Amazonas->index[91].j = 9;
	Amazonas->index[92].i = 11; 	Amazonas->index[92].j = 10;
	Amazonas->index[93].i = 11; 	Amazonas->index[93].j = 11;
	Amazonas->index[94].i = 11; 	Amazonas->index[94].j = 12;
	Amazonas->index[95].i = 11; 	Amazonas->index[95].j = 13;
	Amazonas->index[96].i = 11; 	Amazonas->index[96].j = 14;
	Amazonas->index[97].i = 12; 	Amazonas->index[97].j = 5;
	Amazonas->index[98].i = 12; 	Amazonas->index[98].j = 6;
	Amazonas->index[99].i = 12; 	Amazonas->index[99].j = 7;
	Amazonas->index[100].i = 12; 	Amazonas->index[100].j = 8;
	Amazonas->index[101].i = 12; 	Amazonas->index[101].j = 9;
	Amazonas->index[102].i = 12; 	Amazonas->index[102].j = 10;
	Amazonas->index[103].i = 12; 	Amazonas->index[103].j = 12;
	Amazonas->index[104].i = 12; 	Amazonas->index[104].j = 13;
	Amazonas->index[105].i = 12; 	Amazonas->index[105].j = 14;
	Amazonas->index[106].i = 13; 	Amazonas->index[106].j = 7;
	Amazonas->index[107].i = 13; 	Amazonas->index[107].j = 8;



#pragma endregion

}

void ResetJogador(Jogador * jogador, bool resetNome)
{
	jogador->acertos = 0;
	jogador->erros = 0;
	jogador->vidas = 12;
	jogador->pontos = 0;
	jogador->acertou = false;

	if (resetNome)
	{
		strcpy(jogador->nome, "");
		jogador->pronto = false;
	}
	
	int i;
	for (i = 0; i < 27; i++)
	{
		jogador->acertoPorIndex[i] = 0;
	}

	for (i = 0; i < 5; i++)
	{
		jogador->indexEstadosPerdidos[i] = -1;
	}
}
void ResetLista(Lista * lista)
{
	lista->heightLista = 0;
	lista->velocidade = 1.0f;
	lista->palavraAtual = NULL;
	free(lista->palavraAtual);
}

void UpdateLista(ALLEGRO_FONT * fontLista, Jogador * jogador, Lista * lista)
{
	// Caso a palavra tenha chegado na altura maxima devemos resetar a lista
	if (lista->isMaxHeight)
	{
		if (!clicouPause)
		{
			if (musicaTocando)
			{
				al_play_sample_instance(erroAudioInstance);
			}
			jogador->erros++;
			jogador->vidas--;
		}

		ResetLista(lista);
		jogador->acertou = false;
		jogador->combo = 0;
	}

	if (lista->palavraAtual == NULL)
	{
		SortPalavra(jogador, lista);
	}

	// Caso a altura da palavra seja menor que a altura do mapa devemos continuar a anima��o de "queda"
	if (lista->heightLista < HEIGHTMAPA - 30)
	{
		al_draw_textf(fontLista, lista->cor, WIDTHMAPA + 70, lista->velocidade + 100.0, 0, "%s", lista->palavraAtual);

		// Aumentamos a altura da lista de acordo com a velocidade para dar no��o de anima��o
		// isMaxHeigth permite sabermos que a palavra nao chegou ao final da lista, entao nao devemos reseta-la
		lista->heightLista = lista->velocidade + 10;
		lista->velocidade += 3.8f;
		lista->isMaxHeight = false;
	}
	else {
		al_draw_textf(fontLista, lista->cor, WIDTHMAPA + 70, lista->velocidade + 100.0, 0, "%s", lista->palavraAtual);

		// Chegamos ao final da lista, ent�o isMaxHeight � true
		lista->isMaxHeight = true;
	}
}
void GetColor(Lista * lista, int pontos)
{
	if (pontos >= 36000)
	{
		srand(time(NULL));
		int conjuntoCores = rand() % 5;

		switch (conjuntoCores)
		{
		case 0:
			lista->cor = ORANGE;
			break;
		case 1:
			lista->cor = PINK;
			break;
		case 2:
			lista->cor = PURPLE;
			break;
		case 3:
			lista->cor = GREEN;
			break;
		case 4:
			lista->cor = BLUE;
			break;
		default:
			break;
		}
	}
	else {
		if (lista->indexAtual >= 0 && lista->indexAtual <= 2)
		{
			lista->cor = BLUE;
		}
		else if (lista->indexAtual >= 3 && lista->indexAtual <= 6) {
			lista->cor = PINK;
		}
		else if (lista->indexAtual >= 7 && lista->indexAtual <= 10) {
			lista->cor = ORANGE;
		}
		else if (lista->indexAtual >= 11 && lista->indexAtual <= 17) {
			lista->cor = GREEN;
		}
		else if (lista->indexAtual >= 18 && lista->indexAtual <= 26) {
			lista->cor = PURPLE;
		}
	}	
}
void TiraEstado(Jogador * jogador)
{
	if (!perdeuEstado)
	{
		int i, j, maiorValor = -1, maiorIndex = 0;
		for (i = 0; i < 27; i++)
		{
			if (jogador->acertoPorIndex[i] > maiorValor)
			{
				maiorIndex = i;
				maiorValor = jogador->acertoPorIndex[i];
			}
		}

		for (i = 0; i < 5; i++)
		{
			if (jogador->indexEstadosPerdidos[i] < 0)
			{
				if (maiorValor == -1)
				{
					srand(time(NULL));
					int temp = rand() % 27;
					jogador->indexEstadosPerdidos[i] = temp;
				}
				else {
					jogador->indexEstadosPerdidos[i] = maiorIndex;
					jogador->acertoPorIndex[maiorIndex] = -1;
				}

				perdeuEstado = true;
				break;
			}
		}
	}
}
void ConcatenaLista(char * s1, char * s2, Lista * lista)
{
	lista->palavraAtual = malloc(strlen(s1) + strlen(s2) + 6);
	strcpy(lista->palavraAtual, s1);
	strcat(lista->palavraAtual, "    ");
	strcat(lista->palavraAtual, s2);
}

void SortPalavra(Jogador * jogador, Lista * lista)
{
	srand(time(NULL));
	int i;
	lista->indexAnterior = lista->indexAtual;
	lista->indexAtual = (rand() * 5) % 27;
	while (lista->indexAtual == jogador->indexEstadosPerdidos[0] || lista->indexAtual == jogador->indexEstadosPerdidos[1] ||
		   lista->indexAtual == jogador->indexEstadosPerdidos[2] || lista->indexAtual == jogador->indexEstadosPerdidos[3] || 
		   lista->indexAtual == jogador->indexEstadosPerdidos[4])
	{
		lista->indexAtual = (rand() * 5) % 27;
	}

	if (jogador->pontos <= 12000)
	{
		lista->palavraAtual = Estados[lista->indexAtual];
		GetColor(lista, jogador->pontos);
	}

	if (jogador->pontos > 12000 && jogador->pontos <= 19000)
	{
		int conjuntoEasy = (rand() * 5) % 3;
		GetColor(lista, jogador->pontos);

		switch (conjuntoEasy)
		{
		case 0:
			lista->palavraAtual = Estados[lista->indexAtual];
			break;
		case 1:
			ConcatenaLista(Siglas[lista->indexAtual], Estados[lista->indexAtual], lista);
			break;
		case 2:
			ConcatenaLista(Capitais[lista->indexAtual], Estados[lista->indexAtual], lista);
			break;
		default:
			break;
		}
	}

	if (jogador->pontos > 19000 && jogador->pontos <= 27000)
	{
		int conjuntoMedium = (rand() * 5) % 4;
		GetColor(lista, jogador->pontos);

		switch (conjuntoMedium)
		{
		case 0:
			lista->palavraAtual = Estados[lista->indexAtual];
			break;
		case 1:
			ConcatenaLista(Siglas[lista->indexAtual], Estados[lista->indexAtual], lista);
			break;
		case 2:
			ConcatenaLista(Capitais[lista->indexAtual], Estados[lista->indexAtual], lista);
			break;
		case 3:
			ConcatenaLista(Capitais[lista->indexAtual], Siglas[lista->indexAtual], lista);
			break;
		default:
			break;
		}
	}

	if (jogador->pontos > 27000)
	{
		int conjuntoHard = (rand() * 5) % 6;
		GetColor(lista, jogador->pontos);

		switch (conjuntoHard)
		{
		case 0:
			lista->palavraAtual = Estados[lista->indexAtual];
			break;
		case 1:
			lista->palavraAtual = Capitais[lista->indexAtual];
			break;
		case 2:
			lista->palavraAtual = Siglas[lista->indexAtual];
			break;
		case 3:
			ConcatenaLista(Siglas[lista->indexAtual], Estados[lista->indexAtual], lista);
			break;
		case 4:
			ConcatenaLista(Capitais[lista->indexAtual], Estados[lista->indexAtual], lista);
			break;
		case 5:
			ConcatenaLista(Capitais[lista->indexAtual], Siglas[lista->indexAtual], lista);
			break;
		default:
			break;
		}
	}
}
void SortPontos(Ranking * ranking, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		int temp = ranking->pontosTxt[i];
		char *tempString = ranking->nomesTxt[i];
		int j = i;

		while (j > 0 && temp > ranking->pontosTxt[j - 1])
		{
			ranking->pontosTxt[j] = ranking->pontosTxt[j - 1];
			ranking->nomesTxt[j] = ranking->nomesTxt[j - 1];
			j--;
		}

		ranking->pontosTxt[j] = temp;
		ranking->nomesTxt[j] = tempString;
	}
}

void GetUserInput(Jogador * jogador, ALLEGRO_EVENT ev)
{
	if (strlen(jogador->nome) <= 11)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_A:
			strcat(jogador->nome, "A");
			break;
		case ALLEGRO_KEY_B:
			strcat(jogador->nome, "B");
			break;
		case ALLEGRO_KEY_C:
			strcat(jogador->nome, "C");
			break;
		case ALLEGRO_KEY_D:
			strcat(jogador->nome, "D");
			break;
		case ALLEGRO_KEY_E:
			strcat(jogador->nome, "E");
			break;
		case ALLEGRO_KEY_F:
			strcat(jogador->nome, "F");
			break;
		case ALLEGRO_KEY_G:
			strcat(jogador->nome, "G");
			break;
		case ALLEGRO_KEY_H:
			strcat(jogador->nome, "H");
			break;
		case ALLEGRO_KEY_I:
			strcat(jogador->nome, "I");
			break;
		case ALLEGRO_KEY_J:
			strcat(jogador->nome, "J");
			break;
		case ALLEGRO_KEY_K:
			strcat(jogador->nome, "K");
			break;
		case ALLEGRO_KEY_L:
			strcat(jogador->nome, "L");
			break;
		case ALLEGRO_KEY_M:
			strcat(jogador->nome, "M");
			break;
		case ALLEGRO_KEY_N:
			strcat(jogador->nome, "N");
			break;
		case ALLEGRO_KEY_O:
			strcat(jogador->nome, "O");
			break;
		case ALLEGRO_KEY_P:
			strcat(jogador->nome, "P");
			break;
		case ALLEGRO_KEY_Q:
			strcat(jogador->nome, "Q");
			break;
		case ALLEGRO_KEY_R:
			strcat(jogador->nome, "R");
			break;
		case ALLEGRO_KEY_S:
			strcat(jogador->nome, "S");
			break;
		case ALLEGRO_KEY_T:
			strcat(jogador->nome, "T");
			break;
		case ALLEGRO_KEY_U:
			strcat(jogador->nome, "U");
			break;
		case ALLEGRO_KEY_V:
			strcat(jogador->nome, "V");
			break;
		case ALLEGRO_KEY_W:
			strcat(jogador->nome, "W");
			break;
		case ALLEGRO_KEY_X:
			strcat(jogador->nome, "X");
			break;
		case ALLEGRO_KEY_Y:
			strcat(jogador->nome, "Y");
			break;
		case ALLEGRO_KEY_Z:
			strcat(jogador->nome, "Z");
			break;
		case ALLEGRO_KEY_0:
			strcat(jogador->nome, "0");
			break;
		case ALLEGRO_KEY_1:
			strcat(jogador->nome, "1");
			break;
		case ALLEGRO_KEY_2:
			strcat(jogador->nome, "2");
			break;
		case ALLEGRO_KEY_3:
			strcat(jogador->nome, "3");
			break;
		case ALLEGRO_KEY_4:
			strcat(jogador->nome, "4");
			break;
		case ALLEGRO_KEY_5:
			strcat(jogador->nome, "5");
			break;
		case ALLEGRO_KEY_6:
			strcat(jogador->nome, "6");
			break;
		case ALLEGRO_KEY_7:
			strcat(jogador->nome, "7");
			break;
		case ALLEGRO_KEY_8:
			strcat(jogador->nome, "8");
			break;
		case ALLEGRO_KEY_9:
			strcat(jogador->nome, "9");
			break;
		case ALLEGRO_KEY_BACKSPACE:
			jogador->nome[strlen(jogador->nome) - 1] = '\0';
			break;
		default:
			break;
		}
	}
	else {
		if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
			jogador->nome[strlen(jogador->nome) - 1] = '\0';
		}			
	}
}
void SalvaPontuacao(FILE * rankingData, Jogador * jogador)
{
	char *rankingDataPath = GetFolderPath("/data/dadosRanking.txt");
	rankingData = fopen(rankingDataPath, "a");
	fprintf(rankingData, "%s\n%d\n", jogador->nome, jogador->pontos);
	fclose(rankingData);
	free(rankingDataPath);
}
void GetPontuacao(FILE * rankingData, Ranking * ranking)
{
	char *rankingDataPath = GetFolderPath("/data/dadosRanking.txt");

	int i;
	int j = 0;
	int k = 0;	
	ranking->totalLinhas = GetTotalLinhas(rankingData);

	rankingData = fopen(rankingDataPath, "r");

	for (i = 0; i < ranking->totalLinhas; i++)
	{
		if (i % 2 == 1)
		{
			fscanf(rankingData, "%d", &ranking->pontosTxt[j]);
			j++;
		}
		else {
			ranking->nomesTxt[k] = malloc(25 * sizeof(char));
			fscanf(rankingData, "%s", ranking->nomesTxt[k]);
			k++;
		}
	}

	fclose(rankingData);
	free(rankingDataPath);

	SortPontos(ranking, ranking->totalLinhas / 2);
}
char *GetFolderPath(char * path)
{
	char *formatedPath = malloc(strlen(al_get_current_directory()) + strlen(path) + 1);
	strcpy(formatedPath, "");
	strcat(formatedPath, al_get_current_directory());
	strcat(formatedPath, path);

	return formatedPath;
}
int GetTotalLinhas(FILE * rankingData)
{
	char *rankingDataPath = GetFolderPath("/data/dadosRanking.txt");
	int linhas = 0;

	rankingData = fopen(rankingDataPath, "r");

	while (!feof(rankingData)) {
		char enter = fgetc(rankingData);
		if (enter == '\n')
		{
			linhas++;
		}
	}
	fclose(rankingData);

	return linhas;
}

void JogadorAcertou(Jogador * jogador, Lista * lista, int pontuacao)
{
	if (!clicouPause)
	{
		if (musicaTocando)
		{
			al_play_sample_instance(acertoAudioInstance);
		}
		jogador->pontos += pontuacao;
		jogador->acertoPorIndex[lista->indexAtual] += 1;
		jogador->acertos++;
		jogador->combo++;

		if (jogador->combo == 10 && jogador->vidas < 12)
		{
			jogador->vidas++;	
		}

		if (jogador->combo >= 11)
		{
			jogador->combo = 0;
		}

		jogador->acertou = true;
		ResetLista(lista);
	}	
}
void JogadorErrou(Jogador * jogador, Lista * lista)
{
	if (!clicouPause)
	{
		if (musicaTocando)
		{
			al_play_sample_instance(erroAudioInstance);
		}
		jogador->erros++;
		jogador->vidas--;
		jogador->combo = 0;
		jogador->acertou = false;
		ResetLista(lista);
	}
}

void FreeNomeJogadores(Ranking * ranking)
{
	int i;
	for (i = 0; i < ranking->totalLinhas / 2; i++)
	{
		free(ranking->nomesTxt[i]);
	}
}
void FreeEstadosPaths(char *estadosCinzaPath[], char *estadosVerdesPath[], char *estadosVermelhosPath[], ALLEGRO_BITMAP *estadosCinza[], ALLEGRO_BITMAP *estadosVerdes[], ALLEGRO_BITMAP *estadosVermelhos[])
{
	int i;
	for (i = 0; i < 27; i++)
	{
		al_destroy_bitmap(estadosCinza[i]);
		al_destroy_bitmap(estadosVerdes[i]);
		al_destroy_bitmap(estadosVermelhos[i]);
		free(estadosCinzaPath[i]);
		free(estadosVerdesPath[i]);
		free(estadosVermelhosPath[i]);
	}
}

void DesenhaEstrelas(int pontos, ALLEGRO_BITMAP * estrela)
{
	if (pontos <= 12000)
	{
		al_draw_bitmap(estrela, (WIDTH / 2) - 10, (HEIGHT / 2) - 60, 0);
	}
	else if (pontos > 12000 && pontos <= 19000) {
		al_draw_bitmap(estrela, (WIDTH / 2) - 35, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) + 10, (HEIGHT / 2) - 60, 0);
	}
	else if (pontos > 19000 && pontos <= 27000) {
		al_draw_bitmap(estrela, (WIDTH / 2) - 65, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) - 17, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) + 30, (HEIGHT / 2) - 60, 0);
	}
	else if (pontos > 27000 && pontos <= 36000) {
		al_draw_bitmap(estrela, (WIDTH / 2) - 85, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) - 40, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) + 5, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) + 50, (HEIGHT / 2) - 60, 0);
	}
	else if (pontos > 36000) {
		al_draw_bitmap(estrela, (WIDTH / 2) - 110, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) - 65, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) - 20, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) + 25, (HEIGHT / 2) - 60, 0);
		al_draw_bitmap(estrela, (WIDTH / 2) + 70, (HEIGHT / 2) - 60, 0);
	}
}
void DesenhaCoracoes(ALLEGRO_BITMAP * coracaoVazio, ALLEGRO_BITMAP * coracaoMetade, ALLEGRO_BITMAP * coracaoCheio, Jogador * jogador)
{
	switch (jogador->vidas)
	{
	case 0:
		al_draw_bitmap(coracaoVazio, 950, 70, 0);
		al_draw_bitmap(coracaoVazio, 978, 70, 0);
		al_draw_bitmap(coracaoVazio, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 1:
		al_draw_bitmap(coracaoMetade, 950, 70, 0);
		al_draw_bitmap(coracaoVazio, 978, 70, 0);
		al_draw_bitmap(coracaoVazio, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 2:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoVazio, 978, 70, 0);
		al_draw_bitmap(coracaoVazio, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		TiraEstado(jogador);
		break;
	case 3:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoMetade, 978, 70, 0);
		al_draw_bitmap(coracaoVazio, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 4:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoVazio, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		TiraEstado(jogador);
		break;
	case 5:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoMetade, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 6:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoVazio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		TiraEstado(jogador);
		break;
	case 7:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoMetade, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 8:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoCheio, 1034, 70, 0);
		al_draw_bitmap(coracaoVazio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		TiraEstado(jogador);
		break;
	case 9:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoCheio, 1034, 70, 0);
		al_draw_bitmap(coracaoMetade, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 10:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoCheio, 1034, 70, 0);
		al_draw_bitmap(coracaoCheio, 1062, 70, 0);
		al_draw_bitmap(coracaoVazio, 1090, 70, 0);
		TiraEstado(jogador);
		break;
	case 11:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoCheio, 1034, 70, 0);
		al_draw_bitmap(coracaoCheio, 1062, 70, 0);
		al_draw_bitmap(coracaoMetade, 1090, 70, 0);
		perdeuEstado = false;
		break;
	case 12:
		al_draw_bitmap(coracaoCheio, 950, 70, 0);
		al_draw_bitmap(coracaoCheio, 978, 70, 0);
		al_draw_bitmap(coracaoCheio, 1006, 70, 0);
		al_draw_bitmap(coracaoCheio, 1034, 70, 0);
		al_draw_bitmap(coracaoCheio, 1062, 70, 0);
		al_draw_bitmap(coracaoCheio, 1090, 70, 0);
		perdeuEstado = false;
		break;
	default:
		break;
	}
}
void DesenhaBtnPause(ALLEGRO_BITMAP * pauseBtn)
{
	al_draw_bitmap(pauseBtn, 1160, 25, 0);
}
void DesenhaBtnMusica(ALLEGRO_BITMAP * musicaOn, ALLEGRO_BITMAP * musicaOff, int posX, int posY, bool musicaTocando)
{
	if (musicaTocando)
	{
		al_draw_bitmap(musicaOn, posX, posY, 0);
	}
	else {
		al_draw_bitmap(musicaOff, posX, posY, 0);
	}
}
void DesenhaPontuacaoRanking(ALLEGRO_FONT * fontLista, Ranking * ranking)
{
	if (ranking->totalLinhas / 2 >= 5)
	{
		al_draw_textf(fontLista, WHITE, 490, 331, 0, "%s", ranking->nomesTxt[0]);
		al_draw_textf(fontLista, WHITE, 722, 331, 0, "%d", ranking->pontosTxt[0]);
		al_draw_textf(fontLista, WHITE, 490, 357, 0, "%s", ranking->nomesTxt[1]);
		al_draw_textf(fontLista, WHITE, 722, 357, 0, "%d", ranking->pontosTxt[1]);
		al_draw_textf(fontLista, WHITE, 490, 382, 0, "%s", ranking->nomesTxt[2]);
		al_draw_textf(fontLista, WHITE, 722, 382, 0, "%d", ranking->pontosTxt[2]);
		al_draw_textf(fontLista, WHITE, 490, 408, 0, "%s", ranking->nomesTxt[3]);
		al_draw_textf(fontLista, WHITE, 722, 408, 0, "%d", ranking->pontosTxt[3]);
		al_draw_textf(fontLista, WHITE, 490, 434, 0, "%s", ranking->nomesTxt[4]);
		al_draw_textf(fontLista, WHITE, 722, 434, 0, "%d", ranking->pontosTxt[4]);
	}
	else {
		switch (ranking->totalLinhas / 2)
		{
		case 4:
			al_draw_textf(fontLista, WHITE, 490, 331, 0, "%s", ranking->nomesTxt[0]);
			al_draw_textf(fontLista, WHITE, 722, 331, 0, "%d", ranking->pontosTxt[0]);
			al_draw_textf(fontLista, WHITE, 490, 357, 0, "%s", ranking->nomesTxt[1]);
			al_draw_textf(fontLista, WHITE, 722, 357, 0, "%d", ranking->pontosTxt[1]);
			al_draw_textf(fontLista, WHITE, 490, 382, 0, "%s", ranking->nomesTxt[2]);
			al_draw_textf(fontLista, WHITE, 722, 382, 0, "%d", ranking->pontosTxt[2]);
			al_draw_textf(fontLista, WHITE, 490, 408, 0, "%s", ranking->nomesTxt[3]);
			al_draw_textf(fontLista, WHITE, 722, 408, 0, "%d", ranking->pontosTxt[3]);
			al_draw_textf(fontLista, WHITE, 490, 434, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 434, 0, "---");
			break;
		case 3:
			al_draw_textf(fontLista, WHITE, 490, 331, 0, "%s", ranking->nomesTxt[0]);
			al_draw_textf(fontLista, WHITE, 722, 331, 0, "%d", ranking->pontosTxt[0]);
			al_draw_textf(fontLista, WHITE, 490, 357, 0, "%s", ranking->nomesTxt[1]);
			al_draw_textf(fontLista, WHITE, 722, 357, 0, "%d", ranking->pontosTxt[1]);
			al_draw_textf(fontLista, WHITE, 490, 382, 0, "%s", ranking->nomesTxt[2]);
			al_draw_textf(fontLista, WHITE, 722, 382, 0, "%d", ranking->pontosTxt[2]);
			al_draw_textf(fontLista, WHITE, 490, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 434, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 434, 0, "---");
			break;
		case 2:
			al_draw_textf(fontLista, WHITE, 490, 331, 0, "%s", ranking->nomesTxt[0]);
			al_draw_textf(fontLista, WHITE, 722, 331, 0, "%d", ranking->pontosTxt[0]);
			al_draw_textf(fontLista, WHITE, 490, 357, 0, "%s", ranking->nomesTxt[1]);
			al_draw_textf(fontLista, WHITE, 722, 357, 0, "%d", ranking->pontosTxt[1]);
			al_draw_textf(fontLista, WHITE, 490, 382, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 382, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 434, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 434, 0, "---");
			break;
		case 1:
			al_draw_textf(fontLista, WHITE, 490, 331, 0, "%s", ranking->nomesTxt[0]);
			al_draw_textf(fontLista, WHITE, 722, 331, 0, "%d", ranking->pontosTxt[0]);
			al_draw_textf(fontLista, WHITE, 490, 357, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 357, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 382, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 382, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 434, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 434, 0, "---");
			break;
		case 0:
			al_draw_textf(fontLista, WHITE, 490, 331, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 331, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 357, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 357, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 382, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 382, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 408, 0, "---");
			al_draw_textf(fontLista, WHITE, 490, 434, 0, "---");
			al_draw_textf(fontLista, WHITE, 722, 434, 0, "---");
			break;
		default:
			break;
		}
	}
}
void DesenhaEstadosCinza(ALLEGRO_BITMAP * estadosCinza[], Jogador * jogador)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (jogador->indexEstadosPerdidos[i] >= 0)
		{
			al_draw_bitmap(estadosCinza[jogador->indexEstadosPerdidos[i]], 0, 0, 0);
		}
	}
}
void DesenhaEstadosFeedBack(ALLEGRO_BITMAP * estadosVerdes[], ALLEGRO_BITMAP * estadosVermelhos[], Jogador * jogador, Lista * lista)
{
	if (al_get_timer_started(piscaTimer) && al_get_timer_count(piscaTimer) < 0.5)
	{
		mostraFeedback = true;
		if (jogador->acertou && lista->indexAnterior >= 0)
		{
			al_draw_bitmap(estadosVerdes[lista->indexAnterior], 0, 0, 0);
		}
		else if(!jogador->acertou && lista->indexAnterior >= 0) {
			al_draw_bitmap(estadosVermelhos[lista->indexAnterior], 0, 0, 0);
		}
	}
	else {		
		mostraFeedback = false;
		al_stop_timer(piscaTimer);
		al_set_timer_count(piscaTimer, 0);
	}
}

ClickIndex CheckClickPosition(float lines[], float columns[], int totalLines, int totalColumns, ALLEGRO_EVENT ev)
{
	ClickIndex temp;
	temp.i = -1;
	temp.j = -1;

	int x = ev.mouse.x, y = ev.mouse.y;

	int i = 0, j = 0;
	for (i = 0; i < totalLines; i++) // percorre todas as linhas
	{
		for (j = 0; j < totalColumns; j++) // percorre todas as colunas
		{
			if (x >((j != 0) ? columns[j - 1] : 0) && x < columns[j] && y < lines[i]) //nesse caso est� dentro do range desse quadrado
			{
				temp.i = i;
				temp.j = j;

				return temp; //verdadeiro para quando o click estiver no mapa
			}
		}
	}

	return temp; //falso para quando esta fora do mapa
}
void TestaEstados(Jogador *jogador, Lista *lista, ClickIndex index, EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *Roraima, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins)
{
	int i = 0;

#pragma region ESTADOS
	// Verificamos a posicao do click em rela��o � posi��o no mapa
	// E verificamos se o index da palavra que esta caindo � igual ao
	// indice da palavra que corresponde ao click do jogador
	// caso seja a isMaxHeight � true para limpar as palavras caindo
	// e acertou � igual a true para podermos sortear a pr�xima palavra
#pragma region ACRE
	for (i = 0; i < acreIndexSize; i++)
	{
		ClickIndex temp = Acre->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Acre->myIndexPosition)
				{
					JogadorAcertou(jogador, lista, 1000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Acre->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region ALAGOAS
	for (i = 0; i < alagoasIndexSize; i++)
	{
		ClickIndex temp = Alagoas->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Alagoas->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Alagoas->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region AMAPA
	for (i = 0; i < amapaIndexSize; i++)
	{
		ClickIndex temp = Amapa->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Amapa->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Amapa->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region AMAZONAS
	for (i = 0; i < amazonasIndexSize; i++)
	{
		ClickIndex temp = Amazonas->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Amazonas->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 300);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Amazonas->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region BAHIA
	for (i = 0; i < bahiaIndexSize; i++)
	{
		ClickIndex temp = Bahia->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Bahia->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Bahia->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region CEARA
	for (i = 0; i < cearaIndexSize; i++)
	{
		ClickIndex temp = Ceara->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Ceara->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Ceara->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region DISTRITO FEDERAL
	for (i = 0; i < distritoFederalIndexSize; i++)
	{
		ClickIndex temp = DistritoFederal->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == DistritoFederal->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 2000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[DistritoFederal->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region ESPIRITO SANTO
	for (i = 0; i < espiritoSantoIndexSize; i++)
	{
		ClickIndex temp = EspiritoSanto->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == EspiritoSanto->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[EspiritoSanto->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region GOIAS
	for (i = 0; i < goiasIndexSize; i++)
	{
		ClickIndex temp = Goias->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Goias->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Goias->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region MARANHAO
	for (i = 0; i < maranhaoIndexSize; i++)
	{
		ClickIndex temp = Maranhao->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Maranhao->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Maranhao->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region MATO GROSSO
	for (i = 0; i < matoGrossoIndexSize; i++)
	{
		ClickIndex temp = MatoGrosso->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == MatoGrosso->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 300);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[MatoGrosso->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region MATO GROSSO DO SUL
	for (i = 0; i < matoGrossoDoSulIndexSize; i++)
	{
		ClickIndex temp = MatoGrossoDoSul->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == MatoGrossoDoSul->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[MatoGrossoDoSul->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region MINAS GERAIS
	for (i = 0; i < minasGeraisIndexSize; i++)
	{
		ClickIndex temp = MinasGerais->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == MinasGerais->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[MinasGerais->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region PARA
	for (i = 0; i < paraIndexSize; i++)
	{
		ClickIndex temp = Para->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Para->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 300);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Para->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region PARAIBA
	for (i = 0; i < paraibaIndexSize; i++)
	{
		ClickIndex temp = Paraiba->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Paraiba->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Paraiba->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region PARANA
	for (i = 0; i < paranaIndexSize; i++)
	{
		ClickIndex temp = Parana->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Parana->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Parana->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region PERNAMBUCO
	for (i = 0; i < pernambucoIndexSize; i++)
	{
		ClickIndex temp = Pernambuco->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Pernambuco->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Pernambuco->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region PIAUI
	for (i = 0; i < piauiIndexSize; i++)
	{
		ClickIndex temp = Piaui->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Piaui->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Piaui->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region RIO DE JANEIRO
	for (i = 0; i < rioDeJaneiroIndexSize; i++)
	{
		ClickIndex temp = RioDeJaneiro->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == RioDeJaneiro->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[RioDeJaneiro->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region RIO GRANDE DO NORTE
	for (i = 0; i < rioGrandeDoNorteIndexSize; i++)
	{
		ClickIndex temp = RioGrandeDoNorte->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == RioGrandeDoNorte->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1500);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[RioGrandeDoNorte->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region RIO GRANDE DO SUL
	for (i = 0; i < rioGrandeDoSulIndexSize; i++)
	{
		ClickIndex temp = RioGrandeDoSul->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == RioGrandeDoSul->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[RioGrandeDoSul->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region RONDONIA
	for (i = 0; i < rondoniaIndexSize; i++)
	{
		ClickIndex temp = Rondonia->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Rondonia->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Rondonia->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region RORAIMA
	for (i = 0; i < roraimaIndexSize; i++)
	{
		ClickIndex temp = Roraima->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Roraima->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Roraima->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region SANTA CATARINA
	for (i = 0; i < santaCatarinaIndexSize; i++)
	{
		ClickIndex temp = SantaCatarina->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == SantaCatarina->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 1000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[SantaCatarina->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region SAO PAULO
	for (i = 0; i < saoPauloIndexSize; i++)
	{
		ClickIndex temp = SaoPaulo->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == SaoPaulo->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[SaoPaulo->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region SERGIPE
	for (i = 0; i < sergipeIndexSize; i++)
	{
		ClickIndex temp = Sergipe->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Sergipe->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 2000);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Sergipe->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma region TOCANTINS
	for (i = 0; i < tocantinsIndexSize; i++)
	{
		ClickIndex temp = Tocantins->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (jogadorJogando)
			{
				if (lista->indexAtual == Tocantins->myIndexPosition && jogadorJogando)
				{
					JogadorAcertou(jogador, lista, 700);
				}
				else {
					JogadorErrou(jogador, lista);
				}
			}
			printf("%s \n", Estados[Tocantins->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma endregion

}







