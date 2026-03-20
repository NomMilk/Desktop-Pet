#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "text_bubble.h"

SDL_Texture* bubble_texture = NULL;
SDL_Surface* text_texture_surface = NULL;
SDL_Texture* text_texture = NULL;
TTF_Font* font = NULL;
SDL_Color text_color = {0, 0, 0, 0};

SDL_Rect bubble;

char input_text[] = "Hello fishe! i'm talkin n shi";
int bubble_width = 300;
int bubble_height = 180;
int font_size = 20;

int border = 5;
int padding = 20;
int text_padding = 20;

void Text_Start()
{
	if (TTF_Init() == -1)
	{
		printf("TTF_Init failed: %s\n", TTF_GetError());
		return;
	}

	font = TTF_OpenFont("./Minecraft.ttf", font_size);
	if (!font)
	{
		printf("Failed to load font: %s\n", TTF_GetError());
	}
}

void Text_Update(SDL_Renderer* _renderer)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	bubble.x = bubble.y = padding;
	bubble.w = bubble_width;
	bubble.h = bubble_height;
	SDL_RenderFillRect(_renderer, &bubble);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	bubble.x = bubble.y = padding + border;
	bubble.w = bubble_width - (border * 2);
	bubble.h = bubble_height - (border * 2);
	SDL_RenderFillRect(_renderer, &bubble);

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	text_texture_surface = TTF_RenderText_Solid(font, input_text, text_color);
	text_texture = SDL_CreateTextureFromSurface(_renderer, text_texture_surface);
	SDL_FreeSurface(text_texture_surface);

	bubble.x = padding + border + text_padding;
	bubble.y = bubble.h * 0.5f;
	bubble.w = (bubble_width - (border * 2)) * 0.9f;
	bubble.h = (bubble_height - (border * 2)) * 0.2f;

	SDL_RenderCopy(_renderer, text_texture, NULL, &bubble);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

