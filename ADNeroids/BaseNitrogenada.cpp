#include "BaseNitrogenada.h"
#include <random>

void BaseNitrogenada::update(float deltaTime) {
	life += deltaTime;

	posicion += BASE_VEL * direccion * deltaTime;
	angulo += BASE_GIRO * deltaTime;

	if (posicion.x < BASE_ANCHO / 2.0f) {
		direccion.x = abs(direccion.x);
	}
	else if (posicion.x > ANCHO - BASE_ANCHO / 2.0f) {
		direccion.x = -abs(direccion.x);
	}

	if (posicion.y < BASE_ALTO / 2.0f) {
		direccion.y = abs(direccion.y);
	}
	else if (posicion.y > ALTO - BASE_ALTO / 2.0f) {
		direccion.y = -abs(direccion.y);
	}
}

void BaseNitrogenada::render(sf::RenderWindow& window) {
	window.draw(figura, sf::Transform().translate(posicion).rotate(angulo));
}

void BaseNitrogenada::pintarFigura(int color, sf::VertexArray& fig) {
	if (color == AMARILLO) {
		for (size_t i = 0; i < figura.getVertexCount(); i++) {
			figura[i].color = sf::Color::Yellow;
		}
	}
	else if (color == ROJO) {
		for (size_t i = 0; i < figura.getVertexCount(); i++) {
			figura[i].color = sf::Color::Red;
		}
	}
	else if (color == VERDE) {
		for (size_t i = 0; i < figura.getVertexCount(); i++) {
			figura[i].color = sf::Color::Green;
		}
	}
	else if (color == AZUL) {
		for (size_t i = 0; i < figura.getVertexCount(); i++) {
			figura[i].color = sf::Color::Blue;
		}
	}
}

sf::Vector2f BaseNitrogenada::getRandomDirection() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);

	float angulo = dist(gen);
	return sf::Vector2f(cos(angulo), sin(angulo));
}

sf::Vector2f BaseNitrogenada::getRandomPosition() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> xAxis(BASE_ANCHO, ANCHO);
	std::uniform_real_distribution<float> yAxis(BASE_ALTO, ALTO);

	float x = xAxis(gen); 
	float y = yAxis(gen);

	while (x > ANCHO * .3 && x < ANCHO * .7) {
		x = xAxis(gen);
	}

	while (x > ANCHO * .3 && x < ANCHO * .7) {
		y = yAxis(gen);
	}

	return sf::Vector2f(x,y);
}