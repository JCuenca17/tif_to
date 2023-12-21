#include "Game.h"
#include "BaseNitrogenada.h"
#include "Jugador.h"

// Public static
std::vector<Entity*> Game::entidades{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};
size_t Game::puntuacion{};
sf::SoundBuffer Game::disparoSoundBuffer{};
sf::Sound Game::disparoSonido{};

// Private static
float Game::baseSpawnTime{};
sf::Text Game::puntuacionText{};
sf::Text Game::continueText{};
sf::Font Game::fuente{};
bool Game::isGameOver{};
sf::Text Game::gameOverText{};

void Game::init() {
	fuente.loadFromFile("font.ttf");
	puntuacionText.setFont(fuente);
	puntuacionText.setPosition(sf::Vector2f(30, 20));
	puntuacionText.setCharacterSize(48);

	gameOverText.setFont(fuente);
	gameOverText.setPosition(sf::Vector2f(350, 350));
	gameOverText.setCharacterSize(128); 
	gameOverText.setString("Game Over!");

	continueText.setFont(fuente);
	continueText.setPosition(sf::Vector2f(450, 550));
	continueText.setCharacterSize(24);
	continueText.setString("Press Enter to continue...");

	disparoSoundBuffer.loadFromFile("shoot.wav");
	disparoSonido.setBuffer(disparoSoundBuffer);
}

void Game::begin() {
	isGameOver = false;
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

	puntuacionText.setString(std::to_string(puntuacion));
	window.draw(puntuacionText);

	if (isGameOver) {
		entidades.clear();
		puntuacion = 0;
		window.draw(gameOverText);
		window.draw(continueText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			begin();
		}
	}
}

void Game::gameOver() {
	isGameOver = true;
}
