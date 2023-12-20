#include "Game.h"
#include "BaseNitrogenada.h"
#include "Jugador.h"

// Public static
std::vector<Entity*> Game::entidades{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};
size_t Game::puntuacion{};
std::unordered_map<std::string, sf::SoundBuffer> Game::soundBuffers;

// Private static
float Game::baseSpawnTime{};
sf::Text Game::puntuacionText{};
sf::Font Game::fuente{};

void Game::begin() {
	fuente.loadFromFile("font.ttf");
	puntuacionText.setFont(fuente);
	puntuacionText.setPosition(sf::Vector2f(30, 20));
	puntuacionText.setCharacterSize(48);

	entidades.push_back(new Jugador());
	float baseSpawnTime = BASE_SPAWN_TIME;

	soundBuffers["shoot"].loadFromFile("shoot.wav");
}

void Game::update(sf::RenderWindow& window, float deltaTime) {
	toAddList.clear();
	toRemoveList.clear();
	window.clear();

	baseSpawnTime -= deltaTime;

	for (size_t i = 0; i < entidades.size(); i++) {
		entidades[i]->update(deltaTime);
		entidades[i]->render(window);
	}

	for (const auto& it : toRemoveList) {
		delete* it;
		entidades.erase(it);
	}

	for (auto& ptr : toAddList) {
		entidades.push_back(ptr);
	}

	if (baseSpawnTime <= 0.0f) {
		entidades.push_back(new BaseNitrogenada());
		baseSpawnTime = BASE_SPAWN_TIME;
	}

	puntuacionText.setString(std::to_string(puntuacion));
	window.draw(puntuacionText);
}
