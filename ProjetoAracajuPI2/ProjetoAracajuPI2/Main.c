#pragma region Include

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "Objects.h"

#pragma endregion

// Variaveis globais
const int WIDTH = 1280;
const int HEIGHT = 720;
const int WIDTHMAPA = 650;
const int HEIGHTMAPA = 650;

// Variaveis globais Allegro
ALLEGRO_COLOR BLACK;
ALLEGRO_COLOR BLUE;
ALLEGRO_COLOR GREEN;
ALLEGRO_COLOR RED;
ALLEGRO_COLOR PURPLE;
ALLEGRO_COLOR BEIGE;
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

// Prototipos
void InitJogador(Jogador *jogador);
void InitLista(Lista *lista);
void InitBotaoJogar(BotaoJogar *botaoJogar);
void InitBotaoTutorial(BotaoTutorial *botaoTutorial);
void UpdateLista(ALLEGRO_FONT *fontLista, Jogador *jogador, Lista *lista);
void CreateMatrix(float lines[], float columns[], int totalLines, int totalColumns);
void ConcatenaLista(char *s1, char *s2, Lista *lista);
void SortPalavra(Jogador *jogador, Lista *lista);
ClickIndex CheckClickPosition(float lines[], float columns[], int totalLines, int totalColumns, ALLEGRO_EVENT ev);

void InitEstados(EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins);

void TestaEstados(Jogador *jogador, Lista *lista, ClickIndex index, EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins);

