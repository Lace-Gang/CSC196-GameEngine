#include "Renderer.h" //put our own includes before system includes
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETimer.h"
#include "Color.h"
#include "MathUtils.h"

#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <vector>
#include <fmod.hpp>


//#include "../../Engine/Source/Test.h"
// "../" puts us into a previous folder (so once to get to game, and once to get to Solution
//had to change to "not using precompiled header" to make the second include work
//but now that we've done and include directory, we can just do




void drawRandom(Renderer renderer);
void drawShape(Renderer renderer);
void drawVectors(Renderer renderer, std::vector<Vector2> points);



int main(int argc, char* argv[])
{

	//std::cout << Math::Abs(-2);
	//Initializing important parts of game engine/game
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);


	Input input;
	input.Initialize();

	Time time;

	Color color;

	float offset = 0;

	//particles
	std::vector<Particle> particles;
	for (int i = 0; i < 100; i++)
	{
		//particles.push_back(Particle{ {rand() % 800, rand() % 600}, {randomf(100,300), 0.0f}}); //even just putting "Particle" here is optional btw. you don't need to put Vector2 because it already knows that's what it will be, so just put the points
	}

	//sounds
	FMOD::Sound* sound = nullptr;
	//audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

	//audio->playSound(sound, 0, false, nullptr);

	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound); //0
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound); //1
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound); //2
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound); //3
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound); //4
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound); //5
	sounds.push_back(sound);


	


	



	//main loop
	bool quit = false;
	while (!quit)
	{
		//input
		//updat
		//draw

		//__INPUT__
		time.Tick(); //tick is almost ALWAYS at the start of a while loop like this

		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}


		//__UPDATE__
		Vector2 mousePosition = input.getMousePosition();
		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		audio->update();

		
		if (input.GetMouseButtonDown(0))
		{
			if (!input.GetPrevMouseButtonDown(0))
			{
				color = { (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255) };
			}
			//particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * random(50, 300), randomf(-300, 300)}); //even just putting "Particle" here is optional btw. you don't need to put Vector2 because it already knows that's what it will be, so just put the points
			//particles.push_back(Particle{ mousePosition, {randomOnUnitCircle() * random(50, 300), {randomf(-300, 300)}, randomf(1, 5), color });
			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * random(50, 300), randomf(1, 5), color });
		}


		//sound updates
		if (input.GetKeyDown(SDL_SCANCODE_A) && !input.GetPrevKeyDown(SDL_SCANCODE_A))
		{
			// play bass sound, vector elements can be accessed like an array with [#]
			sound = sounds[0];
			audio->playSound(sound, 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_S) && !input.GetPrevKeyDown(SDL_SCANCODE_S))
		{
			sound = sounds[1];
			audio->playSound(sound, 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_D) && !input.GetPrevKeyDown(SDL_SCANCODE_D))
		{
			sound = sounds[2];
			audio->playSound(sound, 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_F) && !input.GetPrevKeyDown(SDL_SCANCODE_F))
		{
			sound = sounds[3];
			audio->playSound(sound, 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_J) && !input.GetPrevKeyDown(SDL_SCANCODE_J))
		{
			sound = sounds[4];
			audio->playSound(sound, 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_K) && !input.GetPrevKeyDown(SDL_SCANCODE_K))
		{
			sound = sounds[5];
			audio->playSound(sound, 0, false, nullptr);
		}
		

		//particle updates
		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}



		//__DRAW__
		//	// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//	SDL_RenderClear(renderer);

		
		//draw particles
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}

		renderer.SetColor(255, 255, 255, 0);
		float radius = 30;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 /30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle)  * 0.05f) * radius; //try messing around with the stuff in here. You can get a LOT of cool stuff!
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.05f) * radius;

			renderer.DrawRect(x + 400 , y + 300, 4.0f, 4.0f); //the 400 and 300 are so that it is in the middle of the screen instead of the top corner)
		}



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


//one frame = one update + one draw




//things that ONLY work when points is present

//place above main loop in initializing in the main function

//std::vector<Vector2> points;
	//for (int i = 0; i < 100; i++)
	//{
		//points.push_back(Vector2{ rand() % 800, rand() % 600 });
	//}


//place in update
// 
//if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0))
		//{
			//std::cout << "Mouse pressed\n";
			//points.push_back(mousePosition);
		//}

		//if (input.GetMouseButtonDown(0) && input.GetPrevMouseButtonDown(0))
		//{
			//float distance = (points.back() - mousePosition).Length();
			//if(distance > 5) points.push_back(mousePosition); //this can be done if an only if the operation in the if statement is only one line
		//}

//place in draw
//[p, p, p, p]
		//Vector2 speed{ 0.1f, -0.1f };
		//for (Vector2& point : points)
		//{
			//point = point + speed;
			//point = point + 0.002f;
			//by the power of operator overloading!
		//}
		//THIS MAKES THE SHAPE MOVE!!! :D