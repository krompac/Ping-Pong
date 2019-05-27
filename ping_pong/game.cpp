#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <math.h>
#include "game.h"
#include "menu.h"

using namespace std;

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->surface = nullptr;
	this->left_score = nullptr;
	this->right_score = nullptr;
	this->colon_texture = nullptr;
	this->message_texture = nullptr;
	this->answers_textures[0] = nullptr;
	this->answers_textures[1] = nullptr;
	this->ball_picture = nullptr;
	this->winner_texture = nullptr;

	game_window = { 20, 20, 720, 480 };
	first_number = { 310, 520, 60, 70 };
	second_number = { 410, 520, 60, 70 };
	colon = { 375, 520, 30, 70 };
	
	winner_rect = { 180, 70, 400, 100 };
	message_box = { 180, 190, 400, 150 };
	message = { message_box.x + 10, message_box.y + 10, 380, 60 };
	answers[0] = { 250, 280, 100, 50 };
	answers[1] = { 430, 280, 100, 50 };
	max_score = 5;

	menuitems = new SDL_Rect[4];

	menu = Menu(menuitems);

	speed_options = SpeedOptions(starting_ball_speed);
	score_options = ScoreOptions(max_score);
	settings_window = Settings(menu, speed_options, score_options);

	Initialize_Game_Components();
	pad_collision_surface = right_pad.h / 2;
	coefficient = pad_collision_surface / 10; //+ 0.5;

	color = { 255, 255, 255 };

	Init();
}

Game::~Game()
{
	delete menuitems;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
}

void Game::Initialize_Game_Components()
{
	//starting_ball_speed = 5;
	frame_time = 0;
	speed_x = starting_ball_speed;
	speed_y = 0;

	left_pad = { 20, 20, 20, 100 };
	right_pad = { 720, 20, 20, 100 };
	ball = { 370, 250, 20, 20 };

	first_score = 0;
	second_score = 0;
	text_to_convert = to_string(first_score);
	player1_rounds = 0;
	player2_rounds = 0;

	ball_going_right = ball_going_up = true;
	pause = false;
	game_won = false;
}

void Game::Free_Texture(SDL_Texture *texture)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	if (surface != nullptr)
	{
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
}

void Game::Free()
{
}

void Game::Texture_From_Text(SDL_Texture **texture, int number, string text)
{
	Free_Texture(*texture);
	if (text != "")
	{
		text_to_convert = text;
	}
	else
	{
		text_to_convert = to_string(number);
	}
	
	surface = TTF_RenderText_Solid(font, text_to_convert.c_str(), color);
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Game::Render_Game_Window(bool is_message)
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);

	SDL_RenderFillRect(renderer, &left_pad);
	SDL_RenderFillRect(renderer, &right_pad);

	SDL_RenderDrawRect(renderer, &first_number);
	SDL_RenderDrawRect(renderer, &second_number);
	SDL_RenderDrawRect(renderer, &colon);

	menu.Render_Menu(renderer);

	SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(renderer, &game_window);
	
	if (pause)
	{
		SDL_RenderDrawRect(renderer, &menuitems[menu_position]);
	}

	SDL_RenderCopy(renderer, colon_texture, NULL, &colon);
	SDL_RenderCopy(renderer, left_score, NULL, &first_number);
	SDL_RenderCopy(renderer, right_score, NULL, &second_number);
	SDL_RenderCopy(renderer, ball_picture, NULL, &ball);

	if (is_message)
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

		SDL_RenderFillRect(renderer, &message_box);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
		SDL_RenderDrawRect(renderer, &message_box);

		SDL_RenderCopy(renderer, message_texture, NULL, &message);

		SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
		SDL_RenderDrawRect(renderer, &answers[message_position]);
		SDL_RenderCopy(renderer, answers_textures[0], NULL, &answers[0]);
		SDL_RenderCopy(renderer, answers_textures[1], NULL, &answers[1]);
	}

	if (game_won)
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
		SDL_RenderDrawRect(renderer, &winner_rect);
		SDL_RenderCopy(renderer, winner_texture, NULL, &winner_rect);
	}
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(renderer);
}

void Game::Initialize_Message(string message)
{
	surface = TTF_RenderText_Solid(font, message.c_str(), color);
	message_texture = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderText_Solid(font, "Yes", color);
	answers_textures[0] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderText_Solid(font, "No", color);
	answers_textures[1] = SDL_CreateTextureFromSurface(renderer, surface);
}

