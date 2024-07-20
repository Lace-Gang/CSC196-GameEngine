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
		GameOver
	};

public:
	FishGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;

	void Shutdown() override;

	void Update(float dt) override;

	void Draw(Renderer& renderer) override;


private:
	eState m_state{ eState:: Title };
	float m_SpawnTimer{ 0 };
	float m_SpawnTime{ 0 };
	float m_fishTimer{ 0 };

	Font* font = new Font();
	Text* text = new Text(font);
	std::string m_Message = "Score; ";
};