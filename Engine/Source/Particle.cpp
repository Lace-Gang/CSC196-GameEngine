#include "Particle.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);

	if (lifespan != 0)
	{
		lifespan -= dt;
	}
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0)
	{
		//renderer.SetColor(color.red, color.green, color.blue, color.alpha);
		renderer.SetColor((uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a);
		renderer.DrawPoint(position.x, position.y);
		renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
	}
}