void Game::Restart_Game()
{
	Initialize_Message("Would you like to start again?");
	while (Message_Box_Action());
}

bool Game::Message_Box_Action()
{
	Render_Game_Window(true);

	while (SDL_PollEvent(&message_event))
	{
		if (message_event.type == SDL_QUIT)
			this->~Game();
		else if (message_event.type == SDL_KEYDOWN)
		{
			switch (message_event.key.keysym.sym)
			{
				case SDLK_LEFT:
					if (message_position)
					{
						message_position--;
					}
					break;
				case SDLK_RIGHT:
					if (!message_position)
					{
						message_position++;
					}
					break;
				case SDLK_SPACE:
					if (!message_position && menu_position == 0)
					{
						Initialize_Game_Components();
						Texture_From_Text(&left_score, 0);
						Texture_From_Text(&right_score, 0);
					}

					if (!game_won)
					{
						pause = false;
						Render_Game_Window();
						SDL_Delay(500);
					}
					
					return false;
			}
		}

		Render_Game_Window(true);
		SDL_Delay(1);

		return true;
	}

	Render_Game_Window(true);
	SDL_Delay(1);

	return true;
}

void Game::Update_Ball_Origin()
{
	ball_origin = { ball.x + ball.w / 2, ball.y + ball.h / 2 };
}

void Game::Ball_Movement()
{
	if (!pause)
	{
		int y = ball.y + ball.h / 2;

		if (frame_time + 1000 / 60 < SDL_GetTicks())
		{
			frame_time = SDL_GetTicks();
			if (ball_going_right)
			{
				ball.x += speed_x;
				Update_Ball_Origin();

				if (ball_origin.x + ball.w / 2 >= game_window.w + game_window.x)
				{
					ball.x = game_window.x + game_window.w - ball.w;
					Update_Ball_Origin();
					ball_going_right = false;
					first_score++;
					Texture_From_Text(&left_score, first_score);
				}

				if (Check_Corner() || ((ball_origin.x + ball.w / 2 >= right_pad.x) && (ball_origin.y - ball.h / 2) >= right_pad.y && ball_origin.y + ball.h / 2  <= (right_pad.y + right_pad.h)))
				{
					ball_going_right = false;
					z_right_pad = right_pad.y + (right_pad.h / 2);
					speed_y = abs(z_right_pad - ball_origin.y) / coefficient;
					speed_x = starting_ball_speed + 1 - (speed_y / starting_ball_speed);
					ball_going_up = (z_right_pad < y);
					starting_ball_speed += 0.2;
				}
			}
			else
			{
				ball.x -= speed_x;
				Update_Ball_Origin();

				if (ball.x <= game_window.x)
				{
					ball.x = game_window.x;
					Update_Ball_Origin();
					ball_going_right = true;
					second_score++;
					Texture_From_Text(&right_score, second_score);
				}

				if (Check_Corner() || ((ball_origin.x - ball.w / 2 <= left_pad.x + left_pad.w) && (ball_origin.y - ball.h / 2) >= left_pad.y && ball_origin.y + ball.h / 2 <= (left_pad.y + left_pad.h)))
				{
					ball_going_right = true;
					z_left_pad = left_pad.y + (left_pad.h / 2);
					speed_y = abs(z_left_pad - y) / coefficient;
					speed_x = starting_ball_speed + 1 - (speed_y / starting_ball_speed);
					ball_going_up = (z_left_pad < y);
					starting_ball_speed += 0.2;
				}
			}

			if (ball_going_up)
			{
				ball.y += speed_y;
				Update_Ball_Origin();

				if (ball.y + ball.h >= game_window.h + game_window.y)
				{
					ball_going_up = false;
					ball.y = game_window.h;
					Update_Ball_Origin();
				}
			}
			else
			{
				ball.y -= speed_y;
				Update_Ball_Origin();

				if (ball.y <= game_window.y)
				{
					ball_going_up = true;
					ball.y = game_window.y;
					Update_Ball_Origin();
				}
			}
		}
	}

	if (first_score == max_score)
	{
		Texture_From_Text(&winner_texture, 0, "Player 1 Wins");
		game_won = true;
		Restart_Game();
	}
	else if (second_score == max_score)
	{
		Texture_From_Text(&winner_texture, 0, "Player 2 Wins");
		game_won = true;
		Restart_Game();
	}
}

