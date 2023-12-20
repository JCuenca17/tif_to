#include "BaseNitrogenada.h"
#include <random>

BaseNitrogenada::BaseNitrogenada(sf::Vector2f direccion, sf::Vector2f posicion)
	: Entity(posicion, 0, ROJO), direccion(direccion), figura(sf::LinesStrip, 6) {

	figura[0].position = sf::Vector2f(0, 60);
	figura[1].position = sf::Vector2f(60, 0);
	figura[2].position = sf::Vector2f(30, -60);
	figura[3].position = sf::Vector2f(-30, -60);
	figura[4].position = sf::Vector2f(-60, 0);
	figura[5].position = figura[0].position;

	pintarFigura(color, figura);
}

void BaseNitrogenada::update(float deltaTime) {
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
	std::uniform_real_distribution<float> xAxis(BASE_ANCHO / 2.0f, ANCHO - BASE_ANCHO / 2.0f);
	std::uniform_real_distribution<float> yAxis(BASE_ALTO / 2.0f, ALTO - BASE_ALTO / 2.0f);

	return sf::Vector2f(xAxis(gen), yAxis(gen));
}