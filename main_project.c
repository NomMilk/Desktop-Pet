#include <SDL2/SDL.h>
#include <iostream>
#include <time.h>

#include "virtual_pet.h"
#include "text_bubble.h"

#define WIDTH 400
#define HEIGHT 400

#define CLOCKS_PER_SECONDS 50000

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	//Setup
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error initalizing SDL: " << SDL_GetError() << '\n';
		return 1;
	}
	
	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
	window = SDL_CreateWindow
	(
		"Pet",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP
	);

	if(!window)
	{
		std::cout << "Error Creating Window: " << SDL_GetError() << '\n';
		return 1;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		std::cout << "Error Getting Renderer: " << SDL_GetError() << '\n';
		return 1;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//DesktopPet
	bool isRunning = true;
	SDL_Event event;
	Pet_Start(renderer);
	Text_Start(renderer);

	double deltaTime = 0;
	clock_t currentTime = clock();
	clock_t previousTime = clock();

	while(isRunning)
	{
		currentTime = clock();
		deltaTime = (double)(currentTime - previousTime)/CLOCKS_PER_SECONDS;
		previousTime = currentTime;

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isRunning = false;
			}	
		}

		SDL_RenderClear(renderer);

		//Game Logic
		Pet_Update(renderer, deltaTime);
		Text_Update(renderer, deltaTime);

		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
