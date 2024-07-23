#pragma once
#include "Particle.h"

#include <list>
#include<memory>

class Renderer;
class Actor;
class Game;

class Scene
{
public:
	Scene() = default;
	Scene(Game* game) : m_game{ game } {}

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	void RemoveAll();

	void AddParticles(Actor* actor);

	template<typename T>
	T* GetActor();

	Game* GetGame() { return m_game; }

protected:
	std::list<std::unique_ptr<Actor>> m_actors;
	std::list<Particle*> m_particles;
	//std::vector<Particle> m_particles;

	Game* m_game{ nullptr };

};

//Template must be in the header, CANNOT be in the cpp
	template<typename T>
	T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get()); 
			if (result) return result;
		}

		return nullptr;
	}



//implicit casting
//char c = 5;
//int i = c

//or

//float f = 23.54f;
//double d = f;


//Static Cast
//int i = 10;
//float f = 1 / (float)i;
//float f = 1 / static_case<float>(i0;
//done at compile time

//Dynamic Cast
//Class A; Class B; Class C; Class D;
//cast one to the other to check if it is that class,. Else returns null