#include "Jugador.h"
#include "Proyectil.h"
#include "Game.h"
#include "Fisicas.h"
#include "BaseNitrogenada.h"
#include "Global.h"
#include <cmath>

Jugador::Jugador() 
	: Entity(sf::Vector2f(ANCHO / 2, ALTO / 2), 0, AMARILLO),
	figura(sf::LinesStrip, 4),
	disparoTimer(),
	acelerando(false),
	velocidadActual(0.0f),
	velocidadMaxima(VEL_JUG),
	direccionActual(sf::Vector2f(0,0)) {
	figura[0].position = sf::Vector2f(30, 0);
	figura[1].position = sf::Vector2f(-20, -20);
	figura[2].position = sf::Vector2f(-20, 20);
	figura[3].position = figura[0].position;

	pintarFigura(color, figura);
}

void Jugador::update(float deltaTime) {
	disparoTimer -= deltaTime;
	cambioProyectilTimer -= deltaTime;

	// Declarar la variable direccionMovimiento al principio de la función
	sf::Vector2f direccionMovimiento;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		angulo -= VEL_ANG * deltaTime;
		velocidadActual -= VEL_DESACEL_GIRO * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		angulo += VEL_ANG * deltaTime;
		velocidadActual -= VEL_DESACEL_GIRO * deltaTime;
	}

	// Calcular la dirección de movimiento independientemente de si se presiona "Up"
	float radianes = angulo * (M_PI / 180.0f);
	direccionMovimiento = sf::Vector2f(cos(radianes), sin(radianes));

	// Solo actualiza la dirección de movimiento cuando se presiona "Up"
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		acelerando = true;
		velocidadActual += VEL_JUG * deltaTime;
		if (velocidadActual > velocidadMaxima) {
			velocidadActual = velocidadMaxima;
		}

		direccionActual.x = direccionMovimiento.x;
		direccionActual.y = direccionMovimiento.y;

		// Actualiza la posición con la dirección de movimiento actual
		posicion.x += direccionMovimiento.x * velocidadActual * deltaTime;
		posicion.y += direccionMovimiento.y * velocidadActual * deltaTime;
	}
	else {
		acelerando = false;

		// Desaceleración gradual
		velocidadActual -= VEL_DESACEL * deltaTime;
		if (velocidadActual < 0.0f) {
			velocidadActual = 0.0f;
		}

		// Actualiza la posición con la dirección de movimiento actual
		posicion.x += direccionActual.x * velocidadActual * deltaTime;
		posicion.y += direccionActual.y * velocidadActual * deltaTime;
	}

	// Restringir la posición dentro de los límites de la pantalla
	posicion.x = std::min(std::max(posicion.x, JUG_ANCHO / 2.0f), ANCHO - JUG_ANCHO / 2.0f);
	posicion.y = std::min(std::max(posicion.y, JUG_ALTO / 2.0f), ALTO - JUG_ALTO / 2.0f);

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && disparoTimer <= 0.0f) {
		Game::disparoSonido.play();
		disparoTimer = DELAY;
		float radianes = angulo * (M_PI / 180.0f);
		Game::toAddList.push_back(
			new Proyectil(posicion, sf::Vector2f(cos(radianes), sin(radianes)), color));
	}

	/*for (size_t i = 0; i < figura.getVertexCount(); ++i) {
		std::cout << "Vértice " << i << ": x = " << figura[i].position.x << ", y = " << figura[i].position.y << std::endl;
	}*/


	sf::Transform jugadorTransform = sf::Transform().translate(posicion).rotate(angulo);

	for (size_t i = 0; i < Game::entidades.size(); i++) {
		BaseNitrogenada* base = dynamic_cast<BaseNitrogenada*>(Game::entidades[i]);
		if (base != nullptr && base->getLife() >= BASE_HIT_TIME) {
			sf::Transform baseTransform = sf::Transform()
				.translate(base->posicion)
				.rotate(base->angulo);

			// Lógica de colisión
			if (fisicas::intersecta(fisicas::getTransformed(figura, jugadorTransform),
				fisicas::getTransformed(base->getVertexArray(), baseTransform))) {
				Game::gameOver();
			}
		}
	}
}

void Jugador::render(sf::RenderWindow& window) {
	window.draw(figura, sf::Transform().translate(posicion).rotate(angulo));

	// Dibujar llamas de aceleración
	if (acelerando) {
		sf::VertexArray llamas(sf::Triangles, 3);
		llamas[0].position = sf::Vector2f(-25, 0);
		llamas[1].position = sf::Vector2f(-30, 10);
		llamas[2].position = sf::Vector2f(-30, -10);
		llamas[0].color = sf::Color::Red;
		llamas[1].color = sf::Color::Yellow;
		llamas[2].color = sf::Color::White;

		window.draw(llamas, sf::Transform().translate(posicion).rotate(angulo));
	}
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

sf::VertexArray Jugador::getFigura() {
	return sf::VertexArray();
}
