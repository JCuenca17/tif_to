#pragma once
#include "Entity.h"
#include "Global.h"

class BaseNitrogenada : public Entity {
public:
	BaseNitrogenada(sf::Vector2f direccion = BaseNitrogenada::getRandomDirection(),
		sf::Vector2f posicion = BaseNitrogenada::getRandomPosition());

	void update(float deltaTime) override;

	void render(sf::RenderWindow& window) override;

	void pintarFigura(int color, sf::VertexArray& fig);

	const sf::VertexArray& getVertexArray() const;

	static sf::Vector2f getRandomDirection();

	static sf::Vector2f getRandomPosition();

private:
	sf::VertexArray figura;
	sf::Vector2f direccion;
};

