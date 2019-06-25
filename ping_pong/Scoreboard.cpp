#include "Scoreboard.h"

Scoreboard::Scoreboard() {}

Scoreboard::Scoreboard(Menu &menu) : Window(menu)
{
	this->surface = nullptr;
	title = UI_Element();
	title.rect = { 220, 25, 300, 100 };
	title.text = "SCOREBOARD";

	color = { 255, 255, 255 };
}

Scoreboard::~Scoreboard(){}

bool Scoreboard::Window_Action(SDL_Renderer **renderer, bool is_message)
{
	bool stayInWindow = true;

	while (SDL_PollEvent(&event_handler))
	{
		if (event_handler.key.keysym.sym == SDLK_ESCAPE || event_handler.type == SDL_QUIT)
		{
			stayInWindow = false;
			break;
		}
		else
		{
			break;
		}
	}

	return stayInWindow;
}

void Scoreboard::Render(SDL_Renderer **renderer)
{
	Window::Render(renderer);

	title.Render(renderer);
	
	for (auto &item : score_entrys)
	{
		item.Render(renderer);
	}

	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderPresent(*renderer);
}

void Scoreboard::Init_Texture(SDL_Renderer **renderer, TTF_Font *font)
{
	title.Set_Texture(renderer, font, this->surface, color);

	for (auto &item : score_entrys)
	{
		item.Init_Textures(renderer, font, this->surface, color);
	}
}

void Scoreboard::Free_Data()
{
	SDL_DestroyTexture(title.texture);
	
	for (auto &item : score_entrys)
	{
		item.Free_Data();
	}
}

void Scoreboard::Add_Score_Entry(Score_Entry entry)
{
	Score_Row score = Score_Row(entry);

	score_entrys.push_back(score);

	if (score_entrys.size() > 3)
	{
		score_entrys.erase(score_entrys.begin());
	}

	int entrys_size = score_entrys.size();

	for (int i = entrys_size - 1; i >= 0; i--)
	{
		score_entrys[entrys_size - 1 - i].UpdatePosition(i);
	}
}
