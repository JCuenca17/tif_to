#include "Jugador.h"
#include "Proyectil.h"
#include "Game.h"

Jugador::Jugador() 
	: Entity(sf::Vector2f(ANCHO / 2, ALTO / 2), 0, AMARILLO), figura(sf::Quads, 4), disparoTimer() {
	figura[0].position = sf::Vector2f(20, 0);
	figura[1].position = sf::Vector2f(-20, -20);
	figura[2].position = sf::Vector2f(-10, 0);
	figura[3].position = sf::Vector2f(-20, 20);

	pintarFigura(color, figura);
}

void Jugador::update(float deltaTime) {
	disparoTimer -= deltaTime;
	cambioProyectilTimer -= deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		angulo -= VEL_ANG * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		angulo += VEL_ANG * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		float radianes = angulo * (M_PI / 180.0f);

		posicion.x += cos(radianes) * VEL_JUG * deltaTime;
		posicion.y += sin(radianes) * VEL_JUG * deltaTime;

	}

	posicion.x = std::min(std::max(posicion.x, JUG_ANCHO / 2.0f), ANCHO - JUG_ANCHO / 2.0f);
	posicion.y = std::min(std::max(posicion.y, JUG_ALTO / 2.0f), ALTO - JUG_ALTO / 2.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && disparoTimer <= 0.0f) {
		disparoTimer = DELAY;
		float radianes = angulo * (M_PI / 180.0f);
		Game::toAddList.push_back(
			new Proyectil(posicion, sf::Vector2f(cos(radianes), sin(radianes)), color));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && cambioProyectilTimer <= 0.0f) {
		cambioProyectilTimer = CAMBIO_DELAY;
		if (color == AZUL)
			color = AMARILLO;
		else
			color++;
		pintarFigura(color, figura);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && cambioProyectilTimer <= 0.0f) {
		cambioProyectilTimer = CAMBIO_DELAY;
		if (color == AMARILLO)
			color = AZUL;
		else
			color--;
		pintarFigura(color, figura);
	}
}

void Jugador::render(sf::RenderWindow& window) {
	window.draw(figura, sf::Transform().translate(posicion).rotate(angulo));
}

void Jugador::pintarFigura(int color, sf::VertexArray& fig) {
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