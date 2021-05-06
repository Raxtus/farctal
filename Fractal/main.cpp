#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int X_MOVE = 800;
int Y_MOVE = 300;

using namespace std;

float a = 1;

ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);


int power(int x, int n)
{
	if (n <= 0)
		return 1;
	else
		return x * power(x, n - 1);
}

void generate(int n, int xd, int yd)
{
	int move = power(3, n);
	if (n > 1)
	{

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				generate(n - 1, xd + move * x / 3, yd + move * y / 3);
			}
		}

	}
	float x_corner = xd + move / 3;
	float x2_corner = xd + move * 2 / 3;
	float y_corner = yd + move / 3;
	float y2_corner = yd + move * 2 / 3;

	al_draw_filled_rectangle(x_corner *a, y_corner *a, x2_corner *a, y2_corner *a, white);
}

int main()
{
	if (!al_init()) return -1;
	if (!al_init_primitives_addon()) return -1;

	int z = 3;
	int dim = power(3, z);;
	int done = 1;

	ALLEGRO_DISPLAY *window = al_create_display(1920, 1080);
	al_set_window_position(window, 0, 0);
	ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
	ALLEGRO_EVENT event;

	ALLEGRO_BITMAP *fractal;

	al_install_keyboard();
	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_keyboard_event_source());

	fractal = al_create_bitmap(dim, dim);

	while (done >= 0)
	{
		cout << z <<" "<< a << endl;
		dim = power(3, z);
		al_clear_to_color(black);
		if (done == 1)
		{
			al_destroy_bitmap(fractal);
			fractal = al_create_bitmap(dim, dim);
			al_set_target_bitmap(fractal);
			generate(z, 0, 0);
			al_set_target_backbuffer(window);
		}
		al_draw_scaled_bitmap(fractal, 0, 0, dim, dim, X_MOVE, Y_MOVE, dim*a, dim*a, 0);


		al_flip_display();

		done = 0;

		al_wait_for_event(queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = -1;
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				Y_MOVE -= 10;
				break;
			case ALLEGRO_KEY_DOWN:
				Y_MOVE += 10;
				break;
			case ALLEGRO_KEY_LEFT:
				X_MOVE -= 10;
				break;
			case ALLEGRO_KEY_RIGHT:
				X_MOVE += 10;
				break;
			case ALLEGRO_KEY_W:
				a += 1;
				break;
			case ALLEGRO_KEY_Q:
				if (a <= 0) break;
				a -= 1;
				break;
			case ALLEGRO_KEY_R:
				a += 0.1;
				break;
			case ALLEGRO_KEY_E:
				if (a <= 0) break;
				a -= 0.1;
				break;
			case ALLEGRO_KEY_Z:
				if (z >= 8) break;
				z += 1;
				done = 1;
				break;
			case ALLEGRO_KEY_X:
				if (z <= 0) break;
				z -= 1;
				done = 1;
				break;
			case ALLEGRO_KEY_S:
				al_save_bitmap("fractal.bmp", fractal);
				break;
			default:
				break;
			}
		default:
			break;
		}

	}

	al_destroy_event_queue(queue);

	return 0;
}