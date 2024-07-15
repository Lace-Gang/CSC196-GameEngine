#pragma once
#include "Transform.h"
//#include "Model.h"  //not going to include because we'll use a forward reference instead 
//ONLY do this if we don't use any functions or anything contained within that class AND it's a pointer or reference

class Model; //another way to do a forward declaration
class Renderer;

class Actor
{
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}
	Actor(const Transform& transform, Model* model) : 
		m_transform{ transform }, 
		m_model{ model }
	{}

	virtual void Update(float dt);
	void Draw(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }



protected: //since it needs to be accessable to child classes
	bool m_destroyed = false;
	float m_lifespan = 0;
	
	Transform m_transform;
	Vector2 m_velocity{ 0,0 };
	float m_damping{ 0 };

	Model* m_model{ nullptr };

};