#pragma once
#include "BaseNitrogenada.h"

class Timina : public BaseNitrogenada {
public:
	Timina(sf::Vector2f direccion = getRandomDirection(),
		sf::Vector2f posicion = getRandomPosition())
		: BaseNitrogenada(direccion, posicion, ROJO, 7) {

		figura[0].position = sf::Vector2f(0, 40);
		figura[1].position = sf::Vector2f(40, 20);
		figura[2].position = sf::Vector2f(40, -20);
		figura[3].position = sf::Vector2f(0, -40);
		figura[4].position = sf::Vector2f(-40, -20);
		figura[5].position = sf::Vector2f(-40, 20);
		figura[6].position = figura[0].position;

	}

	const sf::VertexArray& getVertexArray() override {
		return figura;
	}

	float getLife() override {
		return life;
	}
};

class Citosina : public BaseNitrogenada {
public:
	Citosina(sf::Vector2f direccion = getRandomDirection(),
		sf::Vector2f posicion = getRandomPosition())
		: BaseNitrogenada(direccion, posicion, AZUL, 7) {

		figura[0].position = sf::Vector2f(0, 40);
		figura[1].position = sf::Vector2f(40, 20);
		figura[2].position = sf::Vector2f(40, -20);
		figura[3].position = sf::Vector2f(0, -40);
		figura[4].position = sf::Vector2f(-40, -20);
		figura[5].position = sf::Vector2f(-40, 20);
		figura[6].position = figura[0].position;

	}

	const sf::VertexArray& getVertexArray() override {
		return figura;
	}

	float getLife() override {
		return life;
	}
};

class Adenina : public BaseNitrogenada {
public:
	Adenina(sf::Vector2f direccion = getRandomDirection(),
		sf::Vector2f posicion = getRandomPosition())
		: BaseNitrogenada(direccion, posicion, AMARILLO, 10) {

		figura[0].position = sf::Vector2f(0, 20);
		figura[1].position = sf::Vector2f(40, 50);
		figura[2].position = sf::Vector2f(80, 20);
		figura[3].position = sf::Vector2f(80, -20);
		figura[4].position = sf::Vector2f(40, -50);
		figura[5].position = sf::Vector2f(0, -20);
		figura[6].position = sf::Vector2f(-40, -40);
		figura[7].position = sf::Vector2f(-40, 0);
		figura[8].position = sf::Vector2f(40, 40);
		figura[9].position = figura[0].position;

	}

	const sf::VertexArray& getVertexArray() override {
		return figura;
	}

	float getLife() override {
		return life;
	}
};

class Guanina : public BaseNitrogenada {
public:
	Guanina(sf::Vector2f direccion = getRandomDirection(),
		sf::Vector2f posicion = getRandomPosition())
		: BaseNitrogenada(direccion, posicion, VERDE, 10) {

		figura[0].position = sf::Vector2f(0, 20);
		figura[1].position = sf::Vector2f(40, 50);
		figura[2].position = sf::Vector2f(80, 20);
		figura[3].position = sf::Vector2f(80, -20);
		figura[4].position = sf::Vector2f(40, -50);
		figura[5].position = sf::Vector2f(0, -20);
		figura[6].position = sf::Vector2f(-40, -40);
		figura[7].position = sf::Vector2f(-40, 0);
		figura[8].position = sf::Vector2f(40, 40);
		figura[9].position = figura[0].position;

	}

	const sf::VertexArray& getVertexArray() override {
		return figura;
	}

	float getLife() override {
		return life;
	}
};

class BaseNitrogenadaFactory {
public:
	static BaseNitrogenada* crearBaseNitrogenada(int type);
};

BaseNitrogenada* BaseNitrogenadaFactory::crearBaseNitrogenada(int type) {
	switch (type) {
	case 1:
		return new Timina();
	case 2:
		return new Citosina();
	case 3:
		return new Adenina();
	case 4:
		return new Guanina();
	default:
		return nullptr;
	}
}