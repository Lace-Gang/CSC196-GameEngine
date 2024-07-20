#pragma once

#include "Renderer.h" //put our own includes before system includes
#include "Input.h"
#include "Audio.h"

#include "Vector2.h"
#include "Particle.h"
#include "Model.h"

#include "Random.h"
#include "ETimer.h"
#include "Color.h"
#include "MathUtils.h"
#include "Transform.h"
#include "ETimer.h"

#include <SDL.h>
#include <fmod.hpp>

//#define RENDERER g_engine.GetRenderer() //these are unpopular due to being "violent". It does make things look nicer though (RENDERER can be put in place of g_engine.GetRenderer() in places

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	Time* m_time{ nullptr };

	Renderer* m_renderer{ nullptr }; //want to put this on heap
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };


};


extern Engine g_engine; 
//(g_(thing) is the standard naming convention here) This makes it global
//extern is the variable version of inline (so that you don't get repeated definition errors)