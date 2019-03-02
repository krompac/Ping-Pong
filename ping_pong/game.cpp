#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "game.h"

using namespace std;

Game::Game()
{
	this->prozor = nullptr;
	this->renderer = nullptr;
	this->start_game_textura = nullptr;
	this->scoreboard_textura = nullptr;
	this->options_textura = nullptr;
	this->quit_textura = nullptr;
	this->povrsina = nullptr;
	this->left_score = nullptr;
	this->right_score = nullptr;
	this->dvotocka_textura = nullptr;
	this->message_textura = nullptr;
	this->answers_textura[0] = nullptr;
	this->answers_textura[1] = nullptr;
	this->loptica_slika = nullptr;

	game_window = { 20, 20, 720, 480 };
	options_window = { 20, 20, 720, 560 };
	start_game = { 800, 20, 150, 70 };
	scoreboard = { 800, 110, 150, 70 };
	options = { 800, 200, 150, 70 };
	quit = { 800, 290, 150, 70 };
	prvi_broj = { 310, 520, 50, 70 };
	drugi_broj = { 410, 520, 50, 70 };
	dvotocka = { 360, 520, 50, 70 };
	
	message_box = { 180, 190, 400, 150 };
	message = { message_box.x + 10, message_box.y + 10, 380, 60 };
	answers[0] = { 250, 280, 100, 50 };
	answers[1] = { 430, 280, 100, 50 };

	menuitems[0] = start_game;
	menuitems[1] = scoreboard;
	menuitems[2] = options;
	menuitems[3] = quit;

	starting_ball_speed = 5;
	initialize_game_components();
	pad_collision_surface = desni_pad.h / 2;
	koeficijent = pad_collision_surface / 10; //+ 0.5;

	boja = { 255, 255, 255 };

	init();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(prozor);
	TTF_Quit();
}

void Game::initialize_game_components()
{
	frame_time = 0;
	speed_x = starting_ball_speed;
	speed_y = 0;

	lijevi_pad = { 20, 20, 20, 100 };
	desni_pad = { 720, 20, 20, 100 };
	loptica = { 370, 250, 20, 20 };

	menu_position = message_position = 0;
	
	lijevi_rezultat = 0;
	desni_rezultat = 0;
	broj = to_string(lijevi_rezultat);

	desno = gore = true;
	pause = false;
}

void Game::free_score(SDL_Texture *score)
{
	if (score != nullptr)
	{
		SDL_DestroyTexture(score);
		score = nullptr;
	}

	if (povrsina != nullptr)
	{
		SDL_FreeSurface(povrsina);
		povrsina = nullptr;
	}
}

void Game::free()
{
}

void Game::render_score(SDL_Texture **score, int number)
{
	free_score(*score);
	broj = to_string(number);
	povrsina = TTF_RenderText_Solid(font, broj.c_str(), boja);
	*score = SDL_CreateTextureFromSurface(renderer, povrsina);
}

void Game::render_game_window(bool is_message)
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);

	SDL_RenderFillRect(renderer, &lijevi_pad);
	SDL_RenderFillRect(renderer, &desni_pad);

	SDL_RenderDrawRect(renderer, &prvi_broj);
	SDL_RenderDrawRect(renderer, &drugi_broj);
	SDL_RenderDrawRect(renderer, &dvotocka);

	SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(renderer, &game_window);
	

	if (pause)
	{
		SDL_RenderDrawRect(renderer, &menuitems[menu_position]);
	}

	SDL_RenderCopy(renderer, start_game_textura, NULL, &start_game);
	SDL_RenderCopy(renderer, scoreboard_textura, NULL, &scoreboard);
	SDL_RenderCopy(renderer, options_textura, NULL, &options);
	SDL_RenderCopy(renderer, quit_textura, NULL, &quit);
	SDL_RenderCopy(renderer, dvotocka_textura, NULL, &dvotocka);
	SDL_RenderCopy(renderer, left_score, NULL, &prvi_broj);
	SDL_RenderCopy(renderer, right_score, NULL, &drugi_broj);
	SDL_RenderCopy(renderer, loptica_slika, NULL, &loptica);

	if (is_message)
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

		SDL_RenderFillRect(renderer, &message_box);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
		SDL_RenderDrawRect(renderer, &message_box);

		SDL_RenderCopy(renderer, message_textura, NULL, &message);

		SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
		SDL_RenderDrawRect(renderer, &answers[message_position]);
		SDL_RenderCopy(renderer, answers_textura[0], NULL, &answers[0]);
		SDL_RenderCopy(renderer, answers_textura[1], NULL, &answers[1]);
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(renderer);
}

