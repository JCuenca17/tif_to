#pragma once
#include <SFML/Graphics.hpp>

namespace fisicas {
	bool intersecta(const sf::Vector2f& point, const sf::VertexArray& poligono);
	sf::VertexArray getTransformed(const sf::VertexArray& poligono, const sf::Transform& transform);
}
