#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"
#include "FishGame.h"

#include<iostream>

void Player::Update(float dt)
{
	//movement
	float thrust = 0;
	Vector2 direction{ 0,0 };

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x= -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegToRad(100) *dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) *dt;

	//strafing
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;

	//Vector2 acceleration = Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	
	//fire
	//m_fireTimer -= dt;
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE)&& m_fireTimer <= 0)
	//{
	//	m_fireTimer = 0.2f * m_fireModifier;
	//
	//
	//	//head minus tail (mouse position - our position)
	//	Vector2 direction = g_engine.GetInput().getMousePosition() - m_transform.position;
	//	float angle = direction.Angle();
	//
	//
	//	std::vector<Vector2> points;
	//	points.push_back(Vector2{ 5, 0 });
	//	points.push_back(Vector2{ -5, -5 });
	//	points.push_back(Vector2{ -5, 5 });
	//	points.push_back(Vector2{ 5, 0 });
	//
	//	Model* model = new Model{ points, Color{ 1, 1, 0 } };
	//	Transform transform{ m_transform.position, angle, 1.0f };
	//
	//	auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
	//	bullet->SetTag("Bullet");
	//	bullet->SetLifespan(0.01f);
	//	m_scene->AddActor(std::move(bullet));
	//}


	Actor :: Update(dt);



	if (m_velocity.Length() > 100)
	{
		if (randomf(0, 4) < 3) return;

		Particle::Data data
		{
			Vector2 {(randomf(m_transform.position.x - (this->GetRadius() / 4), m_transform.position.x + (this->GetRadius() / 2))), (randomf(m_transform.position.y - (this->GetRadius() / 2), m_transform.position.y + (this->GetRadius() / 2)))},//m_transform.position,
			Vector2{1,0}.Rotate(randomf(Math::TwoPi)) * 50,
			randomf(0.1f, 2.0f) * m_velocity.Length()/200,
			Color(255, 255, 255, 255)
		};
		g_engine.GetPS().AddParticle(data);
	}


}

void Player::OnCollision(Actor* actor)
{
	//std::cout << "collision/n";
	if (actor->GetTag() == "Enemy")
	{
		g_engine.GetAudio().PlaySound("crank.wav");
		m_transform.scale -= (actor->GetTransform().scale / 4);
		*m_score -= ((actor->GetTransform().scale) * 10);
		if (*m_score < 0) *m_score = 0;

		actor->GetDestroyed() = true;

		if (m_transform.scale <= 0.1)
		{
			dynamic_cast<FishGame*> (m_scene->GetGame())->OnPlayerDeath();
		}

	}

	if (actor->GetTag() == "Fish")
	{
		g_engine.GetAudio().PlaySound("crank.wav");

		if (actor->GetTransform().scale > m_transform.scale)
		{
			m_destroyed = true;
			//*m_isAlive = false;
			//if(*m_lives > 0) *m_lives = *m_lives - 1;

			dynamic_cast<FishGame*> (m_scene->GetGame())->OnPlayerDeath();
		}
		
		if (actor->GetTransform().scale <= m_transform.scale)
		{
			m_transform.scale += (actor->GetTransform().scale / 4);
			*m_score += ((actor->GetTransform().scale)*10);
			

			actor->GetDestroyed() = true;
		}
			
	}

	if (actor->GetTag() == "Life")
	{
		g_engine.GetAudio().PlaySound("crank.wav");
		dynamic_cast<FishGame*> (m_scene->GetGame())->AddLives();
		actor->GetDestroyed() = true;
	}
	
}
