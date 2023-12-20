#pragma once
#include "Entity.h"
#include "Global.h"

class Jugador : public Entity {
public:
	Jugador();

	void update(float deltaTime) override;

	void render(sf::RenderWindow& window) override;

	void pintarFigura(int color, sf::VertexArray& fig);

private:
	sf::VertexArray figura;
	float disparoTimer;
	float cambioProyectilTimer;
};