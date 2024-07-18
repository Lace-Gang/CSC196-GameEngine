#include "Scene.h"
#include "Actor.h"
#include "Model.h"

#include<algorithm> //for remove_if

void Scene::Update(float dt)
{
	//update

	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
	}

	//destroy
	//c++ doesn't like when you destroy items in a list while in a for each.
	//so we will be using an itterator
	
	//std::list<Actor*>::iterator iter = m_actors.begin(); (great place to use auto instead)
	auto iter = m_actors.begin();
	while (iter != m_actors.end())
	{
		iter = ((*iter)->m_destroyed) ? m_actors.erase(iter) : ++iter; //if iter is destroyed,erase itter. Else ++itter
		//itter++ means to do the ++ after the line (postfix) ++itter means do ++ IN the line (prefix)
	}

	//lambda expressions
	//It moves the things it finds to the back of the list ig? Or something?
	//Just . . . look up how these work later /lh
	//ESPECIALLY if you want to try to USE this
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](Actor* actor) { return actor->m_destroyed; }), m_actors.end());
	// The std::remove_if algorithm reorders the elements in the range [m_actors.begin(), m_actors.end()]
   // such that the elements that satisfy the predicate (i.e., those that should be removed) are moved
   // to the end of the range. The algorithm returns an iterator to the beginning of the "removed" range,
   // which is the new logical end of the container.



	//collision
	for (Actor* actor1 : m_actors)
	{
		//collision
		for (Actor* actor2 : m_actors)
		{
			if (actor1 == actor2) continue; //skip the rest of the loop if they both pointers point to the same object

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();

			float radius = actor1->m_model->GetRadius() + actor2->m_model->GetRadius();

			if (distance <= radius)
			{
				//getting here means that a collision has occured.
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);
			}
		}
	}

}

void Scene::Draw(Renderer& renderer)
{
	for (Actor* actor : m_actors)
	{
		actor->Draw(renderer);
	}
}

void Scene::AddActor(Actor* actor)
{
	actor->m_scene = this;
	m_actors.push_back(actor);
}
