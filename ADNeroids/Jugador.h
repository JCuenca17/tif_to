#pragma once
#include "Entity.h"
#include "Global.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>

constexpr float JUG_ANCHO = 50.0f;
constexpr float JUG_ALTO = 40.0f;
constexpr float VEL_ANG = 200.0f;
constexpr float VEL_JUG = 200.0f;
constexpr float CAMBIO_DELAY = 0.2f;

class Jugador : public Entity {
public:
	Jugador();

	void update(float deltaTime) override;

	void render(sf::RenderWindow& window) override;

	void pintarFigura(int color, sf::VertexArray& fig);

	sf::VertexArray getFigura();

private:
	sf::VertexArray figura;
	float disparoTimer;
	float cambioProyectilTimer;
};