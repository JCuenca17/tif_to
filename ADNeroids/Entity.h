#pragma once
#include <SFML/Graphics.hpp>

constexpr float JUG_ANCHO = 50.0f;
constexpr float JUG_ALTO = 40.0f;
constexpr float VEL_ANG = 200.0f;
constexpr float VEL_JUG = 200.0f;
constexpr float CAMBIO_DELAY = 0.2f;

constexpr float VEL_PROYECTIL = 400.0f;
constexpr float DELAY = 0.2f;
constexpr float PROY_LIFE = 3.0f;

constexpr float BASE_ANCHO = 120.0f;
constexpr float BASE_ALTO = 120.0f;
constexpr float BASE_GIRO = 30.0f;
constexpr float BASE_VEL = 100.0f;
constexpr float BASE_SPAWN_TIME = 10.0f;

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

	sf::Vector2f posicion;
	float angulo;
	int color;
};