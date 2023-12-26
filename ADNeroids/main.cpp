#include "Game.h"
#include "Global.h"
#include "Fisicas.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(ANCHO,ALTO), "ADNeroids Game", sf::Style::Close | sf::Style::Titlebar);
	sf::Clock clock;

	sf::VertexArray poly1(sf::LinesStrip);
	sf::VertexArray poly2(sf::LinesStrip);

	enum { POLY_1, POLY_2, TEST } state = POLY_1;

	Game::init();
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