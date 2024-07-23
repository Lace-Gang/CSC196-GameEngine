#include "Particle.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);

	if (lifespan != 0)
	{
		lifespan -= dt;
	}
	if (lifespan <= 0) isActive = false;
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0)
	{
		//renderer.SetColor(color.red, color.green, color.blue, color.alpha);
		renderer.SetColor((uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a);
		renderer.DrawPoint(position.x, position.y);
		//renderer.DrawRect(position.x, position.y, 4.0f, 4.0f); //change this to draw circle
		//renderer.DrawCircle(position.x, position.y, 20);
	}
}

void Particle::Initialize(const Data& data)
{
	isActive = true;
	position = data.position;
	velocity = data.velocity;
	lifespan = data.lifespan;
	color = data.color;
}