int main() {
	// Tipos Primitivos
	bool finished = false;
	bool isGameOver = false;
	bool redraw = true;
	bool clicouJogar = false;
	const int FPS = 60;
	float mLines[36];
	float mColumns[36];
	srand(time(NULL));
	int ScoreRandom = rand();

	// Variaveis de objeto
	Jogador jogador;
	Lista lista;
	ClickIndex clickIndex;
	BotaoJogar botaoJogar;
	BotaoTutorial botaoTutorial;

	//INICIALIZAÇAO DOS ESTADOS
#pragma region INIT ESTADOS
	EstadosPadrao *_Acre, *_Alagoas, *_Amapa, *_Amazonas, *_Bahia, *_Ceara, *_DistritoFederal, *_EspiritoSanto, *_Goias, *_Maranhao,
		*_MatoGrosso, *_MatoGrossoDoSul, *_MinasGerais, *_Para, *_Paraiba, *_Parana, *_Pernambuco, *_Piaui, *_RioDeJaneiro, *_RioGrandeDoNorte,
		*_RioGrandeDoSul, *_Rondonia, *_SantaCatarina, *_SaoPaulo, *_Sergipe, *_Tocantins;

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
	_SantaCatarina = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_SaoPaulo = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Sergipe = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
	_Tocantins = (EstadosPadrao*)malloc(sizeof(EstadosPadrao));
#pragma endregion

	// Variaveis do Allegro
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *mapaBrasil = NULL;
	ALLEGRO_BITMAP *menu = NULL;
	ALLEGRO_BITMAP *tutorial = NULL;
	ALLEGRO_FONT *fontLista = NULL;

	ALLEGRO_BITMAP *tocantins = NULL;
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

	// Addons e instalações do allegro
	al_install_mouse();											// Possibilita o uso do mouse
	al_install_audio();											// Possibilita o uso de sons
	al_init_acodec_addon();										// Possibilita diferentes formatos
	al_init_font_addon();										// Possibilita escrever na tela
	al_init_ttf_addon();										// Possibilita usar formato ttf
	al_init_image_addon();										// Possibilita usar varios formatos de imagem
	al_init_primitives_addon();									// Possibilita usar formas geometricas

	// Carrega os bitmaps	

	//bitmap do menu do jogo															
	menu = al_load_bitmap("imgs/tela-inicial1.png");
	int menuWidth = al_get_bitmap_width(menu);
	int menuHeight = al_get_bitmap_height(menu);

	//bitmap do mapa do jogo
	mapaBrasil = al_load_bitmap("imgs/Brasil-3D grid.png"); // bmp de testes para encontrar o indice correto
	int mapaWidth = al_get_bitmap_width(mapaBrasil);			// Recebe o tamanho X da imagem
	int mapaHeight = al_get_bitmap_height(mapaBrasil);			// Recebe o tamanho Y da imagem

	tocantins = al_load_bitmap("imgs/EstadosCinzas/tocantins.png"); // bmp de testes para encontrar o indice correto
	int tocantinsWidth = al_get_bitmap_width(mapaBrasil);			// Recebe o tamanho X da imagem
	int tocantinsHeight = al_get_bitmap_height(mapaBrasil);			// Recebe o tamanho Y da imagem
	al_draw_bitmap(tocantins, 0, 0, tocantinsWidth, tocantinsHeight, 0, 0, WIDTHMAPA, HEIGHTMAPA, 0);


	//bitmap do tutorial do jogo
/*	tutorial = al_load_bitmap("imagem.png");
	int tutorialWidth = al_get_bitmap_width(tutorial);
	int tutorialHeight = al_get_bitmap_height(tutorial);
	al_draw_scaled_bitmap(tutorial, -0, -0, tutorialWidth, tutorialHeight, 0, 0, WIDTH, HEIGHT, 0); */

	// Carrega as fonts
	fontLista = al_load_font("fonts/Magnificent.ttf", 20, 0);

	// Inicializa cores
	BLACK = al_map_rgb(0, 0, 0);
	BLUE = al_map_rgb(0, 0, 255);
	GREEN = al_map_rgb(0, 255, 0);
	RED = al_map_rgb(255, 0, 0);
	PURPLE = al_map_rgb(255, 0, 255);
	// beige = al_map_rgb(0, 0, 0); ???

	// Inicializa sons
	al_reserve_samples(2);		// Quantidade de "canais" de audio ( 1 para cada audio )

	// Audio do menu
	menuAudioSample = al_load_sample("audio/Audio.wav");
	menuAudioInstance = al_create_sample_instance(menuAudioSample);
	al_attach_sample_instance_to_mixer(menuAudioInstance, al_get_default_mixer());

	// Audio do fundo do jogo
	jogoAudioSample = al_load_sample("audio/AudioJazz.wav");
	jogoAudioInstance = al_create_sample_instance(jogoAudioSample);
	al_attach_sample_instance_to_mixer(jogoAudioInstance, al_get_default_mixer());
	al_set_sample_instance_gain(jogoAudioInstance, 0.3);

	// Audio de acerto
	acertoAudioSample = al_load_sample("audio/AcertoAudio.wav");
	acertoAudioInstance = al_create_sample_instance(acertoAudioSample);
	al_attach_sample_instance_to_mixer(acertoAudioInstance, al_get_default_mixer());

	// Audio de erro
	erroAudioSample = al_load_sample("audio/ErroAudio.wav");
	erroAudioInstance = al_create_sample_instance(erroAudioSample);
	al_attach_sample_instance_to_mixer(erroAudioInstance, al_get_default_mixer());

	// Inicializacao dos nossos objetos
	CreateMatrix(mLines, mColumns, TOTAL_DE_LINHAS, TOTAL_DE_COLUNAS);
	InitJogador(&jogador);

	InitEstados(_Acre, _Alagoas, _Amapa, _Amazonas, _Bahia, _Ceara, _DistritoFederal, _EspiritoSanto, _Goias, _Maranhao,
		_MatoGrosso, _MatoGrossoDoSul, _MinasGerais, _Para, _Paraiba, _Parana, _Pernambuco, _Piaui, _RioDeJaneiro, _RioGrandeDoNorte,
		_RioGrandeDoSul, _Rondonia, _SantaCatarina, _SaoPaulo, _Sergipe, _Tocantins);

	InitLista(&lista);

	//Inicialização dos Botões do Menu
	InitBotaoJogar(&botaoJogar);
	InitBotaoTutorial(&botaoTutorial);

	event_queue = al_create_event_queue();						// Cria "lista" de eventos
	timer = al_create_timer(1.0 / FPS);							// Inicializa o timer para que tenhamos 60 fps

																// Registro de eventos para a lista de eventos
	al_register_event_source(event_queue, al_get_mouse_event_source());			// Registra o mouse na lista de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(timer));			// Registra o timer na lista de eventos
	al_register_event_source(event_queue, al_get_display_event_source(display));			// Registra o display na lista de eventos

	al_start_timer(timer);										// Inicia o timer
																// Looping Principal


	while (!finished) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		// É invocado a cada frame "Função de update" 
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// Caso a quantidade de vidas do jogador for menor que zero
			// isGameOver é falso para podermos mostrar a tela de pontuação
			/*if (jogador.vidas <= 0)
			{
				isGameOver = true;
			}*/

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)			// Permite fechar a janela pelo X
		{
			finished = true;
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //verifica se o jogador clicou em jogar
		{
			// Verifica se o click esta dentro dos bounds do botao jogar, caso esteja a variavel jogador.jogando fica verdadeira
			if (ev.mouse.x >= botaoJogar.boundXInicio && ev.mouse.x <= botaoJogar.boundXFinal && ev.mouse.y >= botaoJogar.boundYInicio &&  ev.mouse.y <= botaoJogar.boundYFinal)
			{
				jogador.jogando = true;
			}

			//Verifica se o click está dentro dos bounds do botão tutorial, caso esteja variavel jogador.tutorial fica verdadeira 
			if (ev.mouse.x >= botaoTutorial.boundXInicio && ev.mouse.x <= botaoTutorial.boundXFinal && ev.mouse.y >= botaoTutorial.boundYInicio &&  ev.mouse.y <= botaoTutorial.boundYFinal)
			{
				jogador.tutorial = true;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && jogador.tutorial) // Verifica se houve input de click no botão tutorial
		{
	/*		al_draw_scaled_bitmap(tutorial, 0, 0, tutorialWidth, tutorialHeight, 0, 0, WIDTH, HEIGHT, 0);		//coloca o tutorial na tela
			al_flip_display();									// Muda para o back buffer
			al_clear_to_color(al_map_rgb(255, 255, 255));  */ 
			if (jogador.tutorial)
			printf("funcionando\n");
		}
		// TODO: Arrumar o erro que quando o jogador clica em JOGAR ja conta um acerto
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && jogador.jogando) // Verifica se houve input de click no botão jogar
		{
			ClickIndex t = CheckClickPosition(mLines, mColumns, TOTAL_DE_LINHAS, TOTAL_DE_COLUNAS, ev); //checa se o click foi no mapa

			printf("index %d, %d\n", t.i, t.j);

			printf("POS MOUSE X: %d\n", ev.mouse.x);
			printf("POS MOUSE Y: %d\n", ev.mouse.y);
			//TESTA o click para ver qual estado foi clicado
			TestaEstados(&jogador, &lista, t, _Acre, _Alagoas, _Amapa, _Amazonas, _Bahia, _Ceara, _DistritoFederal, _EspiritoSanto, _Goias, _Maranhao,
				_MatoGrosso, _MatoGrossoDoSul, _MinasGerais, _Para, _Paraiba, _Parana, _Pernambuco, _Piaui, _RioDeJaneiro, _RioGrandeDoNorte,
				_RioGrandeDoSul, _Rondonia, _SantaCatarina, _SaoPaulo, _Sergipe, _Tocantins);

			// Se o jogador acertou incrementa os pontos e 
			// som de acerto toca
			if (clicouJogar)
			{
				if (jogador.acertou)
				{
					al_play_sample_instance(acertoAudioInstance);
					jogador.pontos += 50;
				}
				else
				{
					al_play_sample_instance(erroAudioInstance);
					jogador.erros++;
					jogador.vidas--;
				}
			}

			clicouJogar = true;
		}

		if (redraw && al_is_event_queue_empty(event_queue))			// Permite saber quando podemos redesenhar na tela
		{															// Lista de eventos vazia e (evitar bugs)
			redraw = false;

			if (jogador.jogando)   //verifica se o jogador passou a jogar
			{
				al_stop_sample_instance(menuAudioInstance);
				al_play_sample_instance(jogoAudioInstance);

				if (!isGameOver)
				{
					UpdateLista(fontLista, &jogador, &lista);
					al_draw_scaled_bitmap(mapaBrasil, 0, 0, mapaWidth, mapaHeight, 0, 0, WIDTHMAPA, HEIGHTMAPA, 0);		// Coloca o mapa na tela
					al_flip_display();									// Muda para o back buffer
					al_clear_to_color(al_map_rgb(255, 255, 255));		// Limpa a tela

					al_draw_bitmap(tocantins, 0, 0, tocantinsWidth, tocantinsHeight, 0, 0, WIDTHMAPA, HEIGHTMAPA, 0);		// Coloca o mapa na tela
				}
				else 
				{
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));		// Limpa a tela
					al_draw_text(fontLista, RED, WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
					al_draw_textf(fontLista, RED, WIDTH / 2, (HEIGHT / 2) + 30, ALLEGRO_ALIGN_CENTER, "Pontos: %d", jogador.pontos);
					al_draw_textf(fontLista, RED, WIDTH / 2, (HEIGHT / 2) + 60, ALLEGRO_ALIGN_CENTER, "Acertos: %d", jogador.acertos);
					al_draw_textf(fontLista, RED, WIDTH / 2, (HEIGHT / 2) + 90, ALLEGRO_ALIGN_CENTER, "Erros: %d", jogador.erros);
				}
			}
			else
			{
				al_play_sample_instance(menuAudioInstance);
				al_draw_scaled_bitmap(menu, 0, 0, menuWidth, menuHeight, 0, 0, WIDTH, HEIGHT, 0);		//coloca o menu na tela
				al_flip_display();									// Muda para o back buffer
				al_clear_to_color(al_map_rgb(255, 255, 255));
			}
		}
	}

	// Libera a memoria alocada para variaveis Allegro
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(mapaBrasil);
	al_destroy_bitmap(menu);

	al_destroy_bitmap(tocantins);
	//al_destroy_bitmap(tutorial);
	al_destroy_font(fontLista);
	al_destroy_sample(menuAudioSample);
	al_destroy_sample(jogoAudioSample);
	al_destroy_sample(acertoAudioSample);
	al_destroy_sample(erroAudioSample);
	al_destroy_sample_instance(menuAudioInstance);
	al_destroy_sample_instance(jogoAudioInstance);
	al_destroy_sample_instance(acertoAudioInstance);
	al_destroy_sample_instance(erroAudioInstance);
}

