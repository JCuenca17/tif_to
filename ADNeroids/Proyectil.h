#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>

class Proyectil : public Entity {
public:
	Proyectil(sf::Vector2f posicion, sf::Vector2f direccion, int color);
	void update(float deltaTime) override;

	void render(sf::RenderWindow& window) override;

	void pintarFigura(int color, sf::VertexArray& fig) override;

	void pintarFigura(int color, sf::CircleShape& fig);
private:
	sf::Vector2f direccion;
	sf::CircleShape figura;
	float lifetime;
};