#include "Proyectil.h"
#include "Game.h"
#include "BaseNitrogenada.h"
#include "Fisicas.h"

Proyectil::Proyectil(sf::Vector2f posicion, sf::Vector2f direccion, int color) 
	: figura(4.0f), direccion(direccion), Entity(posicion, 0.0f, color), lifetime(PROY_LIFE) {
	pintarFigura(color, figura);
}

void Proyectil::update(float deltaTime) {
	lifetime -= deltaTime;
	posicion += direccion * VEL_PROYECTIL * deltaTime;
	if (lifetime <= 0.0f) {
		Game::toRemoveList.push_back(std::find(Game::entidades.begin(), Game::entidades.end(), this));
	}

	for (size_t i = 0; i < Game::entidades.size(); i++) {
		BaseNitrogenada* base = dynamic_cast<BaseNitrogenada*>(Game::entidades[i]);
		if (base != nullptr) {
			sf::Transform transform = sf::Transform()
				.translate(base->posicion)
				.rotate(base->angulo);
			
			// Logica de colision
			if (fisicas::intersecta(posicion,
				fisicas::getTransformed(base->getVertexArray(), transform))) {
				lifetime = 0.0f;
				
				// Logica de color
				if ((this->color == AMARILLO && base->color == ROJO) ||
					(this->color == ROJO && base->color == AMARILLO) ||
					(this->color == VERDE && base->color == AZUL) ||
					(this->color == AZUL && base->color == VERDE)) {

					Game::toRemoveList.push_back(
						std::find(Game::entidades.begin(), Game::entidades.end(), base));
					Game::puntuacion += 10;
				}
			}
		}
	}
}

void Proyectil::render(sf::RenderWindow& window) {
	window.draw(figura, sf::Transform().translate(posicion));
}

void Proyectil::pintarFigura(int color, sf::VertexArray& fig) {
	return;
}

void Proyectil::pintarFigura(int color, sf::CircleShape& fig) {
	if (color == AMARILLO) {
		figura.setFillColor(sf::Color::Yellow);
	}
	else if (color == ROJO) {
		figura.setFillColor(sf::Color::Red);
	}
	else if (color == VERDE) {
		figura.setFillColor(sf::Color::Green);
	}
	else if (color == AZUL) {
		figura.setFillColor(sf::Color::Blue);
	}
}