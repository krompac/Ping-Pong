#include "Scoreboard.h"

UI_Element::UI_Element() {}

UI_Element::UI_Element(int x, int y, int w, int h)
{
	rect = { x, y, w, h };
	texture = nullptr;
}

void UI_Element::Render(SDL_Renderer ** renderer, bool draw_rect)
{
	if (draw_rect)
	{
		SDL_RenderDrawRect(*renderer, &rect);
	}

	SDL_RenderCopy(*renderer, this->texture, NULL, &rect);
}

Scoreboard::Scoreboard() {}

Scoreboard::Scoreboard(Menu &menu) : Window(menu)
{
	this->surface = nullptr;
	title = UI_Element(220, 25, 300, 100);
	title_text = "SCOREBOARD";

	player1_entry = UI_Element(25, 130, 100, 50);
	player1_score = UI_Element(130, 130, 50, 50);
	colon = UI_Element(185, 130, 50, 50);
	player2_entry = UI_Element(240, 130, 100, 50);
	player2_score = UI_Element(345, 130, 50, 50);

	color = { 255, 255, 255 };
}

Scoreboard::~Scoreboard(){}

bool Scoreboard::Window_Action(SDL_Renderer **renderer, bool is_message)
{
	while (SDL_PollEvent(&event_handler))
	{
		if (event_handler.key.keysym.sym == SDLK_ESCAPE || event_handler.type == SDL_QUIT)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return true;
}

void Scoreboard::Render(SDL_Renderer **renderer)
{
	Window::Render(renderer);

	title.Render(renderer);
	player1_entry.Render(renderer, true);
	player1_score.Render(renderer, true);
	colon.Render(renderer, true);
	player2_entry.Render(renderer, true);
	player2_score.Render(renderer, true);

	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderPresent(*renderer);
}

void Scoreboard::Set_Texture(SDL_Texture ** texture, SDL_Renderer ** renderer, std::string text, TTF_Font * font)
{
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	*texture = SDL_CreateTextureFromSurface(*renderer, surface);
}

void Scoreboard::Init_Texture(SDL_Renderer **renderer, TTF_Font *font)
{
	Set_Texture(&title.texture, renderer, title_text, font);

	Set_Texture(&player1_entry.texture, renderer, score_entrys[0].player1_name, font);
	Set_Texture(&player1_score.texture, renderer, std::to_string(score_entrys[0].player1_score), font);
	Set_Texture(&player2_entry.texture, renderer, score_entrys[0].player2_name, font);
	Set_Texture(&player2_score.texture, renderer, std::to_string(score_entrys[0].player2_score), font);

	Set_Texture(&colon.texture, renderer, ":", font);
}

void Scoreboard::Free_Data()
{
	SDL_DestroyTexture(title.texture);
	SDL_DestroyTexture(player1_entry.texture);
	SDL_DestroyTexture(player2_entry.texture);
	SDL_DestroyTexture(player1_score.texture);
	SDL_DestroyTexture(player2_score.texture);
	SDL_DestroyTexture(colon.texture);
}

void Scoreboard::Add_Score_Entry(Score_Entry entry)
{
	score_entrys.push_back(entry);
}