void Game::render_options_window()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(renderer, &options_window);
}

void Game::initialize_message()
{
	message_position = 0;
	povrsina = TTF_RenderText_Solid(font, "Would you like to start again?", boja);
	message_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
	povrsina = TTF_RenderText_Solid(font, "Yes", boja);
	answers_textura[0] = SDL_CreateTextureFromSurface(renderer, povrsina);
	povrsina = TTF_RenderText_Solid(font, "No", boja);
	answers_textura[1] = SDL_CreateTextureFromSurface(renderer, povrsina);
}

bool Game::message_box_action()
{
	render_game_window(true);

	while (SDL_PollEvent(&message_dogadjaj))
	{
		if (message_dogadjaj.type == SDL_QUIT)
			this->~Game();
		else if (message_dogadjaj.type == SDL_KEYDOWN)
		{
			switch (message_dogadjaj.key.keysym.sym)
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
					if (!message_position)
					{
						initialize_game_components();
						render_score(&left_score, 0);
						render_score(&right_score, 0);
					}

					pause = false;
					render_game_window();
					SDL_Delay(500);
					return false;
			}
		}

		render_game_window(true);
		SDL_Delay(1);

		return true;
	}

	render_game_window(true);
	SDL_Delay(1);

	return true;
}

void Game::set_origin()
{
	ball_origin = { loptica.x + loptica.w / 2, loptica.y + loptica.h / 2 };
}

bool Game::kretnja_loptice()
{
	if (!pause)
	{
		int y = loptica.y + loptica.h;

		if (frame_time + 1000 / 60 < SDL_GetTicks())
		{
			frame_time = SDL_GetTicks();
			if (desno)
			{
				loptica.x += speed_x;
				set_origin();

				if (ball_origin.x + loptica.w / 2 >= game_window.w + game_window.x)
				{
					desno = false;
					lijevi_rezultat++;
					render_score(&left_score, lijevi_rezultat);
				}

				if ((ball_origin.x + loptica.w / 2 >= desni_pad.x) && (ball_origin.y - loptica.h / 2) >= desni_pad.y && ball_origin.y + loptica.h / 2  <= (desni_pad.y + desni_pad.h))
				{
					desno = false;
					z_desni_pad = desni_pad.y + (desni_pad.h / 2);
					speed_y = abs(z_desni_pad - ball_origin.y) / koeficijent;
					cout << "z desni pad = " << z_desni_pad << endl;
					cout << "ball_origin.y = " << ball_origin.y << endl;
					cout << "speed_y = " << speed_y << endl;
					speed_x = starting_ball_speed + 1 - (speed_y / starting_ball_speed);
					gore = (z_desni_pad < y);
				}
			}
			else
			{
				loptica.x -= speed_x;
				set_origin();

				if (loptica.x <= game_window.x)
				{
					desno = true;
					desni_rezultat++;
					render_score(&right_score, desni_rezultat);
				}

				if ((ball_origin.x - loptica.w / 2 <= lijevi_pad.x + lijevi_pad.w) && (ball_origin.y - loptica.h / 2) >= lijevi_pad.y && ball_origin.y + loptica.h / 2 <= (lijevi_pad.y + lijevi_pad.h))
				{
					desno = true;
					z_lijevi_pad = lijevi_pad.y + (lijevi_pad.h / 2);
					speed_y = abs(z_lijevi_pad - y) / koeficijent;
					speed_x = starting_ball_speed + 1 - (speed_y / starting_ball_speed);
					gore = (z_lijevi_pad < y);
				}
			}

			if (gore)
			{
				loptica.y += speed_y;
				set_origin();

				if (loptica.y + loptica.h >= game_window.h + game_window.y)
				{
					gore = false;
					loptica.y = game_window.h;
					set_origin();
				}
			}
			else
			{
				loptica.y -= speed_y;
				set_origin();

				if (loptica.y <= game_window.y)
				{
					gore = true;
					loptica.y = game_window.y;
					set_origin();
				}
			}
		}
	}
	return true;
}

