#pragma once
#include <SFML/Graphics.hpp>

namespace fisicas {
	bool intersecta(const sf::Vector2f& point, const sf::VertexArray& poligono);
	bool intersecta(const sf::VertexArray& poly1, const sf::VertexArray& poly2);
	bool puntoEnPoligono(const sf::Vector2f& punto, const sf::VertexArray& poligono);

	sf::VertexArray getTransformed(const sf::VertexArray& poligono, const sf::Transform& transform);

}

