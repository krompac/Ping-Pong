#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "menu.h"
#include "settings.h"
#include "Scoreboard.h"
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
		Colors left_pad_color;
		SDL_Rect right_pad;
		Colors right_pad_color;
		
		SDL_Rect ball;
		SDL_Rect game_window;

		SDL_Texture *left_score;
		SDL_Texture *right_score;
		SDL_Texture *colon_texture;
		SDL_Texture *message_texture;
		SDL_Texture *answers_textures[2];
		SDL_Texture *ball_picture;
		SDL_Texture *winner_texture;
		SDL_Texture *some_texture;

		TTF_Font *font;
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
		SDL_Rect some_text_rect;

		Menu menu;
		Settings settings_window;
		Scoreboard scoreboard_window;
		Score_Entry entry;
		SpeedOptions speed_options;
		ScoreOptions score_options;
		TextureColorOptions ball_color;
		PadColorOptions left_pad_options;
		PadColorOptions right_pad_options;

		struct { int x, y; } ball_origin;

		std::string text_to_convert;
		std::string some_text;

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
		bool player1_entered_name;
		bool player2_entered_name;

		void Init();
		void Render_Game_Window(bool is_message = false);
		void Texture_From_Text(SDL_Texture **texture, int number = 0, std::string text = "");
		void Initialize_Message(std::string message);
		void Restart_Game();
		void Initialize_Game_Components();
		void Free();
		void Update_Ball_Origin();
		void Free_Texture(SDL_Texture *texture);
		void Entry_Input(char *player_name, int &player_score, int achieved_score, bool &player_entered_name);
		void Ball_Movement();
		void Enter_Record();
		bool Message_Box_Action();
		bool Track_Rightpad();
		bool Main_Loop();
		bool Check_Corner();
		bool Text_Input();
		void Set_Text_Width();

	public:
		Game();
		~Game();
};