// Definicao de funcoes

// Inicializa o jogador
void InitJogador(Jogador *jogador)
{
	jogador->pontos = 0;
	jogador->vidas = 1;
	jogador->acertos = 0;
	jogador->erros = 0;
	jogador->jogando = false;
	jogador->tutorial = false;
}

// Inicializa a lista de palavras
void InitLista(Lista *lista)
{
	lista->velocidade = 20;
	lista->heightLista = 0;
	lista->randomNumber = 0;
	lista->palavraAtual = NULL;
}

//Aqui sera configurado o mapeamento dos estados
void InitEstados(EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins)
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
	Goias->index[5].i = 18; Goias->index[5].j = 21;
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
#pragma endregion
	
#pragma region ACRE
	Acre->myIndexPosition = 14; //posicao no vetor ESTADOS de nomes na classe objects.h
	Acre->index[0].i = 12; Acre->index[0].j = 2;
	Acre->index[1].i = 12; Acre->index[1].j = 3;
	Acre->index[2].i = 13; Acre->index[2].j = 3;
	Acre->index[3].i = 13; Acre->index[3].j = 4;
	Acre->index[4].i = 13; Acre->index[4].j = 5;
	Acre->index[5].i = 13; Acre->index[5].j = 6;
	Acre->index[6].i = 14; Acre->index[6].j = 5;
	Acre->index[7].i = 14; Acre->index[7].j = 6;
	Acre->index[8].i = 14; Acre->index[8].j = 7;
