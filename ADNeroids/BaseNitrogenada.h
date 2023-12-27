#pragma once
#include "Entity.h"
#include "Global.h"

constexpr float BASE_ANCHO = 80.0f;
constexpr float BASE_ALTO = 80.0f;
constexpr float BASE_GIRO = 30.0f;
constexpr float BASE_VEL = 120.0f;
constexpr float BASE_HIT_TIME = 1.0f;
constexpr float BASE_SPAWN_TIME = 3.0f;

class BaseNitrogenada : public Entity {
public:

	BaseNitrogenada(sf::Vector2f direccion, sf::Vector2f posicion, int color, int ladosFigura)
		: Entity(posicion, 0, color), direccion(direccion), figura(sf::LinesStrip, ladosFigura), life() {
		pintarFigura(color, figura);
	}

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void pintarFigura(int color, sf::VertexArray& fig) override;
	virtual const sf::VertexArray& getVertexArray() = 0;
	virtual float getLife() = 0;

	// Funciones auxiliares
	static sf::Vector2f getRandomDirection();
	static sf::Vector2f getRandomPosition();

protected:
	sf::VertexArray figura;
	sf::Vector2f direccion;

	float life;
};