#pragma region Include

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include "Objects.h"

#pragma endregion

// Variaveis globais
const int WIDTH = 1280;
const int HEIGHT = 720;
const int WIDTHMAPA = 650;
const int HEIGHTMAPA = 650;

//variaveis da matriz
const int TOTAL_DE_LINHAS = 26;
const int TOTAL_DE_COLUNAS = 26;

// Prototipos
void InitJogador(Jogador *jogador);
void InitLista(Lista *lista);
void UpdateLista(ALLEGRO_FONT *fontLista, Jogador *jogador,Lista *lista);
char *SortLista();
void CreateMatrix(float lines[], float columns[], int totalLines, int totalColumns);
int CheckClickPosition(float lines[], float columns[], int totalLines, int totalColumns, ALLEGRO_EVENT ev);

int main() {
	// Tipos Primitivos
	bool finished = false;
	bool redraw = true;
	const int FPS = 60;
	float mLines[26];
	float mColumns[26];
	srand(time(NULL));
	int ScoreRandom = rand();

	// Variaveis de objeto
	Jogador jogador;
	Lista lista;
	SaoPaulo SP;

	// Variaveis do Allegro
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *mapaBrasil = NULL;
	ALLEGRO_FONT *fontLista = NULL;

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
	al_init_font_addon();										// Possibilita escrever na tela
	al_init_ttf_addon();										// Possibilita usar formato ttf
	al_init_image_addon();										// Possibilita usar varios formatos de imagem
	al_init_primitives_addon();									// Possibilita usar formas geometricas

	// Carrega os bitmaps
	//mapaBrasil = al_load_bitmap("imgs/Brasil-3D.png");			// Cria o bitmap com as medidas das variaveis passadas como parametros
	mapaBrasil = al_load_bitmap("imgs/Brasil-3D grid.png"); // bmp de testes para encontrar o indice correto
	int mapaWidth = al_get_bitmap_width(mapaBrasil);			// Recebe o tamanho X da imagem
	int mapaHeight = al_get_bitmap_height(mapaBrasil);			// Recebe o tamanho Y da imagem
	al_draw_scaled_bitmap(mapaBrasil, -0, -0, mapaWidth, mapaHeight, 0, 0, WIDTHMAPA, HEIGHTMAPA, 0);

	// Carrega as fonts
	fontLista = al_load_font("fonts/Magnificent.ttf", 20, 0);

	// Inicializacao dos nossos objetos
	CreateMatrix(mLines, mColumns, TOTAL_DE_LINHAS, TOTAL_DE_COLUNAS);
	InitJogador(&jogador);
	InitLista(&lista);
	InitSP(&SP);

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
			redraw = true;
		} 
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)			// Permite fechar a janela pelo X
		{
			finished = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) // Verifica se houve input de click na tela
		{
			CheckClickPosition(mLines, mColumns, TOTAL_DE_LINHAS, TOTAL_DE_COLUNAS, ev); //checa se o click foi no mapa
		}

		if (redraw && al_is_event_queue_empty(event_queue))			// Permite saber quando podemos redesenhar na tela
		{															// Lista de eventos vazia e (evitar bugs)
			redraw = false;

			UpdateLista(fontLista, &jogador, &lista);
			
			al_draw_scaled_bitmap(mapaBrasil, 0, 0, mapaWidth, mapaHeight, 0, 0, WIDTHMAPA, HEIGHTMAPA, 0);		// Coloca o mapa na tela
			al_flip_display();									// Muda para o back buffer
			al_clear_to_color(al_map_rgb(255, 255, 255));		// Limpa a tela			
		}
	}

	// Libera a memoria alocada para variaveis Allegro
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(mapaBrasil);
	al_destroy_font(fontLista);
}

// Definicao de funcoes
/// <summary>
/// Inicializa o jogador
/// </summary>
/// <param name="jogador">Recebe o jogador</param>
void InitJogador(Jogador *jogador)
{
	jogador->pontos = 0;
	jogador->vidas = 5;
}

/// <summary>
/// Inicializa a lista de palavras
/// </summary>
/// <param name="lista">Recebe a lista de palavras</param>
void InitLista(Lista *lista)
{
	lista->velocidade = 30;
	lista->heightLista = 0;
	lista->randomNumber = 0;
	lista->palavraAtual = NULL;
}

