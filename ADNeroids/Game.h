#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <list>
#include "Entity.h"

class Game {
public:
	static void init();
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static void gameOver();

	static std::vector<Entity*> entidades;
	static std::list<std::vector<Entity*> ::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	static size_t puntuacion;

	//Disparo Sound
	static sf::SoundBuffer disparoSoundBuffer;
	static sf::Sound disparoSonido;

	//Aceleracion Sound
	static sf::SoundBuffer aceleracionSoundBuffer;
	static sf::Sound aceleracionSonido;
	
	// Explosion Sonido
	static sf::SoundBuffer explosionSoundBuffer;
	static sf::Sound explosionSonido;

	
private:
	static float baseSpawnTime;
	static size_t highScore;

	static sf::Text puntuacionText;
	static sf::Text gameOverText;
	static sf::Text continueText;
	static sf::Text highScoreText;
	static sf::Text titleText;
	static sf::Text menuText;
	static sf::Text playText;
	static sf::Font fuente;

	static enum State { MENU, PLAYING, GAME_OVER} state;

};