#pragma endregion

#pragma region SANTA CATARINA
	SantaCatarina->myIndexPosition = 1;
	SantaCatarina->index[0].i = 28; SantaCatarina->index[0].j = 18;
	SantaCatarina->index[1].i = 28; SantaCatarina->index[1].j = 19;
	SantaCatarina->index[2].i = 28; SantaCatarina->index[2].j = 20;
	SantaCatarina->index[3].i = 28; SantaCatarina->index[3].j = 21;
	SantaCatarina->index[4].i = 28; SantaCatarina->index[4].j = 22;
	SantaCatarina->index[5].i = 28; SantaCatarina->index[5].j = 23;
	SantaCatarina->index[6].i = 29; SantaCatarina->index[6].j = 22;
	SantaCatarina->index[7].i = 29; SantaCatarina->index[7].j = 23;
#pragma endregion

#pragma region RIO GRANDE DO NORTE
	RioGrandeDoNorte->myIndexPosition = 22; //posicao no vetor ESTADOS de nomes na classe objects.h
	RioGrandeDoNorte->index[0].i = 10; RioGrandeDoNorte->index[0].j = 33;
	RioGrandeDoNorte->index[1].i = 10; RioGrandeDoNorte->index[1].j = 34;
	RioGrandeDoNorte->index[2].i = 10; RioGrandeDoNorte->index[2].j = 35;
#pragma endregion

#pragma region CEARA
	Ceara->myIndexPosition = 21; //posicao no vetor ESTADOS de nomes na classe objects.h
	Ceara->index[0].i = 8; Ceara->index[0].j = 30;
	Ceara->index[1].i = 8; Ceara->index[1].j = 31;
	Ceara->index[2].i = 8; Ceara->index[2].j = 32;
	Ceara->index[3].i = 9; Ceara->index[3].j = 30;
	Ceara->index[4].i = 9; Ceara->index[4].j = 31;
	Ceara->index[5].i = 9; Ceara->index[5].j = 32;
	Ceara->index[6].i = 9; Ceara->index[6].j = 33;
	Ceara->index[7].i = 10; Ceara->index[7].j = 30;
	Ceara->index[8].i = 10; Ceara->index[8].j = 31;
	Ceara->index[9].i = 10; Ceara->index[9].j = 32;
	Ceara->index[10].i = 11; Ceara->index[10].j = 30;
	Ceara->index[11].i = 11; Ceara->index[11].j = 31;
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
	Bahia->myIndexPosition = 11; //posicao no vetor ESTADOS de nomes na classe objects.h
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
	Piaui->index[5].i = 11;  Piaui->index[5].j = 28;
	Piaui->index[6].i = 11;  Piaui->index[6].j = 29;
	Piaui->index[7].i = 12;  Piaui->index[7].j = 26;
	Piaui->index[8].i = 12;  Piaui->index[8].j = 27;
	Piaui->index[9].i = 12;  Piaui->index[9].j = 28;
	Piaui->index[10].i = 12; Piaui->index[10].j = 29;
	Piaui->index[11].i = 13; Piaui->index[11].j = 26;
	Piaui->index[12].i = 13; Piaui->index[12].j = 27;
	Piaui->index[13].i = 13; Piaui->index[13].j = 28;
	Piaui->index[14].i = 14; Piaui->index[14].j = 26;
	Piaui->index[15].i = 14; Piaui->index[15].j = 27;
#pragma endregion

#pragma region MARANHAO
	Maranhao->myIndexPosition = 19; //posicao no vetor ESTADOS de nomes na classe objects.h
	Maranhao->index[0].i = 7;   Maranhao->index[0].j = 26;
	Maranhao->index[1].i = 7;   Maranhao->index[1].j = 27;
	Maranhao->index[2].i = 8;   Maranhao->index[2].j = 25;
	Maranhao->index[3].i = 8;   Maranhao->index[3].j = 26;
	Maranhao->index[4].i = 8;   Maranhao->index[4].j = 27;
	Maranhao->index[5].i = 8;   Maranhao->index[5].j = 28;
	Maranhao->index[6].i = 9;   Maranhao->index[6].j = 24;
	Maranhao->index[7].i = 9;   Maranhao->index[7].j = 25;
	Maranhao->index[8].i = 9;   Maranhao->index[8].j = 26;
	Maranhao->index[9].i = 9;   Maranhao->index[9].j = 27;
	Maranhao->index[10].i = 10; Maranhao->index[10].j = 25;
	Maranhao->index[11].i = 10; Maranhao->index[11].j = 26;
	Maranhao->index[12].i = 10; Maranhao->index[12].j = 27;
	Maranhao->index[13].i = 11; Maranhao->index[13].j = 25;
	Maranhao->index[14].i = 11; Maranhao->index[14].j = 26;
	Maranhao->index[15].i = 11; Maranhao->index[15].j = 27;
	Maranhao->index[16].i = 12; Maranhao->index[16].j = 25;
	Maranhao->index[17].i = 13; Maranhao->index[17].j = 25;
