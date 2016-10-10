#pragma region Include

#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include "Objects.h"

#pragma endregion

// Variaveis globais
const int WIDTH = 900;
const int HEIGHT = 700;
const int WIDTHMAPA = 650;
const int HEIGHTMAPA = 650;

// Prototipos
void InitJogador(Jogador *jogador);
void InitLista(Lista *lista);
void UpdateLista(ALLEGRO_FONT *fontLista, Lista *lista);
void SortLista(char *sortedLista[]);

int main() {
	// Tipos Primitivos
	bool finished = false;
	bool redraw = true;
	const int FPS = 60;

	// Variaveis de objeto
	Jogador jogador;
	Lista lista;

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

	// Addons e instala��es do allegro
	al_install_mouse();											// Possibilita o uso do mouse
	al_init_font_addon();										// Possibilita escrever na tela
	al_init_ttf_addon();										// Possibilita usar formato ttf
	al_init_image_addon();										// Possibilita usar varios formatos de imagem

	// Carrega os bitmaps
	mapaBrasil = al_load_bitmap("imgs/Brasil-3D.png");			// Cria o bitmap com as medidas das variaveis passadas como parametros
	int mapaWidth = al_get_bitmap_width(mapaBrasil);			// Recebe o tamanho X da imagem
	int mapaHeight = al_get_bitmap_height(mapaBrasil);			// Recebe o tamanho Y da imagem

	// Carrega as fonts
	fontLista = al_load_font("fonts/Magnificent.ttf", 20, 0);

	// Inicializacao dos nossos objetos
	InitJogador(&jogador);
	InitLista(&lista);
	SortLista(sortedLista);

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

		// � invocado a cada frame "Fun��o de update" 
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
		} 
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)			// Permite fechar a janela pelo X
		{
			finished = true;
		}

		if (redraw && al_is_event_queue_empty(event_queue))			// Permite saber quando podemos redesenhar na tela
		{															// Lista de eventos vazia e (evitar bugs)
			redraw = false;

			UpdateLista(fontLista, &lista);
			al_draw_scaled_bitmap(mapaBrasil, -150, -50, mapaWidth, mapaHeight, 0, 0, WIDTHMAPA, HEIGHTMAPA, 0);		// Coloca o mapa na tela
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
void InitJogador(Jogador *jogador)
{
	jogador->pontos = 0;
	jogador->vidas = 5;
}

void InitLista(Lista *lista)
{
	lista->velocidade = 30;
	lista->heightLista = 0;
	lista->posicao = 0;
}

void UpdateLista(ALLEGRO_FONT *fontLista, Lista *lista)
{
	if (lista->isMaxHeight)
	{
		lista->heightLista = 0;
		lista->velocidade = 30;
	}

	if (lista->heightLista < HEIGHTMAPA)
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 50, lista->velocidade + 10, 0, "%s", sortedLista[lista->posicao]);
		lista->heightLista = lista->velocidade + 10;
		lista->velocidade += 5;
		lista->isMaxHeight = false;
	}
	else {
		al_draw_textf(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 50, HEIGHTMAPA, 0, "%s", sortedLista[lista->posicao]);
		lista->isMaxHeight = true;
		lista->posicao++;
	}
}

void SortLista(char *sortedLista[])
{
	int i;
	srand(time(NULL));
	
	for (i = 0; i < 100; i++)
	{
		switch ((rand() * 5) % 3)
		{
		case 0:
			sortedLista[i] = Estados[rand() % 27];
			break;
		case 1:
			sortedLista[i] = Siglas[rand() % 27];
			break;
		case 2:
			sortedLista[i] = Capitais[rand() % 27];
			break;
		default:
			break;
		}
	}	
}
