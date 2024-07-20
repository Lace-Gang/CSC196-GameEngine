#include "Fish.h"


void Fish::Update(float dt)
{
	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;
	if (m_transform.position.x > m_scope) m_destroyed = true;

	Actor::Update(dt);
}

void Fish::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player" && actor->GetTransform().scale < m_transform.scale)
	{
		m_transform.scale += (actor->GetTransform().scale / 4);
	}
}
