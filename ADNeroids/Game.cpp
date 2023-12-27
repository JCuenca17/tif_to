#include "Game.h"
#include "BaseNitrogenada.h"
#include "Jugador.h"
#include "Bases.h"
#include <random>
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
sf::Text Game::gameOverText{};
Game::State Game::state{};
sf::Text Game::titleText{};
sf::Text Game::menuText;
sf::Text Game::playText;

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
	
	menuText.setFont(fuente);
	menuText.setPosition(sf::Vector2f(430, 650));
	menuText.setCharacterSize(24);
	menuText.setString("Press ESCAPE to exit to menu...");

	titleText.setFont(fuente);
	titleText.setPosition(sf::Vector2f(350, 350));
	titleText.setCharacterSize(128);
	titleText.setString("ADNEROIDS");

	playText.setFont(fuente);
	playText.setPosition(sf::Vector2f(550, 550));
	playText.setCharacterSize(24);
	playText.setString("Press Enter to Play");

	disparoSoundBuffer.loadFromFile("shoot.wav");
	disparoSonido.setBuffer(disparoSoundBuffer);

	state = MENU;
}

void Game::begin() {
	state = PLAYING;
	entidades.push_back(new Jugador());
	float baseSpawnTime = BASE_SPAWN_TIME;
	puntuacion = 0;
}

void Game::update(sf::RenderWindow& window, float deltaTime) {

	if (state == MENU) {
		window.draw(titleText);
		window.draw(playText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			begin();
		}
		return;
	}

	toAddList.clear();
	toRemoveList.clear();
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

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(1, 4);

		int tipoBase = dist(gen); // Genera un número aleatorio entre 1 y 4
		// 1 -> timina
		// 2 -> citosina
		// 3 -> adenina
		// 4 -> guanina
		BaseNitrogenada* nuevaBase = dynamic_cast<BaseNitrogenada*>(BaseNitrogenadaFactory::createEntity(tipoBase));
		entidades.push_back(nuevaBase);
		baseSpawnTime = BASE_SPAWN_TIME;
	}

	puntuacionText.setString(std::to_string(puntuacion));
	window.draw(puntuacionText);

	if (state == GAME_OVER) {
		entidades.clear();
		puntuacion = 0;
		window.draw(gameOverText);
		window.draw(continueText);
		window.draw(menuText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			puntuacion = 0;
			begin();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			state = MENU;
		}

	}
}

void Game::gameOver() {
	state = GAME_OVER;
}
