#pragma once
#include "Game.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"


#include <string>

class FishGame : public Game
{
public:
	//without class after enum, it is unscoped. This can lead to name issues (such as with a Game enum and a Game class
	enum class eState : char //this saves memory (4 bytes to 1 byte)
	{
		Title, 
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver,
		SetWin,
		GameWon,
		LevelTransition
	};

public:
	FishGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;

	void Shutdown() override;

	void Update(float dt) override;

	void Draw(Renderer& renderer) override;


private:
	eState m_state{ eState:: Title };
	bool playerAlive = true;
	
	float m_transitionTime{ 0 };
	int m_levelCap{ 0 };


	float m_SpawnTimer{ 0 };
	float m_SpawnTime{ 0 };
	float m_fishTimer{ 0 };
	float m_smallFishTimer{ 0 };
	float m_largeFishTimer{ 0 };
	float m_veryLargeFishTimer{ 0 };
	
	Font* titleFont = new Font();
	Font* scoreFont = new Font();
	Font* toStartFont = new Font();
	Font* transitionFont = new Font();

	Text* title = new Text(titleFont);
	Text* spaceToStart = new Text(toStartFont);

	Text* scoreText = new Text(scoreFont);

	Text* gameOverText = new Text(titleFont);
	Text* spaceToRestart = new Text(toStartFont);
	
	Text* levelTransitionText_1 = new Text(transitionFont);
	Text* levelTransitionText_2 = new Text(transitionFont);
	Text* levelTransitionText_3 = new Text(transitionFont);

	//Text* gameWonText = new Text(titleFont);
	//Text* spaceToContinue = new Text(toStartFont);


	std::string m_sScore = "Score: ";
	std::string m_ScoreMessage = "";
	std::string m_transitionMessage_1 = "After finally becoming the largest fish in your pond ";
	std::string m_transitionMessage_2 = "you finally make your way to cleaner ";
	std::string m_transitionMessage_3 = "and most importantly DEEPER waters.";
	//You make your way to better and, more importantly, LARGER waters.
};