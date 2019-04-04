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
	this->prozor = nullptr;
	this->renderer = nullptr;
	this->povrsina = nullptr;
	this->left_score = nullptr;
	this->right_score = nullptr;
	this->dvotocka_textura = nullptr;
	this->message_textura = nullptr;
	this->answers_textura[0] = nullptr;
	this->answers_textura[1] = nullptr;
	this->loptica_slika = nullptr;

	game_window = { 20, 20, 720, 480 };
	settings_window = { 20, 20, 720, 560 };
	prvi_broj = { 310, 520, 60, 70 };
	drugi_broj = { 410, 520, 60, 70 };
	dvotocka = { 375, 520, 30, 70 };
	
	message_box = { 180, 190, 400, 150 };
	message = { message_box.x + 10, message_box.y + 10, 380, 60 };
	answers[0] = { 250, 280, 100, 50 };
	answers[1] = { 430, 280, 100, 50 };

	menuitems = new SDL_Rect[4];

	menu = Menu(menuitems);

	initialize_game_components();
	pad_collision_surface = desni_pad.h / 2;
	koeficijent = pad_collision_surface / 10; //+ 0.5;

	boja = { 255, 255, 255 };

	init();
}

Game::~Game()
{
	delete menuitems;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(prozor);
	TTF_Quit();
}

void Game::initialize_game_components()
{
	starting_ball_speed = 5;
	frame_time = 0;
	speed_x = starting_ball_speed;
	speed_y = 0;

	lijevi_pad = { 20, 20, 20, 100 };
	desni_pad = { 720, 20, 20, 100 };
	loptica = { 370, 250, 20, 20 };

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

	menu.render_menu(renderer);

	SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(renderer, &game_window);
	

	if (pause)
	{
		SDL_RenderDrawRect(renderer, &menuitems[menu_position]);
	}

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

void Game::render_settings_window()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawRect(renderer, &settings_window);
	menu.render_menu(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(renderer);
}

void Game::initialize_message(string message)
{
	povrsina = TTF_RenderText_Solid(font, message.c_str(), boja);
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
		int y = loptica.y + loptica.h / 2;

		if (frame_time + 1000 / 60 < SDL_GetTicks())
		{
			frame_time = SDL_GetTicks();
			if (desno)
			{
				loptica.x += speed_x;
				set_origin();

				if (ball_origin.x + loptica.w / 2 >= game_window.w + game_window.x)
				{
					loptica.x = game_window.x + game_window.w - loptica.w;
					set_origin();
					desno = false;
					lijevi_rezultat++;
					render_score(&left_score, lijevi_rezultat);
				}

				if (check_corner() || ((ball_origin.x + loptica.w / 2 >= desni_pad.x) && (ball_origin.y - loptica.h / 2) >= desni_pad.y && ball_origin.y + loptica.h / 2  <= (desni_pad.y + desni_pad.h)))
				//if ((ball_origin.x + loptica.w / 2 >= desni_pad.x) && (ball_origin.y - loptica.h / 2) >= desni_pad.y && ball_origin.y + loptica.h / 2 <= (desni_pad.y + desni_pad.h))
				{
					desno = false;
					z_desni_pad = desni_pad.y + (desni_pad.h / 2);
					speed_y = abs(z_desni_pad - ball_origin.y) / koeficijent;
					speed_x = starting_ball_speed + 1 - (speed_y / starting_ball_speed);
					gore = (z_desni_pad < y);
					starting_ball_speed += 0.2;
				}
			}
			else
			{
				loptica.x -= speed_x;
				set_origin();

				if (loptica.x <= game_window.x)
				{
					loptica.x = game_window.x;
					set_origin();
					desno = true;
					desni_rezultat++;
					render_score(&right_score, desni_rezultat);
				}

				if (check_corner() || ((ball_origin.x - loptica.w / 2 <= lijevi_pad.x + lijevi_pad.w) && (ball_origin.y - loptica.h / 2) >= lijevi_pad.y && ball_origin.y + loptica.h / 2 <= (lijevi_pad.y + lijevi_pad.h)))
				{
					desno = true;
					z_lijevi_pad = lijevi_pad.y + (lijevi_pad.h / 2);
					speed_y = abs(z_lijevi_pad - y) / koeficijent;
					speed_x = starting_ball_speed + 1 - (speed_y / starting_ball_speed);
					gore = (z_lijevi_pad < y);
					starting_ball_speed += 0.2;
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

bool Game::track_rightpad()
{
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (!pause)
	{
		if (keyboard_state_array[SDL_SCANCODE_UP])
		{
			if (desni_pad.y - 1 >= game_window.y)
				desni_pad.y -= 1;
		}
		else if (keyboard_state_array[SDL_SCANCODE_DOWN])
		{
			if (desni_pad.y + 1 + desni_pad.h <= game_window.h + game_window.y)
				desni_pad.y += 1;
		}
	}
	return true;
}

bool Game::main_loop()
{
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (!pause)
	{
		if (keyboard_state_array[SDL_SCANCODE_W])
		{
			if (lijevi_pad.y - 1 >= game_window.y)
				lijevi_pad.y -= 1;
		}
		else if (keyboard_state_array[SDL_SCANCODE_S])
		{
			if (lijevi_pad.y + 1 + lijevi_pad.h <= game_window.h + game_window.y)
				lijevi_pad.y += 1;
		}
	}

	while (SDL_PollEvent(&dogadjaj))
	{
		if (dogadjaj.type == SDL_QUIT)
			return false;
		else if (dogadjaj.type == SDL_KEYDOWN)
		{
			if (pause)
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
						message_position = 0;
						initialize_message("Would you like to start again?");
						while (message_box_action());
					}
					else if (menu_position == 2)
					{
						render_settings_window();
						SDL_Delay(10000);
					}
					else if (menu_position == 3)
					{
						message_position = 1;
						initialize_message("Are you sure you want to guit the game?");
						while (message_box_action());

						//vraca message_position jer je pozicija Yes odgovora na 0.-oj poziciji (false), a No je 1.-oj poziciji (true)
						return message_position;
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

bool Game::check_corner()
{
	int x_coord = - ball_origin.x;
	int y_coord = - ball_origin.y;

	x_coord += (desno) ? desni_pad.x : lijevi_pad.x + lijevi_pad.w;
	y_coord += (desno) ? desni_pad.y : lijevi_pad.y;
	
	return ((pow((x_coord), 2) + pow((y_coord), 2)) <= pow(loptica.w / 2, 2)) || ((pow((x_coord), 2) + pow((y_coord + desni_pad.h), 2)) <= pow(loptica.w / 2, 2));
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

		menu.init(povrsina, font, boja, renderer);
		povrsina = TTF_RenderText_Solid(font, ":", boja);
		dvotocka_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		render_score(&left_score, 0);
		render_score(&right_score, 0);

		povrsina = IMG_Load("images/circle.png");
		loptica_slika = SDL_CreateTextureFromSurface(renderer, povrsina);
		SDL_SetTextureColorMod(loptica_slika, 0xff, 0x00, 0x00);
		
		render_game_window();

		while (main_loop() && track_rightpad());
	}
}

