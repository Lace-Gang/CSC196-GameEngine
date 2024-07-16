#pragma once
#include "Actor.h" 


class Fish : public Actor
{
public:
	Fish() = default;
	Fish(const Transform& transform) : Actor{ transform } {}
	Fish(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Fish(float speed, const Transform& transform, Model* model, int scope = 900) :
		Actor{ transform, model },
		m_speed{ speed },
		m_scope{ scope }
	{}


	//virtual declares an override
	virtual void Update(float dt);

private:
	float m_speed = 0;
	int m_scope = 0;
};