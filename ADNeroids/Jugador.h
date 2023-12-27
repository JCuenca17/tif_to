#pragma once
#include "Entity.h"
#include "Global.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>

constexpr float JUG_ANCHO = 50.0f;
constexpr float JUG_ALTO = 40.0f;
constexpr float VEL_ANG = 200.0f;
constexpr float VEL_JUG = 600.0f;
constexpr float CAMBIO_DELAY = 0.2f;
constexpr float VEL_DESACEL = 50.0f;
constexpr float VEL_DESACEL_GIRO = 100.0f;

class Jugador : public Entity {
public:
	Jugador();

	void update(float deltaTime) override;

	void render(sf::RenderWindow& window) override;

	void pintarFigura(int color, sf::VertexArray& fig) override;

	sf::VertexArray getFigura();

private:
	sf::VertexArray figura;
	float disparoTimer;
	float cambioProyectilTimer;
	bool acelerando;  // Bandera para verificar si el jugador está acelerando
	float velocidadActual;  // Velocidad actual del jugador
	float velocidadMaxima;  // Velocidad máxima permitida
	sf::Vector2f direccionActual;
};