#pragma once
#include "Entity.h"
#include "Global.h"

constexpr float BASE_ANCHO = 80.0f;
constexpr float BASE_ALTO = 80.0f;
constexpr float BASE_GIRO = 30.0f;
constexpr float BASE_VEL = 100.0f;
constexpr float BASE_HIT_TIME = 2.0f;
constexpr float BASE_SPAWN_TIME = 5.0f;

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

	float getLife() { return life; }

private:
	sf::VertexArray figura;
	sf::Vector2f direccion;

	float life;
};

