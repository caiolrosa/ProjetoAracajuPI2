#pragma region Include

#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include "Objects.h"

#pragma endregion

// Variaveis globais
const int WIDTH = 1000;
const int HEIGHT = 800;
const int WIDTHMAPA = 670;
const int HEIGHTMAPA = 800;

// Prototipos
void InitJogador(Jogador *jogador);

int main() {

	// Tipos Primitivos
	bool finished = false;
	bool redraw = true;
	const int FPS = 60;

	// Variaveis de objeto
	Jogador jogador;

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

	// Carrega os bitmaps
	mapaBrasil = al_load_bitmap("imgs/Brasil-3D.png");			// Cria o bitmap com as medidas das variaveis passadas como parametros
	int mapaWidth = al_get_bitmap_width(mapaBrasil);			// Recebe o tamanho X da imagem
	int mapaHeight = al_get_bitmap_height(mapaBrasil);			// Recebe o tamanho Y da imagem

	// Carrega as fonts
	fontLista = al_load_font("fonts/AlexandriaFLF.ttf", 20, 0);

	// Inicializacao dos nossos objetos
	InitJogador(&jogador);

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

		if (redraw && al_is_event_queue_empty(event_queue))			// Permite saber quando podemos redesenhar na tela
		{															// Lista de eventos vazia e (evitar bugs)
			redraw = false;

			al_draw_text(fontLista, al_map_rgb(0, 0, 0), WIDTHMAPA + 100, 10, 0, "Santa Catarina");		// Coloca o texto da lista na tela
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
void InitJogador(Jogador *jogador)
{
	jogador->pontos = 0;
	jogador->vidas = 5;
}
