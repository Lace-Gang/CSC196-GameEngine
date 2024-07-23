#include "Scene.h"
#include "Actor.h"
#include "Model.h"
#include "Engine.h"
#include "Particle.h"
#include "Color.h"

#include<algorithm> //for remove_if

void Scene::Update(float dt)
{
	//update

	for (auto& actor : m_actors)
	{
		actor->Update(dt);

		//if (randomf(0, 10) > 9)
		//{
		//	AddParticles(actor);
		//}
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


	//this next line can be done in the 2022 verson of c++
	std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });

	
	//for (Particle* particle : m_particles)
	//{
	//	particle->time += g_engine.GetTime().GetDeltaTime();
	//	if (particle->time >= 1.5)
	//	{
	//		particle->Update(g_engine.GetTime().GetDeltaTime());
	//		particle->time = 0;
	//	}
	//}


	//collision
	for (auto& actor1 : m_actors)
	{
		//collision
		for (auto& actor2 : m_actors)
		{
			if (actor1 == actor2 || actor1->m_destroyed || actor2->m_destroyed) continue; //skip the rest of the loop if they both pointers point to the same object

			//Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			//float distance = direction.Length();

			//float radius = actor1->m_model->GetRadius() + actor2->m_model->GetRadius();

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();
			float radius = actor1->GetRadius() + actor2->GetRadius();

			if (distance <= radius)
			{
				//getting here means that a collision has occured.
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}
		}
	}

}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors)
	{
		actor->Draw(renderer);
	}
	
	//for (Particle* particle : m_particles)
	//{
	//	particle->Draw(renderer);
	//}

	//for particle in particles, draw particle
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	m_actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	m_actors.clear();
}

//void Scene::AddParticles(Actor* actor)
//{
//	//Add particles here
//
//	float r = actor->GetTransform().rotation;
//
//	Vector2 location;
//	location.x = actor->GetTransform().position.x + actor->GetRadius();
//	location.y = actor->GetTransform().position.y;
//
//
//	Vector2 direction;
//	direction.x = 0;
//	direction.y = 1;
//
//
//
//	//Particle* p = { location, direction, randomf(1, 5), Color{0.0f, 0.3f, 1.0f} };
//	Particle p;
//	p.position = location;
//	p.velocity = direction;
//	p.lifespan = randomf(1, 5);
//	p.color = Color{ 0.0f, 0.3f, 1.0f };
//
//	
//	m_particles.push_back(&p);
//
//}
