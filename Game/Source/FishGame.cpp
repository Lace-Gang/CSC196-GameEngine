#include "FishGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Fish.h"
#include "GameData.h"
#include "Text.h"

#include<string>

bool FishGame::Initialize()
{
    m_scene = new Scene();
	
	font->Load("homespun.ttf", 20);
	text->Create(g_engine.GetRenderer(), "Big Fish, Little Fish", Color{ 1, 1, 1, 1 });


    return true;
}

void FishGame::Shutdown()
{
}

void FishGame::Update(float dt)
{
	


	switch (m_state)
	{
		case eState::Title:
			if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			{
				font->Load("homespun.ttf", 20);
				text->Create(g_engine.GetRenderer(), "Big Fish, Little Fish", Color{ 1, 1, 1, 1 });

				m_state = eState::StartGame;
			}
			break;



		case eState::StartGame:
			m_score = 0;
			m_state = eState::StartLevel;

			//loading fonts
			//font->Load("arcadeclassic.ttf", 20);
			//font->Load("vcr_osd_mono.tff", 20); this tff file seems to be incompatible 

			break;



		case eState::StartLevel:
			{
				m_state = eState::Game;
				Model* model = new Model{ GameData::shipPoints, Color{0, 0.65f, 1.0f} }; //actor models
				Model* enemyModel = new Model{ GameData::shipPoints, Color{1, 0, 1.0f} };


				Transform transform{ Vector2{ randomf(0, 800), randomf(0,600)}, 0, randomf(0,5) }; //the last two perameters here are optional
				Player* player = new Player(300, transform, model);
				player->SetTag("Player");
				player->SetDamping(2.0f);
				m_scene->AddActor(player);
	
			}

			m_fishTimer = 4;

			m_state = eState::Game;
			break;



		case eState::Game:
		{
			std::string m_ScoreMessage = m_Message + std::to_string(m_score);
			//text->Create(g_engine.GetRenderer(), m_ScoreMessage, Color{ 1, 1, 1, 1 });

		}

		//This next section is responsible for spawning in fish
		{
			m_fishTimer += g_engine.GetTime().GetDeltaTime();

			Model* fishModel = new Model{ GameData::shipPoints, Color{0.1f, 0.1f, 1.0f} };
			
			if (m_fishTimer >= 5)
			{
				m_fishTimer = 0;
			
				Transform fishTransform{ Vector2{ 0.0f, randomf(0,600)}, 0, randomf(0,5) };
				Fish* fish = new Fish(randomf(50, 150), fishTransform, fishModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Fish");
				m_scene->AddActor(fish);
			}

		}
			break;



		case eState::PlayerDead:
			break;



		case eState::GameOver:
			break;

		default:
			break;
	}


    m_scene->Update(dt);
}

void FishGame::Draw(Renderer& renderer)
{
	switch(m_state)
	{
	case eState::Title:
		//draw text "Game Title"
		text->Draw(g_engine.GetRenderer(), 40, 40);

		break;


	case eState::StartGame:
		break;


	case eState::StartLevel:
	
	break;


	case eState::Game:
		//text->Draw(g_engine.GetRenderer(), 40, 40);

		break;


	case eState::PlayerDead:

		break;


	case eState::GameOver:
		//Draw text "Game Over'
		break;

	default:
		break;
	}

	m_scene -> Draw(renderer);
}