#pragma endregion

#pragma region ESPIRITO SANTO
	EspiritoSanto->myIndexPosition = 7; //posicao no vetor ESTADOS de nomes na classe objects.h
	EspiritoSanto->index[0].i = 21; EspiritoSanto->index[0].j = 30;
	EspiritoSanto->index[1].i = 22; EspiritoSanto->index[1].j = 30;
	EspiritoSanto->index[2].i = 23; EspiritoSanto->index[2].j = 29;
#pragma endregion

#pragma region RIO DE JANEIRO
	RioDeJaneiro->myIndexPosition = 5; //posicao no vetor ESTADOS de nomes na classe objects.h
	RioDeJaneiro->index[0].i = 24; RioDeJaneiro->index[0].j = 27;
	RioDeJaneiro->index[1].i = 24; RioDeJaneiro->index[1].j = 28;
	RioDeJaneiro->index[2].i = 24; RioDeJaneiro->index[2].j = 29;
#pragma endregion

#pragma region MINAS GERAIS
	MinasGerais->myIndexPosition = 6; //posicao no vetor ESTADOS de nomes na classe objects.h
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
	SaoPaulo->index[9].i = 25;   SaoPaulo->index[9].j = 23;
	SaoPaulo->index[10].i = 25; SaoPaulo->index[10].j = 24;
	SaoPaulo->index[11].i = 25; SaoPaulo->index[11].j = 25;
	SaoPaulo->index[12].i = 25; SaoPaulo->index[12].j = 26;
	SaoPaulo->index[13].i = 26; SaoPaulo->index[13].j = 24;
#pragma endregion

#pragma region PARANA
	Parana->myIndexPosition = 2; //posicao no vetor ESTADOS de nomes na classe objects.h
	Parana->index[0].i = 25;   Parana->index[0].j = 19;
	Parana->index[1].i = 25;   Parana->index[1].j = 20;
	Parana->index[2].i = 25;   Parana->index[2].j = 21;
	Parana->index[3].i = 25;   Parana->index[3].j = 22;
	Parana->index[4].i = 25;   Parana->index[4].j = 23;
	Parana->index[5].i = 26;   Parana->index[5].j = 19;
	Parana->index[6].i = 26;   Parana->index[6].j = 20;
	Parana->index[7].i = 26;   Parana->index[7].j = 21;
	Parana->index[8].i = 26;   Parana->index[8].j = 22;
	Parana->index[9].i = 26;   Parana->index[9].j = 23;
	Parana->index[10].i = 27;   Parana->index[10].j = 19;
	Parana->index[11].i = 27;   Parana->index[11].j = 20;
	Parana->index[12].i = 27;   Parana->index[12].j = 21;
	Parana->index[13].i = 27;   Parana->index[13].j = 22;
	Parana->index[14].i = 27;   Parana->index[14].j = 23;
#pragma endregion	

#pragma region RIO GRAND DO SUL
	RioGrandeDoSul->myIndexPosition = 0; //posicao no vetor ESTADOS de nomes na classe objects.h
	RioGrandeDoSul->index[0].i = 29;   RioGrandeDoSul->index[0].j = 17;
	RioGrandeDoSul->index[1].i = 29;   RioGrandeDoSul->index[1].j = 18;
	RioGrandeDoSul->index[2].i = 29;   RioGrandeDoSul->index[2].j = 19;
	RioGrandeDoSul->index[3].i = 29;   RioGrandeDoSul->index[3].j = 20;
	RioGrandeDoSul->index[4].i = 29;   RioGrandeDoSul->index[4].j = 21;
	RioGrandeDoSul->index[5].i = 30;   RioGrandeDoSul->index[5].j = 16;
	RioGrandeDoSul->index[6].i = 30;   RioGrandeDoSul->index[6].j = 17;
	RioGrandeDoSul->index[7].i = 30;   RioGrandeDoSul->index[7].j = 18;
	RioGrandeDoSul->index[8].i = 30;   RioGrandeDoSul->index[8].j = 19;
	RioGrandeDoSul->index[9].i = 30;   RioGrandeDoSul->index[9].j = 20;
	RioGrandeDoSul->index[10].i = 30;   RioGrandeDoSul->index[10].j = 21;
	RioGrandeDoSul->index[11].i = 30;   RioGrandeDoSul->index[11].j = 22;
	RioGrandeDoSul->index[12].i = 31;   RioGrandeDoSul->index[12].j = 17;
	RioGrandeDoSul->index[13].i = 31;   RioGrandeDoSul->index[13].j = 18;
	RioGrandeDoSul->index[14].i = 31;   RioGrandeDoSul->index[14].j = 19;
	RioGrandeDoSul->index[15].i = 31;   RioGrandeDoSul->index[15].j = 20;
	RioGrandeDoSul->index[16].i = 31;   RioGrandeDoSul->index[16].j = 21;
	RioGrandeDoSul->index[17].i = 32;   RioGrandeDoSul->index[17].j = 18;
	RioGrandeDoSul->index[18].i = 32;   RioGrandeDoSul->index[18].j = 19;
	RioGrandeDoSul->index[19].i = 32;   RioGrandeDoSul->index[19].j = 20;
	RioGrandeDoSul->index[20].i = 32;   RioGrandeDoSul->index[20].j = 21;
	RioGrandeDoSul->index[21].i = 33;   RioGrandeDoSul->index[21].j = 19;
	RioGrandeDoSul->index[22].i = 33;   RioGrandeDoSul->index[22].j = 20;
