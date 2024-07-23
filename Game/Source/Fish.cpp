#include "Fish.h"
#include "Engine.h"
#include "Vector2.h"



void Fish::Update(float dt)
{
	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;
	if (m_transform.position.x > m_scope) m_destroyed = true;

	Actor::Update(dt);

	if (m_velocity.Length() > 100)
	{
		if (randomf(0, 4) < 3) return;

		//Vector2 location;
		//location.x = m_transform.position.x + GetRadius();
		//location.y = m_transform.position.y;


		Particle::Data data
		{

			Vector2 {(randomf(m_transform.position.x - (this->GetRadius() / 4), m_transform.position.x + (this->GetRadius() / 2))), (randomf(m_transform.position.y - (this->GetRadius()/2), m_transform.position.y + (this->GetRadius()/2)))}, //m_transform.position,
			Vector2{1,0}.Rotate(randomf(Math::TwoPi)) * 50,   
			randomf(0.1f, 2.0f) * m_velocity.Length() / 200,
			Color(255, 255, 255, 255)
		};
		g_engine.GetPS().AddParticle(data);
	}
}

void Fish::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player" && actor->GetTransform().scale < m_transform.scale)
	{
		m_transform.scale += (actor->GetTransform().scale / 4);
	}
}
