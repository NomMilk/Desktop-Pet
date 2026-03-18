#include <iostream>
#include <SDL2/SDL.h>

#include "text_bubble.h"

SDL_Surface* bubble_texture_surface = NULL;
SDL_Texture* bubble_texture = NULL;

SDL_Rect bubble;

int bubble_width = 300;
int bubble_height = 180;

int border = 5;

void Text_Start(SDL_Renderer* _renderer)
{
}

void Text_Update(SDL_Renderer* _renderer, float _deltaTime)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	bubble.x = bubble.y = 20;
	bubble.w = bubble_width;
	bubble.h = bubble_height;
	SDL_RenderFillRect(_renderer, &bubble);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	bubble.x = bubble.y = 20 + border;
	bubble.w = bubble_width - (border * 2);
	bubble.h = bubble_height - (border * 2);
	SDL_RenderFillRect(_renderer, &bubble);
}