#pragma endregion

#pragma region MATO GROSSO DO SUL
	MatoGrossoDoSul->myIndexPosition = 4; //posicao no vetor ESTADOS de nomes na classe objects.h
	MatoGrossoDoSul->index[1].i=20 ; 		MatoGrossoDoSul->index[1].j=17 ; 
	MatoGrossoDoSul->index[2].i=20 ; 		MatoGrossoDoSul->index[2].j=18 ;
	MatoGrossoDoSul->index[3].i=21 ; 		MatoGrossoDoSul->index[3].j=16 ;
	MatoGrossoDoSul->index[4].i=21 ; 		MatoGrossoDoSul->index[4].j=17 ;
	MatoGrossoDoSul->index[5].i=21 ; 		MatoGrossoDoSul->index[5].j=18 ;
	MatoGrossoDoSul->index[6].i=21 ; 		MatoGrossoDoSul->index[6].j=19 ;
	MatoGrossoDoSul->index[7].i=22 ; 		MatoGrossoDoSul->index[7].j=16 ;
	MatoGrossoDoSul->index[8].i=22 ; 		MatoGrossoDoSul->index[8].j=17 ;
	MatoGrossoDoSul->index[9].i=22 ; 		MatoGrossoDoSul->index[9].j=18 ;
	MatoGrossoDoSul->index[10].i=22 ; 		MatoGrossoDoSul->index[10].j=19 ;
	MatoGrossoDoSul->index[11].i=22 ; 		MatoGrossoDoSul->index[11].j=20 ;
	MatoGrossoDoSul->index[12].i=22 ; 		MatoGrossoDoSul->index[12].j=21 ;
	MatoGrossoDoSul->index[13].i=23 ; 		MatoGrossoDoSul->index[13].j=15 ;
	MatoGrossoDoSul->index[14].i=23 ; 		MatoGrossoDoSul->index[14].j=15 ;
	MatoGrossoDoSul->index[15].i=23 ; 		MatoGrossoDoSul->index[15].j=16 ;
	MatoGrossoDoSul->index[16].i=23 ; 		MatoGrossoDoSul->index[16].j=17 ;
	MatoGrossoDoSul->index[17].i=23 ; 		MatoGrossoDoSul->index[17].j=18 ;
	MatoGrossoDoSul->index[18].i=23 ; 		MatoGrossoDoSul->index[18].j=19 ;
	MatoGrossoDoSul->index[19].i=23 ; 		MatoGrossoDoSul->index[19].j=20 ;
	MatoGrossoDoSul->index[20].i=24 ; 		MatoGrossoDoSul->index[20].j=15 ;
	MatoGrossoDoSul->index[21].i=24 ; 		MatoGrossoDoSul->index[21].j=16 ;
	MatoGrossoDoSul->index[22].i=24 ; 		MatoGrossoDoSul->index[22].j=17 ;
	MatoGrossoDoSul->index[23].i=24 ; 		MatoGrossoDoSul->index[23].j=18;
	MatoGrossoDoSul->index[24].i=24 ; 		MatoGrossoDoSul->index[24].j=19 ;
	MatoGrossoDoSul->index[25].i=25 ; 		MatoGrossoDoSul->index[25].j=18 ;
	
#pragma endregion 

