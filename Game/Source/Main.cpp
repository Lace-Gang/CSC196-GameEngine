#include "Renderer.h" //put our own includes before system includes
#include "Vector2.h"

#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <vector>
#include "Input.h"

//#include "../../Engine/Source/Test.h"
// "../" puts us into a previous folder (so once to get to game, and once to get to Solution
//had to change to "not using precompiled header" to make the second include work
//but now that we've done and include directory, we can just do




void drawRandom(Renderer renderer);
void drawShape(Renderer renderer);
void drawVectors(Renderer renderer, std::vector<Vector2> points);



int main(int argc, char* argv[])
{
	//Initializing important parts of game engine
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();


	Vector2 v1{ 400, 300 };
	Vector2 v2{ 200, 100 };

	std::vector<Vector2> points;
	//for (int i = 0; i < 100; i++)
	//{
		//points.push_back(Vector2{ rand() % 800, rand() % 600 });
	//}



	//main loop
	bool quit = false;
	while (!quit)
	{
		//input
		//updat
		//draw

		//__INPUT__
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}


		//__UPDATE__
		Vector2 mousePosition = input.getMousePosition();
		std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0))
		{
			std::cout << "Mouse pressed\n";
			points.push_back(mousePosition);
		}

		if (input.GetMouseButtonDown(0) && input.GetPrevMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			if(distance > 5) points.push_back(mousePosition); //this can be done if an only if the operation in the if statement is only one line
		}
	 
		
		//[p, p, p, p]
		//Vector2 speed{ 0.1f, -0.1f };
		//for (Vector2& point : points)
		//{
			//point = point + speed;
			//point = point + 0.002f;
			//by the power of operator overloading!
		//}
		//THIS MAKES THE SHAPE MOVE!!! :D
		



		//__DRAW__
		//	// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//	SDL_RenderClear(renderer);

		//drawRandom(renderer);
		//drawShape(renderer);
		//drawVectors(renderer, points);

		//renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		//	// draw line
		//renderer.SetColor(255, 255, 255, 0);
		//renderer.DrawLine(0, 0, 800, 600);

		drawVectors(renderer, points);



		//	// show screen
		//	SDL_RenderPresent(renderer);
		renderer.EndFrame();
	}

	return 0;
}


void drawRandom(Renderer renderer)
{
	//int value = rand() % 1000;

	for (int i = 0; i < 50; i++)
	{
		renderer.SetColor(255, 255, 255, 0);
		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0); // create random color

		int p1_x = rand() % 800;
		int p1_y = rand() % 600;
		int p2_x = rand() % 800;
		int p2_y = rand() % 600;
		renderer.DrawPoint(p1_x, p1_y);
		renderer.DrawPoint(p2_x, p2_y);
		renderer.DrawLine(p1_x, p1_y, p2_x, p2_y);
	}


}

void drawShape(Renderer renderer)
{
	renderer.SetColor(255, 255, 255, 0);
	renderer.DrawPoint(400, 300);
	renderer.DrawPoint(300, 400);
	renderer.DrawPoint(500, 550);

	renderer.DrawLine(400, 300, 300, 400);
	renderer.DrawLine(400, 300, 500, 550);
	renderer.DrawLine(300, 400, 500, 550);
}


void drawVectors(Renderer renderer, std::vector<Vector2> points)
{
	for (int i = 0; points.size() > 1 & i < points.size() - 1; i++)
	{
		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
		renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
}


//Dynamic Linked Library (done at runtime) .dll
//Static Linked Library (done at compile time) .lib
//Objects (the compiled object code) .obj
//Executable (what you run) .exe
//Headers (declares things in a class) .h
//CPP (not sure what it stands for) (defines things in a class) .cpp



//Characters are single quotes, strings are double quotes