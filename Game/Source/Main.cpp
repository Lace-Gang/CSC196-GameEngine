#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Fish.h"
#include "Font.h"
#include "Text.h"
#include "GameData.h"
#include "FishGame.h"


#include <iostream>
#include <cstdlib>
#include <vector>





//void drawRandom(Renderer renderer);
//void drawShape(Renderer renderer);
//void drawVectors(Renderer renderer, std::vector<Vector2> points);



int main(int argc, char* argv[])
{
	g_engine.Initialize();

	FishGame* game = new FishGame(&g_engine);
	game->Initialize();

	while (!g_engine.IsQuit())
	{

		//____INPUT____

		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());


		//____DRAW____


		//	// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());
		g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();



	}

	g_engine.Shutdown();

	return 0;
}

/*



	//Initializing important parts of game engine/game (create systems)
	
	//loading sound
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("snare.wav");

	//loading fonts
	Font* font = new Font();
	font->Load("arcadeclassic.ttf", 20);
	//font->Load("vcr_osd_mono.tff", 20); this tff file seems to be incompatible 

	//loading text
	Text* text = new Text(font);
	text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	//void* extradriverdata = nullptr;
	//audio->init(32, FMOD_INIT_NORMAL, extradriverdata);


	//Input input;
	

	Color color;

	float offset = 0;

	float fishTimer = 4;
	float spawnTimer = 2;




	

	//particles
	std::vector<Particle> particles;
	


	//std::vector<Vector2> points;
	//points.push_back(Vector2{ 7, 0 });
	//points.push_back(Vector2{ 3, -2 });
	//points.push_back(Vector2{ 1.0f, -2.5f });
	//points.push_back(Vector2{ -1, -2 });
	//points.push_back(Vector2{ -5, 0 });
	//points.push_back(Vector2{ -8, -2 });
	//points.push_back(Vector2{ -8, 4 });
	//points.push_back(Vector2{ -5, 2 });
	//points.push_back(Vector2{ -2, 3 });
	//points.push_back(Vector2{ 0.0f, 3.1f });
	//points.push_back(Vector2{ 1, 3 });
	//points.push_back(Vector2{ 3.5f, 2.25f });
	//points.push_back(Vector2{ 5.0f, 1.5f });
	//points.push_back(Vector2{ 7, 0 });

	

	Model* model = new Model{ GameData::shipPoints, Color{0, 0.65f, 1.0f} }; //actor
	Model* enemyModel = new Model{ GameData::shipPoints, Color{1, 0, 1.0f} };
	Model* fishModel = new Model{ GameData::shipPoints, Color{0.1f, 0.1f, 1.0f} };


	//Transform transform{ { g_engine.GetRenderer().GetWidth() >> 1, g_engine.GetRenderer().GetHeight() / 2}, 0, 8 }; //the last two perameters here are optional
	// >> 1 (shifts the binary over by one) (8 would go to 4, to 2, to 1)
	//As used above in the Transform transform  to divide by 2 :)
	// ">> 1>>"   :) 


	Scene* scene = new Scene();


	
		Transform transform{ Vector2{ randomf(0, 800), randomf(0,600)}, 0, randomf(0,5) }; //the last two perameters here are optional
		Player* player = new Player(300, transform, model);
		player->SetTag("Player");
		player->SetDamping(2.0f);
		scene->AddActor(player);
	




		Enemy* enemy = new Enemy(400, Transform{ {300, 300 }, 0, 2 }, enemyModel); 
		enemy->SetTag("Enemy");
		enemy->SetDamping(2.0f);
		scene->AddActor(enemy);

		//
		auto examplef = 4.5f; //auto lets the computer imply what data type if there's enough reason to believe it can accurately assume
		//
	

	
		




	//main loop
	while (!g_engine.IsQuit())
	{
		//input
		//updat
		//draw



		//____INPUT____
		
		//time.Tick(); //tick is almost ALWAYS at the start of a while loop like this

		g_engine.Update();



		fishTimer += g_engine.GetTime().GetDeltaTime();



		

		

		//____UPDATE____

		Vector2 mousePosition = g_engine.GetInput().getMousePosition();

		scene->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetAudio().Update();

		
		if (g_engine.GetInput().GetMouseButtonDown(0))
		{
			if (!g_engine.GetInput().GetPrevMouseButtonDown(0))
			{
				color = { randomf(255), randomf(255), randomf(255), randomf(255) };
			}
			
			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * random(50, 300), randomf(1, 5), color });
		}


		//sound updates
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_A)) g_engine.GetAudio().PlaySound("bass.wav");

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_S)) g_engine.GetAudio().PlaySound("clap.wav");

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_D)) g_engine.GetAudio().PlaySound("close-hat.wav");

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_F) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_F)) g_engine.GetAudio().PlaySound("cowbell.wav");

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_J) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_J)) g_engine.GetAudio().PlaySound("open-hat.wav");

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_K) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_K)) g_engine.GetAudio().PlaySound("snare.wav");
		

		//particle updates
		for (Particle& particle : particles)
		{
			particle.Update(g_engine.GetTime().GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		//fish spawning
		if (fishTimer >= 5)
		{
			fishTimer = 0;

			Transform fishTransform{ Vector2{ 0.0f, randomf(0,600)}, 0, randomf(0,5) };
			Fish* fish = new Fish(randomf(50, 150), fishTransform, fishModel, g_engine.GetRenderer().GetWidth());
			fish->SetTag("Fish");
			scene->AddActor(fish);
		}






		//____DRAW____
		
		
		//	// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();


		
		//draw particles
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(g_engine.GetRenderer());
		}

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		float radius = 30;
		offset += (90 * g_engine.GetTime().GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 /30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle)  * 0.05f) * radius; 
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.05f) * radius;
		}



		scene->Draw(g_engine.GetRenderer());
		text->Draw(g_engine.GetRenderer(), 40, 40);



		//	// show screen
		//	SDL_RenderPresent(renderer);
		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}


void drawRandom(Renderer renderer)
{
	//int value = rand() % 1000;

	for (int i = 0; i < 50; i++)
	{
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		g_engine.GetRenderer().SetColor(rand() % 256, rand() % 256, rand() % 256, 0); // create random color

		int p1_x = rand() % 800;
		int p1_y = rand() % 600;
		int p2_x = rand() % 800;
		int p2_y = rand() % 600;
		g_engine.GetRenderer().DrawPoint(p1_x, p1_y);
		g_engine.GetRenderer().DrawPoint(p2_x, p2_y);
		g_engine.GetRenderer().DrawLine(p1_x, p1_y, p2_x, p2_y);
	}


}

void drawShape(Renderer renderer)
{
	g_engine.GetRenderer().SetColor(255, 255, 255, 0);
	g_engine.GetRenderer().DrawPoint(400, 300);
	g_engine.GetRenderer().DrawPoint(300, 400);
	g_engine.GetRenderer().DrawPoint(500, 550);
	
	g_engine.GetRenderer().DrawLine(400, 300, 300, 400);
	g_engine.GetRenderer().DrawLine(400, 300, 500, 550);
	g_engine.GetRenderer().DrawLine(300, 400, 500, 550);
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

*/