#pragma region Include

#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Objects.h"

#pragma endregion

// Variaveis globais
const int WIDTH = 800;
const int HEIGHT = 400;

// Prototipos
void InitJogador(Jogador *jogador);

int main() {

	// Tipos Primitivos
	bool finished = false;
	const int FPS = 60;

	// Variaveis de objeto
	Jogador jogador;

	// Variaveis do Allegro
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	// Inicializa o Allegro
	if (!al_init())
	{
		return -1;
	}

	// Initialize display
	display = al_create_display(WIDTH, HEIGHT);					// Inicializa o display

	// Addons e instalações do allegro
	al_install_mouse();											// Possibilita o uso do mouse
	al_init_font_addon();										// Possibilita escrever na tela
	al_init_ttf_addon();										// Possibilita usar formato ttf

	// Inicializacao dos nossos objetos
	InitJogador(&jogador);

	event_queue = al_create_event_queue();						// Cria "lista" de eventos
	timer = al_create_timer(1 / FPS);							// Inicializa o timer para que tenhamos 60 fps

	// Registro de eventos para a lista de eventos
	al_register_event_source(event_queue, al_get_mouse_event_source());			// Registra o mouse na lista de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(timer));			// Registra o timer na lista de eventos
	al_register_event_source(event_queue, al_get_display_event_source(display));			// Registra o display na lista de eventos

	// Caso nao inicializar o display retorna -1 para o SO
	if (!display)
	{
		return -1;
	}

	// Looping Principal
	while (!finished) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		// É invocado a cada frame "Função de update" 
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{

		}

		// Permite fechar a janela pelo X
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			finished = true;
		}
	}
}

// Definicao de funcoes
void InitJogador(Jogador *jogador)
{
	jogador->pontos = 0;
	jogador->vidas = 5;
}