/// <summary>
/// Altera o valor Y do elemento da lista de acordo velocidade
/// da lista(lista->velocidade) para dar noção de animação
/// </summary>
/// <param name="fontLista">Fonte utilizada para escrever na tela</param>
/// <param name="jogador">Struct do Jogador</param>
/// <param name="lista">Struct da Lista</param>
void UpdateLista(ALLEGRO_FONT *fontLista, Jogador *jogador, Lista *lista)
{
	srand(time(NULL));

	// Caso a palavra tenha chegado na altura maxima devemos resetar a lista
	if (lista->isMaxHeight)
	{
		lista->heightLista = 0;
		lista->velocidade = 30;
		lista->palavraAtual = NULL;
		lista->randomNumber = rand();
		jogador->pontos += 50;
		al_clear_to_color(al_map_rgb(255, 255, 255));
	}

	if (lista->palavraAtual == NULL)
	{
		lista->palavraAtual = SortLista();
	}

	// Caso a altura da palavra seja menor que a altura do mapa devemos continuar a animação de "queda"
	if (lista->heightLista < HEIGHTMAPA)
	{	
		al_clear_to_color(al_map_rgb(255, 255, 255));
		
		// Aumentamos a dificuldade do jogo de acordo com o score do jogador, colocando siglas, estados e capitais juntos
		if (jogador->pontos < 100)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s", lista->palavraAtual);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 0)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s    %s", Estados[lista->randomNumber % 27], Siglas[lista->randomNumber % 27]);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 1)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s    %s", Capitais[lista->randomNumber % 27], Siglas[lista->randomNumber % 27]);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 2)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s    %s", Estados[lista->randomNumber % 27], Capitais[lista->randomNumber % 27]);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 3)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s", lista->palavraAtual);
		}
		
		// Aumentamos a altura da lista de acordo com a velocidade para dar noção de animação
		// isMaxHeigth permite sabermos que a palavra nao chegou ao final da lista, entao nao devemos reseta-la
		lista->heightLista = lista->velocidade + 10;
		lista->velocidade += 5;
		lista->isMaxHeight = false;
	}
	else {
		if (jogador->pontos < 100)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s", lista->palavraAtual);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 0)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s    %s", Estados[lista->randomNumber % 27], Siglas[lista->randomNumber % 27]);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 1)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s    %s", Capitais[lista->randomNumber % 27], Siglas[lista->randomNumber % 27]);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 2)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s    %s", Estados[lista->randomNumber % 27], Capitais[lista->randomNumber % 27]);
		}
		if (jogador->pontos >= 100 && lista->randomNumber % 4 == 3)
		{
			al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 70, lista->velocidade + 10, 0, "%s", lista->palavraAtual);
		}

		// Chegamos ao final da lista, então isMaxHeight é true
		lista->isMaxHeight = true;
	}
}


/// <summary>
/// Sorteia uma a uma as palavras simples (somente estado, sigla ou capital)
/// </summary>
/// <returns>Ponteiro para char (string) que representa o estado, sigla ou capital sorteado</returns>
char *SortLista()
{
	srand(time(NULL));
	int multiSort = rand();

	switch ((rand() * 5) % 3)
	{
	case 0:
		return Estados[rand() % 27];
		break;
	case 1:
		return Siglas[rand() % 27];
		break;
	case 2:
		return Capitais[rand() % 27];
		break;
	default:	
		printf("Deu Ruim");
		break;
	}

	printf("Deu Muito Ruim");
	return "0";
}


/// <summary>
/// Cria matriz sob o Bitmap para poder identificar o click
/// </summary>
/// <param name="lines">Vetor contendo as linhas da matriz</param>
/// <param name="columns">Vetor contendo as colunas da matriz</param>
/// <param name="totalLines">Total de linhas da matriz</param>
/// <param name="totalColumns">Total de colunas da matriz</param>
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


/// <summary>
/// Retorna 0 caso não esteja dentro da matriz e 1 caso esteja
/// e verifica em qual indice aconteceu o click
/// </summary>
/// <param name="lines">Vetor contendo as linhas da matriz</param>
/// <param name="columns">Vetor contendo as colunas da matriz</param>
/// <param name="totalLines">Total de linhas da matriz</param>
/// <param name="totalColumns">Total de colunas da matriz</param>
/// <param name="ev">Recebe o evento do allegro, no caso o click do mouse</param>
/// <returns></returns>
int CheckClickPosition(float lines[], float columns[], int totalLines, int totalColumns, ALLEGRO_EVENT ev)
{
	int x = ev.mouse.x, y = ev.mouse.y;
	printf("x = %d y - %d\n", x, y);

	int i = 0, j = 0;
	for (i = 0; i < totalLines; i++) // percorre todas as linhas
	{
		for (j = 0; j < totalColumns; j++) // percorre todas as colunas
		{
			if (x > ((j != 0) ? columns[j - 1] : 0) && x < columns[j] && y < lines[i]) //nesse caso está dentro do range desse quadrado
			{
				printf("i - %d, j %d\n", i, j);

				// Sao Paulo
				if (i >= 16 && i <= 18 && j >= 13 && j <= 15)
				{
					printf("Clicou em SP");
				}

				return 1; //verdadeiro para quando o click estiver no mapa
			}
		}
	}

	return 0; //falso para quando esta fora do mapa
}
