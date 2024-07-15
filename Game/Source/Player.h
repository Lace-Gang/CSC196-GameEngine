#pragma once
#include "Actor.h" //include not optional when deriving (creating a child class)


//declares Player as an Actor
class Player : public Actor
{
public:
	Player() = default; 
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model }, 
		m_speed{ speed }
	{}


	//virtual declares an override
	virtual void Update(float dt);

private:
	float m_speed = 0;

};