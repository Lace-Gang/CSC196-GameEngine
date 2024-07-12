#include "Engine.h"


#include <iostream>
#include <cstdlib>
#include <vector>





void drawRandom(Renderer renderer);
void drawShape(Renderer renderer);
void drawVectors(Renderer renderer, std::vector<Vector2> points);



int main(int argc, char* argv[])
{
	g_engine.Initialize();



	//std::cout << Math::Abs(-2);
	//Initializing important parts of game engine/game (create systems)
	
	g_engine.GetAudio()->AddSound("bass.wav");
	g_engine.GetAudio()->AddSound("clap.wav");
	g_engine.GetAudio()->AddSound("close-hat.wav");
	g_engine.GetAudio()->AddSound("cowbell.wav");
	g_engine.GetAudio()->AddSound("open-hat.wav");
	g_engine.GetAudio()->AddSound("snare.wav");

	//void* extradriverdata = nullptr;
	//audio->init(32, FMOD_INIT_NORMAL, extradriverdata);


	//Input input;
	//input.Initialize();

	Time time;

	Color color;

	float offset = 0;

	//particles
	std::vector<Particle> particles;
	for (int i = 0; i < 100; i++)
	{
		//particles.push_back(Particle{ {rand() % 800, rand() % 600}, {randomf(100,300), 0.0f}}); //even just putting "Particle" here is optional btw. you don't need to put Vector2 because it already knows that's what it will be, so just put the points
	}



	


	std::vector<Vector2> points;
	points.push_back(Vector2{ 7, 0 });
	points.push_back(Vector2{ 3, -2 });
	points.push_back(Vector2{ 1.0f, -2.5f });
	points.push_back(Vector2{ -1, -2 });
	points.push_back(Vector2{ -5, 0 });
	points.push_back(Vector2{ -8, -2 });
	points.push_back(Vector2{ -8, 4 });
	points.push_back(Vector2{ -5, 2 });
	points.push_back(Vector2{ -2, 3 });
	points.push_back(Vector2{ 0.0f, 3.1f });
	points.push_back(Vector2{ 1, 3 });
	points.push_back(Vector2{ 3.5f, 2.25f });
	points.push_back(Vector2{ 5.0f, 1.5f });
	points.push_back(Vector2{ 7, 0 });
	Model model{ points, Color{0, 0.65f, 1.0f} };

	Transform transform{ { g_engine.GetRenderer()->GetWidth() >> 1, g_engine.GetRenderer()->GetHeight() / 2}, 0, 8}; //the last two perameters here are optional


	// >> 1 (shifts the binary over by one) (8 would go to 4, to 2, to 1)
	//As used above in the Transform transform  to divide by 2 :)
	// ">> 1>>"   :) 

	

	



	//main loop
	bool quit = false;
	while (!quit)
	{
		//input
		//updat
		//draw

		//__INPUT__
		time.Tick(); //tick is almost ALWAYS at the start of a while loop like this

		g_engine.GetInput()->Update();

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}



		float thrust = 0;

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_UP))
		{
			thrust = 400;
		}
		//if (input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -200;

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();

		
		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)g_engine.GetRenderer()->GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)g_engine.GetRenderer()->GetHeight());

		//transform.rotation = transform.rotation + time.GetDeltaTime(); //this doesn't work anymore
		//rotation = velocity * angle();

		//__UPDATE__
		Vector2 mousePosition = g_engine.GetInput()->getMousePosition();
		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		g_engine.GetAudio()->Update();

		
		if (g_engine.GetInput()->GetMouseButtonDown(0))
		{
			if (!g_engine.GetInput()->GetPrevMouseButtonDown(0))
			{
				//color = { (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255) };
				color = { randomf(255), randomf(255), randomf(255), randomf(255) };
			}
			//particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * random(50, 300), randomf(-300, 300)}); //even just putting "Particle" here is optional btw. you don't need to put Vector2 because it already knows that's what it will be, so just put the points
			//particles.push_back(Particle{ mousePosition, {randomOnUnitCircle() * random(50, 300), {randomf(-300, 300)}, randomf(1, 5), color });
			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * random(50, 300), randomf(1, 5), color });
		}


		//sound updates
		//go and make all of these single line if statements. it should work
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput()->GetPrevKeyDown(SDL_SCANCODE_A))
		{
					g_engine.GetAudio()->PlaySound("bass.wav");
		}

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput()->GetPrevKeyDown(SDL_SCANCODE_S))
		{
			g_engine.GetAudio()->PlaySound("clap.wav");
		}

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_D) && !g_engine.GetInput()->GetPrevKeyDown(SDL_SCANCODE_D))
		{
			g_engine.GetAudio()->PlaySound("close-hat.wav");
		}

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_F) && !g_engine.GetInput()->GetPrevKeyDown(SDL_SCANCODE_F))
		{
			g_engine.GetAudio()->PlaySound("cowbell.wav");
		}

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_J) && !g_engine.GetInput()->GetPrevKeyDown(SDL_SCANCODE_J))
		{
			g_engine.GetAudio()->PlaySound("open-hat.wav");
		}

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_K) && !g_engine.GetInput()->GetPrevKeyDown(SDL_SCANCODE_K))
		{
		
			g_engine.GetAudio()->PlaySound("snare.wav");
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
		g_engine.GetRenderer()->SetColor(0, 0, 0, 0);
		g_engine.GetRenderer()->BeginFrame();
		//	SDL_RenderClear(renderer);

		
		//draw particles
		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(*g_engine.GetRenderer());
		}

		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		float radius = 30;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 /30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle)  * 0.05f) * radius; //try messing around with the stuff in here. You can get a LOT of cool stuff!
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.05f) * radius;

			//renderer.DrawRect(x + 400 , y + 300, 4.0f, 4.0f); //the 400 and 300 are so that it is in the middle of the screen instead of the top corner)
		}



		model.Draw(*g_engine.GetRenderer(), transform);



		//	// show screen
		//	SDL_RenderPresent(renderer);
		g_engine.GetRenderer()->EndFrame();
	}

	return 0;
}


void drawRandom(Renderer renderer)
{
	//int value = rand() % 1000;

	for (int i = 0; i < 50; i++)
	{
		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		g_engine.GetRenderer()->SetColor(rand() % 256, rand() % 256, rand() % 256, 0); // create random color

		int p1_x = rand() % 800;
		int p1_y = rand() % 600;
		int p2_x = rand() % 800;
		int p2_y = rand() % 600;
		g_engine.GetRenderer()->DrawPoint(p1_x, p1_y);
		g_engine.GetRenderer()->DrawPoint(p2_x, p2_y);
		g_engine.GetRenderer()->DrawLine(p1_x, p1_y, p2_x, p2_y);
	}


}

void drawShape(Renderer renderer)
{
	g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
	g_engine.GetRenderer()->DrawPoint(400, 300);
	g_engine.GetRenderer()->DrawPoint(300, 400);
	g_engine.GetRenderer()->DrawPoint(500, 550);
	
	g_engine.GetRenderer()->DrawLine(400, 300, 300, 400);
	g_engine.GetRenderer()->DrawLine(400, 300, 500, 550);
	g_engine.GetRenderer()->DrawLine(300, 400, 500, 550);
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




//the triangle
//points.push_back(Vector2{ 5, 0 });
	//points.push_back(Vector2{ -5, -5 });
	//points.push_back(Vector2{ -5, 5 });
	//points.push_back(Vector2{ 5, 0 });