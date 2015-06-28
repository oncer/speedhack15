#include "common.h"
#include "plant.h"

ALLEGRO_DISPLAY *g_display;

int main(int argc, char **argv)
{
	rng_init();
	if (!al_init()) {
		return 1;
	}
	al_install_keyboard();
	al_init_image_addon();

	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	g_display = al_create_display(800, 480);
	bool quit;
	ALLEGRO_EVENT_QUEUE *queue;
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(g_display));
	ALLEGRO_EVENT event;
	Plant plant;
	while (!quit)
	{
		while (al_get_next_event(queue, &event)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				quit = true;
			} else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (event.type == ALLEGRO_KEY_ESCAPE) {
					quit = true;
				}
			} else if (event.type == ALLEGRO_KEY_F11) {
				bool opp = !(al_get_display_flags(g_display) & ALLEGRO_FULLSCREEN_WINDOW);
				al_toggle_display_flag(g_display, ALLEGRO_FULLSCREEN_WINDOW, opp);
			}
		}

		ALLEGRO_COLOR black;
		black.r = black.g = black.b = 0;
		black.a = 255;

		al_clear_to_color(black);
		plant.update();
		plant.draw();

		al_flip_display();
		al_rest(0.02);
	}
	al_destroy_display(g_display);
	al_destroy_event_queue(queue);
	return 0;
}

