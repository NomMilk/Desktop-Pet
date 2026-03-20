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

char* nouns = "{nouns}";
char* intensifiers = "{intensifiers}";
char* adjectives = "{adjectives}";

int bubble_width = 350;
int bubble_height = 130;
int font_size = 60;

int border = 5;
int padding = 20;
int text_padding = 20;

void generate_random_sentence()
{
    FILE* nouns_file = fopen("wordlist/nouns", "r");
    if (nouns_file == NULL) {
        perror("Failed to open file");
    }
    fclose(nouns_file);

    FILE* intensifiers_file = fopen("wordlist/intensifiers", "r");
    if (intensifiers_file == NULL) {
        perror("Failed to open file");
    }
    fclose(intensifiers_file);


    FILE* adjectives_file = fopen("wordlist/adjectives", "r");
    if (adjectives_file == NULL) {
        perror("Failed to open file");
    }
    fclose(adjectives_file);
}

void Text_Start()
{
	generate_random_sentence();
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

	//build sentence	
	char sentence[100];
	snprintf(sentence, sizeof(sentence), "%ss are %s %s!", nouns, intensifiers, adjectives);

	text_texture_surface = TTF_RenderText_Solid(font, sentence, text_color);
	text_texture = SDL_CreateTextureFromSurface(_renderer, text_texture_surface);
	SDL_FreeSurface(text_texture_surface);

	bubble.x = padding + border + text_padding;
	bubble.y = bubble.h * 0.5f;
	bubble.w = (bubble_width - (border * 2)) * 0.9f;
	bubble.h = (bubble_height - (border * 2)) * 0.2f;

	SDL_RenderCopy(_renderer, text_texture, NULL, &bubble);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

