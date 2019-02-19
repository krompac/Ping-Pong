#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#undef main

class menu_item
{
	public:
		menu_item *prev, *next;
		SDL_Rect *item;
};

class Game
{
	private:
		SDL_Window *prozor;
		SDL_Renderer *renderer;
		SDL_Rect lijevi_pad;
		SDL_Rect desni_pad;
		// struct Loptica
		// {
		//     int x, y, r;
		// } loptica;
		SDL_Rect loptica;
		SDL_Rect game_window;

		SDL_Texture *start_game_textura;
		SDL_Texture *scoreboard_textura;
		SDL_Texture *options_textura;
		SDL_Texture *quit_textura;
		SDL_Texture *left_score;
		SDL_Texture *right_score;
		SDL_Texture *dvotocka_textura;

		TTF_Font* font;
		SDL_Color boja;
		SDL_Surface *povrsina;
		SDL_Rect start_game;
		SDL_Rect scoreboard;
		SDL_Rect options;
		SDL_Rect quit;
		SDL_Rect prvi_broj;
		SDL_Rect drugi_broj;
		SDL_Rect dvotocka;

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

		bool desno;
		bool gore;
		bool pause;

		void init();
		void render();
		void render_score(SDL_Texture **score, int number);
		void free();
		void free_score(SDL_Texture *score);
		void DrawCircle(SDL_Renderer *Renderer, int _x, int _y, int radius);
		bool kretnja_loptice();
		bool main_loop();

	public:
		Game();
		~Game();
};


