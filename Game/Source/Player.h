#pragma once
#include "Actor.h" //include not optional when deriving (creating a child class)
#include "Font.h"
#include "Engine.h"
#include "Color.h"

class Font;

//declares Player as an Actor
class Player : public Actor
{
public:
	Player() = default; 
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Player(float speed, const Transform& transform, Model* model, int* score, bool* isAlive, int* lives) :
		Actor{ transform, model }, 
		m_speed{ speed },
		m_score{ score },
		m_isAlive{isAlive},
		m_lives{ lives }
	{}


	//virtual declares an override
	virtual void Update(float dt);
	void OnCollision(Actor* actor);

	void SetFireModifier(float modifier) { m_fireModifier = modifier; }

private:
	float m_speed = 0;
	float m_fireTimer = 0.3f;

	int* m_score = 0;
	bool* m_isAlive{ nullptr };
	int* m_lives = 0;
	
	float m_fireModifier = 1;
};