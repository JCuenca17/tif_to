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

bool fisicas::intersecta(const sf::VertexArray& poly1, const sf::VertexArray& poly2) {
	size_t n1 = poly1.getVertexCount() - 1;
	size_t n2 = poly2.getVertexCount() - 1;

	for (size_t i = 0; i < n1; i++) {
		sf::Vector2f esquina = poly1[i].position - poly1[(i + 1) % n1].position;
		sf::Vector2f normal(-esquina.y, esquina.x);

		// Normalizando el vector
		float length = sqrt(normal.x * normal.x + normal.y * normal.y);
		normal /= length;

		// Limites
		float min1 = std::numeric_limits<float>::max();
		float max1 = std::numeric_limits<float>::min();
		float min2 = std::numeric_limits<float>::max();
		float max2 = std::numeric_limits<float>::min();

		for (size_t j = 0; j < n1; j++) {
			float proyeccion = poly1[j].position.x * normal.x + poly1[j].position.y * normal.y;
			min1 = std::min(min1, proyeccion);
			max1 = std::max(max1, proyeccion);
		}
		
		for (size_t j = 0; j < n2; j++) {
			float proyeccion = poly2[j].position.x * normal.x + poly2[j].position.y * normal.y;
			min2 = std::min(min2, proyeccion);
			max2 = std::max(max2, proyeccion);
		}

		if (max1 < min2 || max2 < min1) {
			return false;
		}

	}

	return true;
}

sf::VertexArray fisicas::getTransformed(const sf::VertexArray& poligono,
	const sf::Transform& transform) {
	sf::VertexArray transformed = poligono;

	for (size_t i = 0; i < transformed.getVertexCount(); i++) {
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}
