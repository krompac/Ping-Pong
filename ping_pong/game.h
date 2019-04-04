#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "menu.h"
#undef main

class Game
{
	private:
		SDL_Window *prozor;
		SDL_Renderer *renderer;
		SDL_Event dogadjaj;
		SDL_Event message_dogadjaj;
		SDL_Rect lijevi_pad;
		SDL_Rect desni_pad;
		SDL_Rect loptica;
		SDL_Rect game_window;
		SDL_Rect settings_window;

		SDL_Texture *left_score;
		SDL_Texture *right_score;
		SDL_Texture *dvotocka_textura;
		SDL_Texture *message_textura;
		SDL_Texture *answers_textura[2];
		SDL_Texture *loptica_slika;

		TTF_Font* font;
		SDL_Color boja;
		SDL_Surface *povrsina;

		SDL_Rect prvi_broj;
		SDL_Rect drugi_broj;
		SDL_Rect message_box;
		SDL_Rect message;
		SDL_Rect answers[2];
		SDL_Rect dvotocka;
		SDL_Rect *menuitems;

		Menu menu;

		struct 
		{
			int x, y;
		} ball_origin;

		std::string broj;

		const int sirina = 1000;
		const int visina = 600;

		int frame_time;
		int speed_x;
		int speed_y;
		int z_lijevi_pad;
		int z_desni_pad;
		int rotator;
		int pad_collision_surface;
		int koeficijent;
		int lijevi_rezultat;
		int desni_rezultat;
		int menu_position;
		int message_position;
		float starting_ball_speed;

		bool desno;
		bool gore;
		bool pause;
		bool quit_game;

		void init();
		void render_game_window(bool is_message = false);
		void render_score(SDL_Texture **score, int number);
		void render_settings_window();
		void initialize_message(std::string message);
		void initialize_game_components();
		void free();
		void set_origin();
		void free_score(SDL_Texture *score);
		bool message_box_action();
		bool kretnja_loptice();
		bool track_rightpad();
		bool main_loop();
		bool check_corner();

	public:
		Game();
		~Game();
};


