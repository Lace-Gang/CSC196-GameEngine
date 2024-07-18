#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
//header files contain declarations, but not definitions

class Renderer
{
public:
	Renderer() = default;

	bool Initialize(); //return true or false if it was successfully initialized (good to return bool on anything that might fail so you can check
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);   //uint8_t "typedef unsigned char" (gives you only up to 255 (which is what we need
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);
	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	friend class Text;
private:
	SDL_Window* m_window{ nullptr }; //"m_" means a member of the class. Not required, but good convention
	SDL_Renderer* m_renderer{ nullptr };

	int m_width = 0;
	int m_height = { 0 };
};