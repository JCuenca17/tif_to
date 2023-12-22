#pragma once
#include <SFML/Graphics.hpp>

constexpr float VEL_PROYECTIL = 400.0f;
constexpr float DELAY = 0.4f;
constexpr float PROY_LIFE = 3.0f;

enum colores {
	AMARILLO,
	ROJO,
	VERDE,
	AZUL
};

class Entity {
public:
	Entity(sf::Vector2f posicion, float angulo, int color) :
		posicion(posicion), angulo(angulo), color(color) {
	}

	~Entity() {
		printf("Elemento eliminado");
	}


	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void pintarFigura(int color, sf::VertexArray& fig) = 0;

	sf::Vector2f posicion;
	float angulo;
	int color;
};