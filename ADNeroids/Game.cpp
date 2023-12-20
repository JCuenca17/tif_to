#include "Game.h"
#include "BaseNitrogenada.h"
#include "Jugador.h"


std::vector<Entity*> Game::entidades{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};
float Game::baseSpawnTime{};

void Game::begin() {
	entidades.push_back(new Jugador());
	float baseSpawnTime = BASE_SPAWN_TIME;
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
}
