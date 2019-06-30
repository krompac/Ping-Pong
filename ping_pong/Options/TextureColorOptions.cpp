#include "Options.h"
#include "ChangeTextureColor.h"

TextureColorOptions::TextureColorOptions() {}

TextureColorOptions::TextureColorOptions(SDL_Texture ** texture, std::string option_label_string, int options_y_position, Colors start_color) 
	: Options(option_label_string, options_y_position)
{
	this->texture_to_change = texture;

	active_color = start_color;
}

TextureColorOptions::~TextureColorOptions()
{
}

bool TextureColorOptions::Update_Options(SDL_Renderer ** renderer, int change_index)
{
	int enum_index = active_color + change_index;

	if (enum_index >= Blue && enum_index <= Magenta)
	{
		active_color = (Colors)enum_index;

		Change_Texture_Color(texture_to_change, active_color);
		Change_Texture_Color(&option_text, active_color);

		return true;
	}

	return false;
}

std::string TextureColorOptions::Get_Option()
{
	return "BALL";
}

void TextureColorOptions::Init_Textures(SDL_Renderer ** renderer, TTF_Font * font)
{
	Options::Init_Textures(renderer, font);
	Change_Texture_Color(texture_to_change, active_color);
	Change_Texture_Color(&option_text, active_color);
}