/*#pragma region MATO GROSSO
	MatoGrosso->index[1].i =13 ; 		MatoGrosso->index[1].j =12 ;
	MatoGrosso->index[2].i =13 ; 		MatoGrosso->index[2].j =13 ;
	MatoGrosso->index[3].i =13 ; 		MatoGrosso->index[3].j =14 ;
	MatoGrosso->index[4].i =13 ; 		MatoGrosso->index[4].j =15 ;
	MatoGrosso->index[5].i =13 ; 		MatoGrosso->index[5].j =16 ;
	MatoGrosso->index[6].i =14 ; 		MatoGrosso->index[6].j =12 ;
	MatoGrosso->index[7].i =14 ; 		MatoGrosso->index[7].j =13 ;
	MatoGrosso->index[8].i =14 ; 		MatoGrosso->index[8].j =14 ;
	MatoGrosso->index[9].i =14 ; 		MatoGrosso->index[9].j =15 ;
	MatoGrosso->index[10].i =14 ; 		MatoGrosso->index[10].j =16 ;
	MatoGrosso->index[11].i =14 ; 		MatoGrosso->index[11].j =17 ;
	MatoGrosso->index[12].i =14 ; 		MatoGrosso->index[12].j =18 ;
	MatoGrosso->index[13].i =14 ; 		MatoGrosso->index[13].j =19 ;
	MatoGrosso->index[14].i =14 ; 		MatoGrosso->index[14].j =20 ;
	MatoGrosso->index[15].i =14 ; 		MatoGrosso->index[15].j =21 ;
	MatoGrosso->index[16].i =15 ; 		MatoGrosso->index[16].j =14 ;
	MatoGrosso->index[17].i =15 ; 		MatoGrosso->index[17].j =15 ;
	MatoGrosso->index[18].i =15 ; 		MatoGrosso->index[18].j =16 ;
	MatoGrosso->index[19].i =15 ; 		MatoGrosso->index[19].j =17 ;
	MatoGrosso->index[20].i =15 ; 		MatoGrosso->index[20].j =18 ;
	MatoGrosso->index[21].i =15 ; 		MatoGrosso->index[21].j =19 ;
	MatoGrosso->index[22].i =15 ; 		MatoGrosso->index[22].j =20 ;
	MatoGrosso->index[23].i =15 ; 		MatoGrosso->index[23].j =21 ;
	MatoGrosso->index[24].i =16 ; 		MatoGrosso->index[24].j =13 ;
	MatoGrosso->index[25].i =16 ; 		MatoGrosso->index[25].j =14 ;
	MatoGrosso->index[26].i =16 ; 		MatoGrosso->index[26].j =15 ;
	MatoGrosso->index[27].i =16 ; 		MatoGrosso->index[27].j =16 ;
	MatoGrosso->index[28].i =16 ; 		MatoGrosso->index[28].j =17 ;
	MatoGrosso->index[29].i =16 ; 		MatoGrosso->index[29].j =18 ;
	MatoGrosso->index[30].i =16 ; 		MatoGrosso->index[30].j =19 ;
	MatoGrosso->index[31].i =16 ; 		MatoGrosso->index[31].j =20 ;
	MatoGrosso->index[32].i =16 ; 		MatoGrosso->index[32].j =21 ;
	MatoGrosso->index[33].i =17 ; 		MatoGrosso->index[33].j =13 ;
	MatoGrosso->index[34].i =17 ; 		MatoGrosso->index[34].j =14 ;
	MatoGrosso->index[35].i =17 ; 		MatoGrosso->index[35].j =15 ;
	MatoGrosso->index[36].i =17 ; 		MatoGrosso->index[36].j =16 ;
	MatoGrosso->index[37].i =17 ; 		MatoGrosso->index[37].j = 17;
	MatoGrosso->index[38].i =17 ; 		MatoGrosso->index[38].j =18 ;
	MatoGrosso->index[39].i =17 ; 		MatoGrosso->index[39].j =19 ;
	MatoGrosso->index[40].i =17 ; 		MatoGrosso->index[40].j =20 ;
	MatoGrosso->index[41].i =17 ; 		MatoGrosso->index[41].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
	MatoGrosso->index[42].i =18 ; 		MatoGrosso->index[42].j =21 ;
#pragma endregion */
}

// Inicializa o botao jogar
void InitBotaoJogar(BotaoJogar * botaoJogar)
{
	botaoJogar->boundXInicio = 435;
	botaoJogar->boundXFinal = 850;

	botaoJogar->boundYInicio = 420;
	botaoJogar->boundYFinal = 485;
}

// Inicializa o botao tutorial
void InitBotaoTutorial(BotaoTutorial *botaoTutorial)
{

	botaoTutorial->boundXInicio = 435;
	botaoTutorial->boundXFinal = 850;

	botaoTutorial->boundYInicio = 500;
	botaoTutorial->boundYFinal = 570;
}

// Altera o valor Y do elemento da lista de acordo velocidade
// da lista(lista->velocidade) para dar noção de animação
void UpdateLista(ALLEGRO_FONT *fontLista, Jogador *jogador, Lista *lista)
{
	srand(time(NULL));
	// Caso a palavra tenha chegado na altura maxima devemos resetar a lista
	if (lista->isMaxHeight)
	{
		if (!jogador->acertou)
		{
			al_play_sample_instance(erroAudioInstance);
		}

		lista->heightLista = 0;
		lista->velocidade = 30;
		lista->palavraAtual = NULL;
		lista->randomNumber = rand();

		free(lista->palavraAtual);
		al_clear_to_color(al_map_rgb(255, 255, 255));
	}

	jogador->acertou = false;

	if (lista->palavraAtual == NULL)
	{
		SortPalavra(jogador, lista);
	}

	// Caso a altura da palavra seja menor que a altura do mapa devemos continuar a animação de "queda"
	if (lista->heightLista < HEIGHTMAPA)
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));

		al_draw_textf(fontLista, BLACK, WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s", lista->palavraAtual);

		// Aumentamos a altura da lista de acordo com a velocidade para dar noção de animação
		// isMaxHeigth permite sabermos que a palavra nao chegou ao final da lista, entao nao devemos reseta-la
		lista->heightLista = lista->velocidade + 10;
		lista->velocidade += 5;
		lista->isMaxHeight = false;
	}
	else {
		al_draw_textf(fontLista, BLACK, WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s", lista->palavraAtual);

		// Chegamos ao final da lista, então isMaxHeight é true
		lista->isMaxHeight = true;
	}
}

