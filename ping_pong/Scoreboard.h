#pragma once
#include <vector>
#include "Window.h"

class UI_Element
{
	public:
		UI_Element();
		
		void Render(SDL_Renderer **renderer, bool draw_rect = false);
		void Set_Texture(SDL_Renderer **renderer, TTF_Font *font, SDL_Surface *surface, SDL_Color &color);
		void Free_Data();

		SDL_Rect rect;
		SDL_Texture *texture;
		std::string text;
};

struct Score_Entry
{
	char player1_name[10];
	int player1_score;

	char player2_name[10];
	int player2_score;
};

class Score_Row
{
	public:
		Score_Row();
		Score_Row(Score_Entry entry);

		void Init_Textures(SDL_Renderer **renderer, TTF_Font *font, SDL_Surface *surface, SDL_Color &color);
		void Render(SDL_Renderer **renderer);
		void Free_Data();
		void UpdatePosition(int index);

	private:
		UI_Element player1_name;
		UI_Element player1_score;
		UI_Element colon;
		UI_Element player2_name;
		UI_Element player2_score;
};

class Scoreboard : public Window
{
	public:
		Scoreboard();
		Scoreboard(Menu &menu);
		~Scoreboard();

		bool Window_Action(SDL_Renderer **renderer, bool is_message = false);
		void Render(SDL_Renderer **renderer);
		void Init_Texture(SDL_Renderer **renderer, TTF_Font *font);
		void Free_Data();
		void Add_Score_Entry(Score_Entry entry, bool write_to_file = false);
		void Init_Data();

	private:
		SDL_Surface *surface;
		SDL_Color color;
		UI_Element title;

		Score_Entry entry_to_read;

		std::vector<Score_Row> score_entrys;

		std::string title_text;

		void Update_Entrys();
};
