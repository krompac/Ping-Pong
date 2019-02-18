#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

	lijevi_pad = { 20, 20, 20, 100 };
	desni_pad = { 720, 20, 20, 100 };
	loptica = { 340, 220, 20, 20 };
	game_window = { 20, 20, 720, 480 };
	start_game = { 800, 20, 150, 70 };
	scoreboard = { 800, 110, 150, 70 };
	options = { 800, 200, 150, 70 };
	quit = { 800, 290, 150, 70 };
	prvi_broj = { 310, 520, 50, 70 };
	//pom = {0,0, 92, 128};
	// 120, 230, 340
	pom = { 345, 0, 92, 128 };

	desno = gore = true;
	pause = false;
	pad_collision_surface = desni_pad.h / 2;
	koeficijent = (pad_collision_surface / 20) + 0.5;


	boja = { 202, 206, 173 };

	frame_time = 0;
	speed_x = 5;
	speed_y = 0;

	init();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(prozor);
	//TTF_Quit();
}

void Game::DrawCircle(SDL_Renderer *Renderer, int _x, int _y, int radius)
{
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int err = tx - (radius << 1); // shifting bits left by 1 effectively
								  // doubles the value. == tx - diameter
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
		SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
		SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
		SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
		SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
		SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
		SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
		SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}

void Game::free()
{
	// if (start_game_textura != NULL)
	// {
	// 	SDL_DestroyTexture(start_game_textura);
	// 	start_game_textura = NULL;
	// }

	// if (povrsina != NULL)
	// {
	// 	SDL_FreeSurface(povrsina);
	// 	povrsina = NULL;
	// }
}

void Game::render()
{
	//	free();
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);

	SDL_RenderFillRect(renderer, &lijevi_pad);
	SDL_RenderFillRect(renderer, &desni_pad);
	SDL_RenderFillRect(renderer, &loptica);

	SDL_SetRenderDrawColor(renderer, 0xCA, 0xCE, 0xAD, 0xff);
	SDL_RenderDrawRect(renderer, &game_window);
	//	DrawCircle(renderer, loptica.x, loptica.y, loptica.r);

	//	povrsina = TTF_RenderText_Solid(font, "Start game", boja);
	//	
	//	SDL_RenderCopy(renderer, start_game_textura, NULL, &start_game);
	SDL_RenderCopy(renderer, start_game_textura, NULL, &start_game);
	SDL_RenderCopy(renderer, scoreboard_textura, NULL, &scoreboard);
	SDL_RenderCopy(renderer, options_textura, NULL, &options);
	SDL_RenderCopy(renderer, quit_textura, NULL, &quit);

	SDL_RenderDrawRect(renderer, &prvi_broj);
	SDL_RenderCopy(renderer, left_score, &pom, &prvi_broj);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderPresent(renderer);
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

				if (loptica.x + loptica.w >= game_window.w + game_window.x)
				{
					desno = false;
					speed_y = 0;
					speed_x = 5;
					loptica.x = game_window.w;
				}

				if ((loptica.x + loptica.w >= desni_pad.x) && y > desni_pad.y && y < (desni_pad.y + desni_pad.h))
				{
					desno = false;
					z_desni_pad = desni_pad.y + (desni_pad.h / 2);
					speed_y = abs(z_desni_pad - y) / koeficijent;
					speed_x = 6 - (speed_y / 5);
					gore = (z_desni_pad < y);
				}
			}
			else
			{
				loptica.x -= speed_x;

				if (loptica.x <= game_window.x)
				{
					desno = true;
					speed_y = 0;
					speed_x = 5;
					loptica.x = game_window.x;
					pom.x += 110;
				}

				if ((loptica.x <= (lijevi_pad.x + lijevi_pad.w)) && loptica.y > lijevi_pad.y && loptica.y < (lijevi_pad.y + lijevi_pad.h))
				{
					desno = true;
					z_lijevi_pad = lijevi_pad.y + (lijevi_pad.h / 2);
					speed_y = abs(z_lijevi_pad - y) / koeficijent;
					speed_x = 6 - (speed_y / 5);
					gore = (z_lijevi_pad < y);
				}
			}

			if (gore)
			{
				loptica.y += speed_y;

				if (loptica.y + loptica.h >= game_window.h + game_window.y)
				{
					gore = false;
					loptica.y = game_window.h;
				}
			}
			else
			{
				loptica.y -= speed_y;

				if (loptica.y <= game_window.y)
				{
					gore = true;
					loptica.y = game_window.y;
				}
			}
		}
	}
	return true;
}

bool Game::main_loop()
{
	SDL_Event dogadjaj;

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

			switch (dogadjaj.key.keysym.sym)
				case SDLK_ESCAPE:
					pause = !pause;
					break;

					kretnja_loptice();
					render();

					return true;
		}
	}

	kretnja_loptice();
	render();
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
			cout << "Greška kod pravljenja prozora i/ili renderera!\nError: " << SDL_GetError() << endl;
		}

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
		povrsina = IMG_Load("images/start_game.png");
		start_game_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = IMG_Load("images/scoreboard.png");
		scoreboard_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = IMG_Load("images/options.png");
		options_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = IMG_Load("images/quit.png");
		quit_textura = SDL_CreateTextureFromSurface(renderer, povrsina);
		povrsina = IMG_Load("images/numbers.png");
		left_score = SDL_CreateTextureFromSurface(renderer, povrsina);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
		render();

		while (main_loop());
	}
}