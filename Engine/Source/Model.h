#pragma once

#include "Vector2.h"
#include"Color.h"
#include "Renderer.h"
#include "Transform.h"

#include <vector>

//it's okay to include std in a cpp, but NOT in a header (bad ettiquet)


class Model
{
public:
	Model() = default;
	Model(const std::vector<Vector2>& points, const Color& color) :
		m_points{ points },
		m_color{ color }
	{}


	void Draw(Renderer& renderer, const Vector2& position, float angle, float scale);
	void Draw(Renderer& renderer, const Transform transform);

	void Reverse();

private:
	std::vector<Vector2> m_points;
		Color m_color;
};
