#pragma once
#include "Transform.h"
#include "Model.h"
#include<iostream>
//#include "Model.h"  //not going to include because we'll use a forward reference instead 
//ONLY do this if we don't use any functions or anything contained within that class AND it's a pointer or reference

class Model; //another way to do a forward declaration
class Renderer;
class Scene;

class Actor
{
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}
	Actor(const Transform& transform, Model* model) : 
		m_transform{ transform }, 
		m_model{ model }
	{}

	//virtual means it is going to be overridden
	virtual void Update(float dt);
	void Draw(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }

	const Transform& GetTransform() { return m_transform; }

	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	bool& GetDestroyed() { return m_destroyed; }

	//"On"[thing] is the typical naming convention for event things such as this
	virtual void OnCollision(Actor* actor) = 0; //=0 makes this a pure virtual function, which makews Actor and abstract class :)   (so it can never be created)
	float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }


	friend class Scene; //we want our friends to have access to our protected variables/functions

protected: //since it needs to be accessable to child classes
	std::string m_tag;

	bool m_destroyed = false;
	float m_lifespan = 0;
	
	Transform m_transform;
	Vector2 m_velocity{ 0,0 };
	float m_damping{ 0 };

	Model* m_model{ nullptr };
	Scene* m_scene{ nullptr };

};