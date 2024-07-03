#pragma once

#include "Vector2.h"
#include "Renderer.h"
#include "Color.h"


struct Particle
{
	Vector2 position{ 0, 0 }; //sets the default in a nice shorthand way
	Vector2 velocity{ 0, 0 };
	float lifespan{ 0}; //this works just as well as "=0" would
	Color color{ 255, 255, 255, 0 };
	


	Particle() = default; //default constructor

	Particle(Vector2 position, Vector2 velocity) : position{ position }, velocity{ velocity }{} //this is a nice modern fast way to write a constructor (the : is very important)

	Particle(Vector2 position, Vector2 velocity, float lifespan) : position{ position }, velocity{ velocity }, lifespan{lifespan} {}

	Particle(Vector2 position, Vector2 velocity, float lifespan, Color color) : position{ position }, velocity{ velocity }, lifespan{ lifespan }, color{ color } {}


	void Update(float dt); //dt = delta time (change in time) which means here "how much time has passed since the last frame
	void Draw(Renderer& renderer); //& so that it doesn't make a new renderer and just passes the address (as things like a renderer can be rather large)
};