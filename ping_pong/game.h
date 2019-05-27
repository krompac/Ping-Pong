#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "menu.h"
#include "settings.h"
#include "Options.h"
#undef main

class Game
{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event event_handler;
		SDL_Event message_event;
		SDL_Rect left_pad;
		SDL_Rect right_pad;
		SDL_Rect ball;
		SDL_Rect game_window;

		SDL_Texture *left_score;
		SDL_Texture *right_score;
		SDL_Texture *colon_texture;
		SDL_Texture *message_texture;
		SDL_Texture *answers_textures[2];
		SDL_Texture *ball_picture;
		SDL_Texture *winner_texture;

		TTF_Font* font;
		SDL_Color color;
		SDL_Surface *surface;

		SDL_Rect winner_rect;
		SDL_Rect first_number;
		SDL_Rect second_number;
		SDL_Rect message_box;
		SDL_Rect message;
		SDL_Rect answers[2];
		SDL_Rect colon;
		SDL_Rect *menuitems;

		Menu menu;
		Settings settings_window;
		SpeedOptions speed_options;
		ScoreOptions score_options;

		struct 
		{
			int x, y;
		} ball_origin;

		std::string text_to_convert;

		const int WIDTH = 1000;
		const int HEIGHT = 600;

		int frame_time;
		int speed_x;
		int speed_y;
		int z_left_pad;
		int z_right_pad;
		int rotator;
		int pad_collision_surface;
		int coefficient;
		int first_score;
		int second_score;
		int player1_rounds;
		int player2_rounds;
		int max_score;
		int number_of_rounds;

		//predstavlja index menu itema {0: start game, 1: scoreboard, 2: options, 3: quit game}
		int menu_position;
		//DA pozicija 0, NE pozicija 1
		int message_position;
		float starting_ball_speed;

		bool ball_going_right;
		bool ball_going_up;
		bool pause;
		bool game_won;

		void Init();
		void Render_Game_Window(bool is_message = false);
		void Texture_From_Text(SDL_Texture **texture, int number = 0, std::string text = "");
		void Initialize_Message(std::string message);
		void Restart_Game();
		void Initialize_Game_Components();
		void Free();
		void Update_Ball_Origin();
		void Free_Texture(SDL_Texture *texture);
		bool Message_Box_Action();
		void Ball_Movement();
		bool Track_Rightpad();
		bool Main_Loop();
		bool Check_Corner();
		bool Settings_Window_Action();

	public:
		Game();
		~Game();
};


