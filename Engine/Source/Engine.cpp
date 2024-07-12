#include "Engine.h"

Engine g_engine;
//Engine Engine::ms_engine; (to do a static member variable of the class) (must be declared in the header too. kinda a lot of trouble though

bool Engine::Initialize()
{
    m_renderer = new Renderer();
    m_input = new Input();
    m_audio = new Audio();

    //(*m_renderer).Initialize(); same thing as the arrow below
    m_renderer->Initialize(); //the shorthand
    m_renderer->CreateWindow("Game Engine", 800, 600);
    m_input->Initialize();
    m_audio->Initialize();

    return true;
}

void Engine::Shutdown()
{
    m_renderer->Shutdown();
    m_input->Shutdown();
    m_audio->Shutdown();
}

void Engine::Update()
{
    m_input->Update();
    m_input->Update();
}
