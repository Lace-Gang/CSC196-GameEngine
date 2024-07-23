#include "FishGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Fish.h"
#include "GameData.h"
#include "Text.h"
#include "Pickup.h"

#include<string>

bool FishGame::Initialize()
{
    m_scene = new Scene(this);
	
	g_engine.GetAudio().AddSound("crank.wav");
	g_engine.GetAudio().AddSound("undersea.wav");


    return true;
}

void FishGame::Shutdown()
{ 
}

void FishGame::Update(float dt)
{
	m_musicTimer += dt;

	if (m_musicTimer >= 102)
	{
		m_musicTimer = 0;
		g_engine.GetAudio().PlaySound("undersea.wav");
	}
	
	switch (m_state)
	{
		case eState::Title:
			titleFont->Load("homespun.ttf", g_engine.GetRenderer().GetWidth()*0.065); //20
			toStartFont->Load("homespun.ttf", g_engine.GetRenderer().GetWidth()*0.025); //20


			title->Create(g_engine.GetRenderer(), "Big Fish, Little Fish", Color{ 1, 1, 1, 1 });
			spaceToStart->Create(g_engine.GetRenderer(), "Press Space To Start", Color{ 1, 1, 1, 1 });

			if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			{

				m_state = eState::StartGame;
			}
			break;



		case eState::StartGame:
			m_score = 0;
			m_lives = 1;
			m_levelCap = 0;
			scoreFont->Load("VCR_OSD_MONO.ttf", 20);
			m_scene->RemoveAll();

			m_state = eState::StartLevel;

			//loading fonts
			//font->Load("arcadeclassic.ttf", 20);
			//font->Load("vcr_osd_mono.tff", 20); this tff file seems to be incompatible 

			break;


		case eState::StartLevel:
			playerAlive = true;
			m_levelCap = m_score + 1000;

			m_scene->RemoveAll();

			

			{
				m_state = eState::Game;
				Model* model = new Model{ GameData::shipPoints, Color{0, 0.65f, 1.0f} }; //actor models
				Model* enemyModel = new Model{ GameData::shipPoints, Color{1, 0, 1.0f} };


				Transform transform{ Vector2{ randomf(0, 800), randomf(0,600)}, 0.0f, 2 }; //randomf(0,5)
				auto player = std::make_unique<Player>(300, transform, model, &m_score, &playerAlive, &m_lives);
				player->SetTag("Player");
				player->SetDamping(2.0f);
				m_scene->AddActor(std::move(player));

				m_player = player.get();
	
			}

			m_fishTimer = 4;
			m_smallFishTimer = 5;
			m_largeFishTimer = 10;
			m_veryLargeFishTimer = 20;
			m_lifeTimer = 30;
			m_enemyTimer = 1;

			//this has to be set up here of the game will crash, then it refreshes in the eState::Game to keep it acurate
			m_ScoreMessage = m_sScore + std::to_string(m_score);
			scoreText->Create(g_engine.GetRenderer(), m_ScoreMessage, Color{ 1, 1, 1, 1 });
			m_LivesMessage = m_sLives + std::to_string(m_lives);
			livesText->Create(g_engine.GetRenderer(), m_LivesMessage, Color{ 1, 1, 1, 1 });


			m_stateTimer = 3;

			m_state = eState::Game;
			break;



		case eState::Game:
		
			m_ScoreMessage = m_sScore + std::to_string(m_score);
			scoreText->Create(g_engine.GetRenderer(), m_ScoreMessage, Color{ 1, 1, 1, 1 });
			m_LivesMessage = m_sLives + std::to_string(m_lives);
			livesText->Create(g_engine.GetRenderer(), m_LivesMessage, Color{ 1, 1, 1, 1 });

			if (!playerAlive || m_lives <= 0)
			{
				gameOverText->Create(g_engine.GetRenderer(), "GAME OVER", Color{ 1, 1, 1, 1 });
				spaceToRestart->Create(g_engine.GetRenderer(), "Press Space to Restart", Color{ 1, 1, 1, 1 });

				m_state = eState::GameOver;
				break;
			}

			if (m_score >= m_levelCap)
			{
				m_state = eState::SetWin;
			}

		

		//This next section is responsible for spawning in fish
		{
			m_fishTimer += g_engine.GetTime().GetDeltaTime();
			m_smallFishTimer += g_engine.GetTime().GetDeltaTime();
			m_largeFishTimer += g_engine.GetTime().GetDeltaTime();
			m_veryLargeFishTimer += g_engine.GetTime().GetDeltaTime();
			m_lifeTimer += g_engine.GetTime().GetDeltaTime();
			m_enemyTimer += g_engine.GetTime().GetDeltaTime();


			Model* fishModel = new Model{ GameData::shipPoints, Color{0.1f, 0.1f, 1.0f} };
			Model* lifeModel = new Model{ GameData::shipPoints, Color{1.0f, 1.0f, 0.1f} };
			Model* enemyModel = new Model{ GameData::shipPoints, Color{1, 0, 1.0f} };
			
			if (m_fishTimer >= 5)
			{
				m_fishTimer = 0;
			
				Transform fishTransform{ Vector2{ 0.0f, randomf(0, g_engine.GetRenderer().GetHeight())}, 0, randomf(0,12) };
				auto fish = std::make_unique<Fish>(randomf(50, 150), fishTransform, fishModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Fish");
				m_scene->AddActor(std::move(fish));
			}
			
			if (m_smallFishTimer >= 9)
			{
				m_smallFishTimer = 0;
			
				Transform fishTransform{ Vector2{ 0.0f, randomf(0, g_engine.GetRenderer().GetHeight())}, 0, randomf(0,4) };
				auto fish = std::make_unique < Fish>(randomf(50, 150), fishTransform, fishModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Fish");
				m_scene->AddActor(std::move(fish));
			}
			
			if (m_largeFishTimer >= 23)
			{
				m_largeFishTimer = 0;
			
				Transform fishTransform{ Vector2{ 0.0f, randomf(0, g_engine.GetRenderer().GetHeight())}, 0, randomf(0,20) };
				auto fish = std::make_unique < Fish>(randomf(50, 150), fishTransform, fishModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Fish");
				m_scene->AddActor(std::move(fish));
			}
			
			if (m_veryLargeFishTimer >= 45)
			{
				m_veryLargeFishTimer = 0;
			
				Transform fishTransform{ Vector2{ 0.0f, randomf(0, g_engine.GetRenderer().GetHeight())}, 0, randomf(21,32) };
				auto fish = std::make_unique <Fish>(randomf(50, 150), fishTransform, fishModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Fish");
				m_scene->AddActor(std::move(fish));
			}

			//spawns extra life
			if (m_lifeTimer >= 50)
			{
				m_lifeTimer = 0;

				Player* player = m_scene->GetActor<Player>();
				Transform fishTransform{ Vector2{ 0.0f, randomf(0, g_engine.GetRenderer().GetHeight())}, 0, randomf(0,player->GetTransform().scale - 1) };
				auto fish = std::make_unique < Fish>(randomf(50, 150), fishTransform, lifeModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Life");
				m_scene->AddActor(std::move(fish));
			}

			//spawns enemy
			if (m_enemyTimer >= 34)
			{
				m_enemyTimer = 0;

				Player* player = m_scene->GetActor<Player>();
				Transform fishTransform{ Vector2{ 0.0f, randomf(0, g_engine.GetRenderer().GetHeight())}, 0, randomf((player->GetTransform().scale/2),player->GetTransform().scale)};
				auto fish = std::make_unique < Fish>(randomf(50, 150), fishTransform, enemyModel, g_engine.GetRenderer().GetWidth());
				fish->SetTag("Enemy");
				m_scene->AddActor(std::move(fish));
			}


			//pickup spawn
			if (m_pickupTimer <= -1)
			{
				m_pickupTimer = 0;

				Transform fishTransform{ Vector2{ 0.0f, randomf(0,600)}, 0, randomf(0,12) };
				auto pickup = std::make_unique < Pickup>(fishTransform, fishModel);
				pickup->SetTag("pickup");
				m_scene->AddActor(std::move(pickup));
			}



		}
			break;



		case eState::PlayerDead:
			m_scene->RemoveAll();
			m_stateTimer -= dt;
			if (m_stateTimer <= 0)
			{
				//m_levelCap = 0;
				m_state = eState::StartLevel;

			}


			break;



		case eState::GameOver:
			if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::StartGame;
			}


			break;

		case eState::SetWin:

			gameOverText->Create(g_engine.GetRenderer(), "You Win!", Color{ 1, 1, 1, 1 });
			spaceToRestart->Create(g_engine.GetRenderer(), "Press Space to Continue", Color{ 1, 1, 1, 1 });

			m_state = eState::GameWon;

			break;

		case eState::GameWon:

			if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::LevelTransition;

				m_transitionTime = 0;

				transitionFont->Load("homespun.ttf", g_engine.GetRenderer().GetWidth() * 0.025);
				levelTransitionText_1->Create(g_engine.GetRenderer(), m_transitionMessage_1, Color{ 1, 1, 1, 1 });
				levelTransitionText_2->Create(g_engine.GetRenderer(), m_transitionMessage_2, Color{ 1, 1, 1, 1 });
				levelTransitionText_3->Create(g_engine.GetRenderer(), m_transitionMessage_3, Color{ 1, 1, 1, 1 });
			}

			break;

		case eState::LevelTransition:
			m_transitionTime += dt;


			//if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			//{
			//	m_state = eState::StartLevel;
			//}

			if (m_transitionTime >= 5)
			{
				m_state = eState::StartLevel;
			}


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
		title->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth()*0.25, g_engine.GetRenderer().GetHeight() / 2.1);
		spaceToStart->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth()*0.4, g_engine.GetRenderer().GetHeight() / 1.5);

		break;


	case eState::StartGame:
		break;


	case eState::StartLevel:
	
	break;


	case eState::Game:
		m_scene->Draw(renderer);

		scoreText->Draw(g_engine.GetRenderer(), 40, 40);
		livesText->Draw(g_engine.GetRenderer(), 40, 65);

		break;


	case eState::PlayerDead:

		m_scene->Draw(renderer);

		break;


	case eState::GameOver:
		m_scene->Draw(renderer);

		//Draw text "Game Over'
		scoreText->Draw(g_engine.GetRenderer(), 40, 40);
		livesText->Draw(g_engine.GetRenderer(), 40, 65);

		gameOverText->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth() * 0.35, g_engine.GetRenderer().GetHeight() / 2.5);
		spaceToRestart->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth() * 0.37, g_engine.GetRenderer().GetHeight() / 1.5);


		break;
	case eState::GameWon:
		m_scene->Draw(renderer);

		scoreText->Draw(g_engine.GetRenderer(), 40, 40);
		livesText->Draw(g_engine.GetRenderer(), 40, 65);

		gameOverText->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth() * 0.35, g_engine.GetRenderer().GetHeight() / 2.5);
		spaceToRestart->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth() * 0.37, g_engine.GetRenderer().GetHeight() / 1.5);

		break;

	case eState::LevelTransition:
		levelTransitionText_1->Draw(g_engine.GetRenderer(), 40, 40);
		levelTransitionText_2->Draw(g_engine.GetRenderer(), 40, 90);
		levelTransitionText_3->Draw(g_engine.GetRenderer(), 40, 140);
		break;

	default:
		break;
	}

	//m_scene -> Draw(renderer);


}

void FishGame::OnPlayerDeath()
{
	m_lives--;
	m_state = (m_lives == 0) ? eState::PlayerDead : eState::PlayerDead;   // eState::GameOver : eState::PlayerDead;
}


void FishGame::AddLives()
{
	m_lives++;
}