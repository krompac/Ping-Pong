#include "Options.h"
#include "ChangeTextureColor.h"

PadColorOptions::PadColorOptions() {}

PadColorOptions::PadColorOptions(std::string option_label_string, int options_y_position, Colors &start_color, bool left_pad)
	: Options(option_label_string, options_y_position, 60)
{
	this->active_color = &start_color;

	if (left_pad)
	{
		this->pad_text = " Left pad ";
	}
	else
	{
		this->pad_text = " Right pad ";
	}
}

PadColorOptions::~PadColorOptions()
{
}

bool PadColorOptions::Update_Options(SDL_Renderer ** renderer, int change_index)
{
	int enum_index = *active_color + change_index;

	if (enum_index >= Blue && enum_index <= Magenta)
	{
		*active_color = (Colors)enum_index;
		Change_Texture_Color(&option_text, *active_color);

		return true;
	}

	return false;
}

std::string PadColorOptions::Get_Option()
{
	return pad_text;
}

void PadColorOptions::Init_Textures(SDL_Renderer ** renderer, TTF_Font * font)
{
	Options::Init_Textures(renderer, font);
	Change_Texture_Color(&option_text, *active_color);
}