bool Game::Track_Rightpad()
{
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (!pause)
	{
		if (keyboard_state_array[SDL_SCANCODE_UP])
		{
			if (right_pad.y - 1 >= game_window.y)
				right_pad.y -= 1;
		}
		else if (keyboard_state_array[SDL_SCANCODE_DOWN])
		{
			if (right_pad.y + 1 + right_pad.h <= game_window.h + game_window.y)
				right_pad.y += 1;
		}
	}
	return true;
}

bool Game::Main_Loop()
{
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (!pause)
	{
		if (keyboard_state_array[SDL_SCANCODE_W])
		{
			if (left_pad.y - 1 >= game_window.y)
				left_pad.y -= 1;
		}
		else if (keyboard_state_array[SDL_SCANCODE_S])
		{
			if (left_pad.y + 1 + left_pad.h <= game_window.h + game_window.y)
				left_pad.y += 1;
		}
	}

	while (SDL_PollEvent(&event_handler))
	{
		if (event_handler.type == SDL_QUIT)
			return false;
		else if (event_handler.type == SDL_KEYDOWN)
		{
			if (pause)
			{
				if (event_handler.key.keysym.sym == SDLK_UP || event_handler.key.keysym.sym == SDLK_w)
				{
					if (menu_position > 0)
					{
						menu_position--;
					}
				}
				else if (event_handler.key.keysym.sym == SDLK_DOWN || event_handler.key.keysym.sym == SDLK_s)
				{
					if (menu_position < 3)
					{
						menu_position++;
					}
				}
				else if (event_handler.key.keysym.sym == SDLK_SPACE)
				{
					if (menu_position == 0)
					{
						message_position = 0;
						Restart_Game();
					}
					else if (menu_position == 2)
					{
						settings_window.Init_Textures(&renderer, font);
						do
						{
							settings_window.Render(&renderer);
						} while (settings_window.Window_Action(&renderer));
						settings_window.FreeData();
					}
					else if (menu_position == 3)
					{
						message_position = 1;
						Initialize_Message("Are you sure you want to guit the game?");
						while (Message_Box_Action());

						//vraca message_position jer je pozicija Yes odgovora na 0.-oj poziciji (false), a No je 1.-oj poziciji (true)
						return message_position;
					}
				}
			}

			if (event_handler.key.keysym.sym == SDLK_ESCAPE)
			{
				pause = !pause;
			}

			Ball_Movement();
			Render_Game_Window();

			return true;
		}
	}

	Ball_Movement();
	Render_Game_Window();
	SDL_Delay(1);

	return true;
}

bool Game::Check_Corner()
{
	int x_coord = - ball_origin.x;
	int y_coord = - ball_origin.y;

	x_coord += (ball_going_right) ? right_pad.x : left_pad.x + left_pad.w;
	y_coord += (ball_going_right) ? right_pad.y : left_pad.y;
	
	return ((pow((x_coord), 2) + pow((y_coord), 2)) <= pow(ball.w / 2, 2)) || ((pow((x_coord), 2) + pow((y_coord + right_pad.h), 2)) <= pow(ball.w / 2, 2));
}

bool Game::Settings_Window_Action()
{
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (pause)
	{

	}


	return true;
}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL nije mogel inicijalizirati!\nError: " << SDL_GetError() << endl;
	}
	else
	{
		if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer))
		{
			cout << "Greška kod pravljenja prozora i/ili renderera!\nError: " << SDL_GetError() << endl;
		}

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}

		if (TTF_Init() == -1)
		{
			cout << "Greska kod TTF inita!\n";
		}
		font = TTF_OpenFont("images/Sans.ttf", 100);
		
		menu.Init(surface, font, color, renderer);

		surface = TTF_RenderText_Solid(font, ":", color);
		colon_texture = SDL_CreateTextureFromSurface(renderer, surface);
		Texture_From_Text(&left_score, 0);
		Texture_From_Text(&right_score, 0);

		surface = IMG_Load("images/circle.png");
		ball_picture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_SetTextureColorMod(ball_picture, 0x00, 0xff, 0x00);
		
		Render_Game_Window();

		while (Main_Loop() && Track_Rightpad() && !game_won);
	}
}

