#include <iostream>
#include <SDL2/SDL.h>

#include "virtual_pet.h"

SDL_Surface* pet_texture_surface = NULL;
SDL_Texture* pet_texture = NULL;

SDL_Rect dst;

int PET_SIZE = 200;
int newTarget = 40;
float currentTime = 0;

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

void Pet_Update(SDL_Renderer* _renderer, float _deltaTime)
{
	
	if(currentTime < newTarget)
	{
		newTarget = 40;
		currentTime += 2 * _deltaTime;
	}
	else
	{
		newTarget = 0;
		currentTime -= 2 * _deltaTime;
	}

	dst.x = PET_SIZE;
	dst.y = PET_SIZE + currentTime;
	dst.w = PET_SIZE;
	dst.h = PET_SIZE - currentTime;

	SDL_RenderCopy(_renderer, pet_texture, NULL, &dst);
}