// Sorteia uma a uma as palavras simples (somente estado, sigla ou capital)
void SortPalavra(Jogador *jogador, Lista *lista)
{
	srand(time(NULL));
	int conjunto = (rand() * 5) % 3;

	lista->indexAtual = lista->randomNumber % 27;

	if (jogador->pontos >= 100)
	{
		if (conjunto == 0)
		{
			ConcatenaLista(Estados[lista->indexAtual], Siglas[lista->indexAtual], lista);
		}
		else if (conjunto == 1) {
			ConcatenaLista(Capitais[lista->indexAtual], Siglas[lista->indexAtual], lista);
		}
		else if (conjunto == 2) {
			ConcatenaLista(Estados[lista->indexAtual], Capitais[lista->indexAtual], lista);
		}
	}
	else if (jogador->pontos < 100) {
		switch (conjunto)
		{
		case 0:
			lista->palavraAtual = Estados[lista->indexAtual];
			break;
		case 1:
			lista->palavraAtual = Siglas[lista->indexAtual];
			break;
		case 2:
			lista->palavraAtual = Capitais[lista->indexAtual];
			break;
		default:
			printf("Deu Ruim");
			break;
		}
	}
}

// Concatena as palavras da lista
void ConcatenaLista(char *s1, char *s2, Lista *lista)
{
	lista->palavraAtual = malloc(strlen(s1) + strlen(s2) + 6);
	strcpy(lista->palavraAtual, s1);
	strcat(lista->palavraAtual, "    ");
	strcat(lista->palavraAtual, s2);
}

// Cria matriz sob o Bitmap para poder identificar o click
void CreateMatrix(float lines[], float columns[], int totalLines, int totalColumns)
{
	float pixelW = WIDTHMAPA / (float)totalLines; //dividir o width pelo numero de linhas me da o tamanho em pixel de cada quadrado
	float pixelH = HEIGHTMAPA / (float)totalColumns; // mesma coisa de cima

	int i = 0, j = 0;
	for (i = 0; i < totalLines; i++)
	{
		lines[i] = pixelH + pixelH * i; // adiciono o valor em pixels onde ira comecar a matriz de Linhas
	}
	for (j = 0; j < totalColumns; j++)
	{
		columns[j] = pixelW + pixelW * j; // adiciono o valor em pixels onde ira comecar a matriz de colunas
	}
}

// Verifica a posicao do click
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
			if (x >((j != 0) ? columns[j - 1] : 0) && x < columns[j] && y < lines[i]) //nesse caso está dentro do range desse quadrado
			{
				temp.i = i;
				temp.j = j;

				return temp; //verdadeiro para quando o click estiver no mapa
			}
		}
	}
#pragma region RIO GRAND DO SUL
	return temp; //falso para quando esta fora do mapa
}

//Testa qual estado corresponde a posicao clicada e verifica acerto
void TestaEstados(Jogador *jogador, Lista *lista, ClickIndex index, EstadosPadrao *Acre, EstadosPadrao *Alagoas, EstadosPadrao *Amapa, EstadosPadrao *Amazonas, EstadosPadrao *Bahia,
	EstadosPadrao *Ceara, EstadosPadrao *DistritoFederal, EstadosPadrao *EspiritoSanto, EstadosPadrao *Goias, EstadosPadrao *Maranhao,
	EstadosPadrao *MatoGrosso, EstadosPadrao *MatoGrossoDoSul, EstadosPadrao *MinasGerais, EstadosPadrao *Para, EstadosPadrao *Paraiba,
	EstadosPadrao *Parana, EstadosPadrao *Pernambuco, EstadosPadrao *Piaui, EstadosPadrao *RioDeJaneiro, EstadosPadrao *RioGrandeDoNorte,
	EstadosPadrao *RioGrandeDoSul, EstadosPadrao *Rondonia, EstadosPadrao *SantaCatarina, EstadosPadrao *SaoPaulo, EstadosPadrao *Sergipe,
	EstadosPadrao *Tocantins)
{
	int i = 0;

#pragma region ESTADOS
	// Verificamos a posicao do click em relação à posição no mapa
	// E verificamos se o index da palavra que esta caindo é igual ao
	// indice da palavra que corresponde ao click do jogador
	// caso seja a isMaxHeight é true para limpar as palavras caindo
	// e acertou é igual a true para podermos sortear a próxima palavra
#pragma region ACRE
	for (i = 0; i < acreIndexSize; i++)
	{
		ClickIndex temp = Acre->index[i];
		if (temp.i == index.i && temp.j == index.j)
		{
			if (lista->indexAtual == Acre->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Alagoas->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Amapa->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Amazonas->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Bahia->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Ceara->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == DistritoFederal->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == EspiritoSanto->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Goias->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Maranhao->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == MatoGrosso->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == MatoGrossoDoSul->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == MinasGerais->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Para->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Paraiba->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Parana->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Pernambuco->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Piaui->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == RioDeJaneiro->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == RioGrandeDoNorte->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == RioGrandeDoSul->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Rondonia->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
			}
			printf("%s \n", Estados[Rondonia->myIndexPosition]);
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
			if (lista->indexAtual == SantaCatarina->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == SaoPaulo->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Sergipe->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
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
			if (lista->indexAtual == Tocantins->myIndexPosition)
			{
				jogador->acertos++;
				jogador->acertou = true;
				lista->isMaxHeight = true;
			}
			else {
				jogador->acertou = false;
				jogador->erros++;
			}
			printf("%s \n", Estados[Tocantins->myIndexPosition]);
			return;
		}
	}
#pragma endregion

#pragma endregion

}





