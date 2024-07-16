#pragma once
#include "Actor.h" //include not optional when deriving (creating a child class)


//declares Player as an Actor
class Enemy : public Actor
{
public:
	Enemy() = default;
	Enemy(const Transform& transform) : Actor{ transform } {}
	Enemy(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Enemy(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}


	//virtual declares an override
	virtual void Update(float dt);

private:
	float m_speed = 0;
	float m_fireTimer = 0;
};
