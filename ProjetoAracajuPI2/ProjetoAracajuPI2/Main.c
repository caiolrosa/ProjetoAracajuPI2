#include <stdio.h>
#include <allegro5\allegro.h>
#include "Objects.h"

// Variaveis globais
const int width = 800;
const int height = 400;

// Prototipos

int main() {

	// Tipos Primitivos
	bool finished = false;
	const int FPS = 60;

	// Variaveis de objeto
	

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
	display = al_create_display(width, height);

	// Caso nao inicializar o display retorna -1 para o SO
	if (!display)
	{
		return -1;
	}

	// Looping Principal
	while (!finished) {
		// ...
	}
}