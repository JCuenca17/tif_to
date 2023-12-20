#include "Fisicas.h"

bool fisicas::intersecta(const sf::Vector2f& point, const sf::VertexArray& poligono) {
	size_t n = poligono.getVertexCount() - 1;
	size_t intersecciones = 0;
	sf::Vector2f figEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);
	for (size_t i = 0; i < n; i++) {
		//Transformacion
		sf::Vector2f p1 = poligono[i].position;
		sf::Vector2f p2 = poligono[i + 1].position;

		if ((p1.y < point.y && p2.y >= point.y) ||
			(p2.y < point.y && p1.y >= point.y)) {
			float t = (point.y - p1.y) / (p2.y - p1.y);
			float interseccionX = p1.x + t * (p2.x - p1.x);

			if (interseccionX <= point.x && interseccionX <= figEnd.x) {
				intersecciones++;
			}
		}
	}

	return intersecciones % 2 == 1;
	
}

sf::VertexArray fisicas::getTransformed(const sf::VertexArray& poligono,
	const sf::Transform& transform) {
	sf::VertexArray transformed = poligono;

	for (size_t i = 0; i < transformed.getVertexCount(); i++) {
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}
