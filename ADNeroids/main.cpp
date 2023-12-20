#include "Game.h"
#include "Global.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(unsigned int(ANCHO),unsigned int(ALTO)), "ADNeroids Game", sf::Style::Close | sf::Style::Titlebar);
	sf::Clock clock;

	Game::begin();

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		sf::Event e{};
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}
		Game::update(window, deltaTime);
		window.display();
	}
}