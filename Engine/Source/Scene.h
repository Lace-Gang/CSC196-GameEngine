#pragma once

#include <list>

class Renderer;
class Actor;

class Scene
{
public:
	Scene() = default;

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(Actor* actor);

	template<typename T>
	T* GetActor();

protected:
	std::list<Actor*> m_actors;

};

//Template must be in the header, CANNOT be in the cpp
	template<typename T>
	T* Scene::GetActor()
	{
		for (Actor* actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor); 
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