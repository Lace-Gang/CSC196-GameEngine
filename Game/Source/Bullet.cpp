#include "Bullet.h"
#include "Engine.h"
#include "Color.h"

void Bullet::Update(float dt)
{
	m_velocity = Vector2{ 1, 0}.Rotate(m_transform.rotation) * m_speed;
	Actor::Update(dt);

	//create particle trail
	Particle::Data data
	{
		m_transform.position,
		Vector2{1,0}.Rotate(randomf(Math::TwoPi)) * 50,
		randomf(0.5f, 2.0f),
		Color(255, 255, 255, 255)
	};
	g_engine.GetPS().AddParticle(data);
}

void Bullet::OnCollision(Actor* actor)
{
}
