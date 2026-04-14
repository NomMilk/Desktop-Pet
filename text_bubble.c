#include <stdio.h>
#include <time.h>
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
#define MAX_TEXT_LENGTH 1000
#define MAX_WORD_LENGTH 100

char* nouns = "{nouns}";
char nounContent[MAX_TEXT_LENGTH];

char* intensifiers = "{intensifiers}";
char intenseContent[MAX_TEXT_LENGTH];

char* adjectives = "{adjectives}";
char adjContent[MAX_TEXT_LENGTH];

int bubble_width = 350;
int bubble_height = 130;
int font_size = 60;

int border = 5;
int padding = 20;
int text_padding = 20;

void generate_random_sentence()
{
	{
		FILE* nouns_file = fopen("wordlist/nouns", "r");
		if (nouns_file == NULL) {
			printf("Can't Load Nouns");
		}

		fgets(nounContent, MAX_TEXT_LENGTH, nouns_file);

		fclose(nouns_file);

		srand(time(NULL));

		int randomIndex = 0;
		randomIndex = rand() % MAX_WORD_LENGTH - 1;
		nouns = &nounContent[randomIndex];

		int start = 0;
		int end = 0;
		while(randomIndex > 0)
		{
			if(nounContent[start] == ' ') 
			{
				randomIndex--;
			}
			start++;
		}

		end = start;

		while(nounContent[end] != ' ')
		{
			end++;
		}

		strncpy(nouns, &nounContent[start], end - start);
		nouns[end - start] = '\0';
	}

	{
		FILE* intensifiers_file = fopen("wordlist/intensifiers", "r");
		if (intensifiers_file == NULL) {
			printf("Can't Load Intense");
		}
		
		fgets(intenseContent, MAX_TEXT_LENGTH, intensifiers_file);

		fclose(intensifiers_file);

		srand(time(NULL));

		int randomIndex = 0;
		randomIndex = rand() % MAX_WORD_LENGTH - 1;
		intensifiers = &intenseContent[randomIndex];

		int start = 0;
		int end = 0;
		while(randomIndex > 0)
		{
			if(intenseContent[start] == ' ') 
			{
				randomIndex--;
			}
			start++;
		}

		end = start;

		while(intenseContent[end] != ' ')
		{
			end++;
		}

		strncpy(intensifiers, &intenseContent[start], end - start);
		intensifiers[end - start] = '\0';
	}



	{
		FILE* adjectives_file = fopen("wordlist/adjectives", "r");
		if (adjectives_file == NULL) {
			printf("Can't Load Adje");
		}

		fgets(adjContent, MAX_TEXT_LENGTH, adjectives_file);

		fclose(adjectives_file);

		srand(time(NULL));

		int randomIndex = 0;
		randomIndex = rand() % MAX_WORD_LENGTH - 1;
		adjectives = &adjContent[randomIndex];

		int start = 0;
		int end = 0;
		while(randomIndex > 0)
		{
			if(adjContent[start] == ' ') 
			{
				randomIndex--;
			}
			start++;
		}

		end = start;

		while(adjContent[end] != ' ')
		{
			end++;
		}

		strncpy(adjectives, &adjContent[start], end - start);
		adjectives[end - start] = '\0';

	}
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

