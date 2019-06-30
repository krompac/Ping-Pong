#include "Window.h"

Window::Window(){}

Window::Window(Menu &menu)
{
	this->menu = &menu;
	render_window = { 20, 20, 720, 560 };
}

void Window::Render(SDL_Renderer **renderer)
{
	SDL_RenderClear(*renderer);
	SDL_SetRenderDrawColor(*renderer, 0xCA, 0xCE, 0xAD, 0xff);

	SDL_RenderDrawRect(*renderer, &render_window);
	this->menu->Render_Menu(*renderer);
}