void Game::menu()
{
	
}

bool Game::main_loop()
{
	while (SDL_PollEvent(&dogadjaj))
	{
		if (dogadjaj.type == SDL_QUIT)
			return false;
		else if (dogadjaj.type == SDL_KEYDOWN)
		{
			if (!pause)
			{
				switch (dogadjaj.key.keysym.sym)
				{
					case SDLK_UP:
						if (desni_pad.y - 10 >= game_window.y)
							desni_pad.y -= 10;
						break;
					case SDLK_DOWN:
						if (desni_pad.y + 10 + desni_pad.h <= game_window.h + game_window.y)
							desni_pad.y += 10;
						break;
					case SDLK_s:
						if (lijevi_pad.y + 10 + lijevi_pad.h <= game_window.h + game_window.y)
							lijevi_pad.y += 10;
						break;
					case SDLK_w:
						if (lijevi_pad.y - 10 >= game_window.y)
							lijevi_pad.y -= 10;
						break;
				}
			}
			else
			{
				if (dogadjaj.key.keysym.sym == SDLK_UP || dogadjaj.key.keysym.sym == SDLK_w)
				{
					if (menu_position > 0)
					{
						menu_position--;
					}
				}
				else if (dogadjaj.key.keysym.sym == SDLK_DOWN || dogadjaj.key.keysym.sym == SDLK_s)
				{
					if (menu_position < 3)
					{
						menu_position++;
					}
				}
				else if (dogadjaj.key.keysym.sym == SDLK_SPACE)
				{
					if (menu_position == 0)
					{
						initialize_message();
						while (message_box_action());
					}
					else if (menu_position == 3)
					{
						return false;
					}
				}
			}

			switch (dogadjaj.key.keysym.sym)
				case SDLK_ESCAPE:
					pause = !pause;
					break;

			kretnja_loptice();
			render_game_window();

			return true;
		}
	}

	kretnja_loptice();
	render_game_window();
	SDL_Delay(1);

	return true;
}

void Game::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL nije mogel inicijalizirati!\nError: " << SDL_GetError() << endl;
	}
	else
	{
		if (SDL_CreateWindowAndRenderer(sirina, visina, SDL_WINDOW_SHOWN, &prozor, &renderer))
		{
			cout << "Gre�ka kod pravljenja prozora i/ili renderera!\nError: " << SDL_GetError() << endl;
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

		povrsina = TTF_RenderText_Solid(font, "Start game", boja);
		start_game_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = TTF_RenderText_Solid(font, "Scoreboard", boja);
		scoreboard_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = TTF_RenderText_Solid(font, "Options", boja);
		options_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = TTF_RenderText_Solid(font, "Quit", boja);
		quit_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = TTF_RenderText_Solid(font, ":", boja);
		dvotocka_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		render_score(&left_score, 0);
		render_score(&right_score, 0);

		povrsina = IMG_Load("images/circle.png");
		loptica_slika = SDL_CreateTextureFromSurface(renderer, povrsina);
		SDL_SetTextureColorMod(loptica_slika, 0x00, 0x00, 0xff);

		render_game_window();

		while (main_loop());
	}
}

