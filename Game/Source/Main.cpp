#include <iostream>
#include <SDL.h>
#include <cstdlib>

//#include "../../Engine/Source/Test.h"
// "../" puts us into a previous folder (so once to get to game, and once to get to Solution
//had to change to "not using precompiled header" to make the second include work
//but now that we've done and include directory, we can just do
#include "Test.h"



void drawRandom(SDL_Renderer* renderer);
void drawShape(SDL_Renderer* renderer);



int main(int argc, char* argv[])
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// create window
	// returns pointer to window if successful or nullptr if failed
	SDL_Window* window = SDL_CreateWindow("Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	while (true)
	{
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		drawRandom(renderer);
		drawShape(renderer);

		// draw line
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//SDL_RenderDrawLine(renderer, 0, 0, 800, 600);

		// show screen
		SDL_RenderPresent(renderer);
	}

	return 0;
}


void drawRandom(SDL_Renderer* renderer)
{
	//int value = rand() % 1000;

	for (int i = 0; i < 50; i++)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color

		int p1_x = rand() % 800;
		int p1_y = rand() % 600;
		int p2_x = rand() % 800;
		int p2_y = rand() % 600;
		SDL_RenderDrawPoint(renderer, p1_x, p1_y);
		SDL_RenderDrawPoint(renderer, p2_x, p2_y);
		SDL_RenderDrawLine(renderer, p1_x, p1_y, p2_x, p2_y);
	}


	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color

	//int p1_x = rand() % 800;
	//int p1_y = rand() % 600;
	//int p2_x = rand() % 800;
	//int p2_y = rand() % 600;
	//SDL_RenderDrawPoint(renderer, p1_x, p1_y);
	//SDL_RenderDrawPoint(renderer, p2_x, p2_y);
	//SDL_RenderDrawLine(renderer, p1_x, p1_y, p2_x, p2_y);
}

void drawShape(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color

	SDL_RenderDrawPoint(renderer, 400, 300);
	SDL_RenderDrawPoint(renderer, 300, 400);
	SDL_RenderDrawPoint(renderer, 500, 550);

	SDL_RenderDrawLine(renderer, 400, 300, 300, 400);
	SDL_RenderDrawLine(renderer, 400, 300, 500, 550);
	SDL_RenderDrawLine(renderer, 300, 400, 500, 550);
}


//Dynamic Linked Library (done at runtime) .dll
//Static Linked Library (done at compile time) .lib
//Objects (the compiled object code) .obj
//Executable (what you run) .exe
//Headers (declares things in a class) .h
//CPP (not sure what it stands for) (defines things in a class) .cpp
