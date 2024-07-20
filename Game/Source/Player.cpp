#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"

#include<iostream>

void Player::Update(float dt)
{
	//movement
	float thrust = 0;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegToRad(100) *dt;

	Vector2 acceleration = Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	
	//fire
	m_fireTimer -= dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE)&& m_fireTimer <= 0)
	{
		m_fireTimer = 0.2f;

		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });

		Model* model = new Model{ points, Color{ 1, 1, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		Bullet* bullet = new Bullet(400.0f, transform, model);
		bullet->SetTag("Bullet");
		bullet->SetLifespan(0.01f);
		m_scene->AddActor(bullet);
	}





	Actor :: Update(dt);



}

void Player::OnCollision(Actor* actor)
{
	//std::cout << "collision/n";
	if (actor->GetTag() == "Enemy")
	{
		m_destroyed = true;
	}

	if (actor->GetTag() == "Fish")
	{
		if (actor->GetTransform().scale > m_transform.scale)
		{
			m_destroyed = true;
		}
		
		if (actor->GetTransform().scale <= m_transform.scale)
		{
			m_transform.scale += (actor->GetTransform().scale / 2);
			actor->GetDestroyed() = true;
		}
			
	}
	
}
