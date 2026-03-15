#include <iostream>
#include <SDL2/SDL.h>

#include "virtual_pet.h"

SDL_Surface* pet_texture_surface = NULL;
SDL_Texture* pet_texture = NULL;

SDL_Rect dst;

void Pet_Start(SDL_Renderer* _renderer)
{
	pet_texture_surface = SDL_LoadBMP("cone.bmp");
	if(pet_texture_surface == NULL)
	{
		std::cout << "Error initalizing image: " << SDL_GetError() << '\n';
		return;
	}
	pet_texture = SDL_CreateTextureFromSurface(_renderer, pet_texture_surface);
	SDL_FreeSurface(pet_texture_surface);
}

void Pet_Update(SDL_Renderer* _renderer)
{

	dst.x = 100;
	dst.y = 100;
	dst.w = 100;
	dst.h = 100;

	SDL_RenderCopy(_renderer, pet_texture, NULL, &dst);
}
