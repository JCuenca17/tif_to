#include "Fisicas.h"
#include <limits>

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
    // Iterar sobre los vértices del polígono 1
    for (size_t i = 0; i < poly1.getVertexCount(); ++i) {
        // Obtener el vértice actual
        sf::Vector2f punto = poly1[i].position;

        // Verificar si el vértice está dentro del polígono 2
        if (puntoEnPoligono(punto, poly2)) {
            return true;  // Colisión detectada
        }
    }

    // Iterar sobre los vértices del polígono 2
    for (size_t i = 0; i < poly2.getVertexCount(); ++i) {
        // Obtener el vértice actual
        sf::Vector2f punto = poly2[i].position;

        // Verificar si el vértice está dentro del polígono 1
        if (puntoEnPoligono(punto, poly1)) {
            return true;  // Colisión detectada
        }
    }

    // No se detectó colisión
    return false;
}

bool fisicas::puntoEnPoligono(const sf::Vector2f& punto, const sf::VertexArray& poligono) {
    // Contador de intersecciones con las aristas del polígono
    int intersecciones = 0;

    // Iterar sobre las aristas del polígono
    for (size_t i = 0; i < poligono.getVertexCount(); ++i) {
        // Obtener los vértices de la arista
        sf::Vector2f v1 = poligono[i].position;
        sf::Vector2f v2 = poligono[(i + 1) % poligono.getVertexCount()].position;

        // Verificar si el punto está a la izquierda de la arista
        if ((v1.y > punto.y) != (v2.y > punto.y) &&
            punto.x < (v2.x - v1.x) * (punto.y - v1.y) / (v2.y - v1.y) + v1.x) {
            intersecciones++;
        }
    }

    // El punto está dentro del polígono si el número de intersecciones es impar
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
