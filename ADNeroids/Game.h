#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <list>
#include "Entity.h"

class Game {
public:
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static std::vector<Entity*> entidades;
	static std::list<std::vector<Entity*> ::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	static size_t puntuacion;
	static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
private:
	static float baseSpawnTime;
	static sf::Text puntuacionText;
	static sf::Font fuente;

};

