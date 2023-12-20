#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <random>

constexpr float M_PI = 3.14159265f; //358979323846;

constexpr float const ANCHO = 1366.0f;
constexpr float const ALTO = 768.0f;

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
constexpr float BASE_SPAWN_TIME = 3.0f;

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


	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	sf::Vector2f posicion;
	float angulo;
	int color;
};

std::vector<Entity*> entidades{};
std::list<std::vector<Entity*> ::const_iterator> toRemoveList{};
std::list<Entity*> toAddList{};

class Proyectil : public Entity {
public:
	Proyectil(sf::Vector2f posicion, sf::Vector2f direccion, int color) : 
		figura(4.0f), direccion(direccion), Entity(posicion, 0.0f, color), lifetime(PROY_LIFE){
		pintarFigura(color, figura);
	
	}
	void update(float deltaTime) override {
		lifetime -= deltaTime;
		posicion += direccion * VEL_PROYECTIL * deltaTime;
		if (lifetime <= 0.0f) {
			toRemoveList.push_back(std::find(entidades.begin(), entidades.end(), this));
		}
	}

	void render(sf::RenderWindow& window) override {
		window.draw(figura, sf::Transform().translate(posicion));
	}

	void pintarFigura(int color, sf::CircleShape& fig) {
		if (color == AMARILLO) {
			figura.setFillColor(sf::Color::Yellow);
		}
		else if (color == ROJO) {
			figura.setFillColor(sf::Color::Red);
		}
		else if (color == VERDE) {
			figura.setFillColor(sf::Color::Green);
		}
		else if (color == AZUL) {
			figura.setFillColor(sf::Color::Blue);
		}
	}
private:
	sf::Vector2f direccion;
	sf::CircleShape figura;
	float lifetime;
};

class Jugador : public Entity {
public:
	Jugador() :
		Entity(sf::Vector2f(ANCHO / 2, ALTO / 2), 0, AMARILLO), figura(sf::Quads, 4), disparoTimer() {
		figura[0].position = sf::Vector2f(20, 0);
		figura[1].position = sf::Vector2f(-20, -20);
		figura[2].position = sf::Vector2f(-10, 0);
		figura[3].position = sf::Vector2f(-20, 20);

		pintarFigura(color, figura);
	}

	void update(float deltaTime) override{
		disparoTimer -= deltaTime;
		cambioProyectilTimer -= deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			angulo -= VEL_ANG * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			angulo += VEL_ANG * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			float radianes = angulo * (M_PI / 180.0f);

			posicion.x += cos(radianes) * VEL_JUG * deltaTime;
			posicion.y += sin(radianes) * VEL_JUG * deltaTime;

		}

		posicion.x = std::min(std::max(posicion.x, JUG_ANCHO / 2.0f), ANCHO - JUG_ANCHO / 2.0f);
		posicion.y = std::min(std::max(posicion.y, JUG_ALTO / 2.0f), ALTO - JUG_ALTO / 2.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && disparoTimer <= 0.0f) {
			disparoTimer = DELAY;
			float radianes = angulo * (M_PI / 180.0f);
			toAddList.push_back(
				new Proyectil(posicion, sf::Vector2f(cos(radianes), sin(radianes)), color));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && cambioProyectilTimer <= 0.0f) {
			cambioProyectilTimer = CAMBIO_DELAY;
			if (color == AZUL)
				color = AMARILLO;
			else
				color++;
			pintarFigura(color, figura);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && cambioProyectilTimer <= 0.0f) {
			cambioProyectilTimer = CAMBIO_DELAY;
			if (color == AMARILLO)
				color = AZUL;
			else
				color--;
			pintarFigura(color, figura);
		}
	}

	void render(sf::RenderWindow& window) override {
		window.draw(figura, sf::Transform().translate(posicion).rotate(angulo));
	}

	void pintarFigura(int color, sf::VertexArray & fig) {
		if (color == AMARILLO) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Yellow;
			}
		}
		else if (color == ROJO) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Red;
			}
		}
		else if (color == VERDE) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Green;
			}
		}
		else if (color == AZUL) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Blue;
			}
		}
	}

private:
	sf::VertexArray figura;
	float disparoTimer;
	float cambioProyectilTimer;
};

class BaseNitrogenada : public Entity {
public:
	BaseNitrogenada(sf::Vector2f direccion = BaseNitrogenada::getRandomDirection(),
		sf::Vector2f posicion = BaseNitrogenada::getRandomPosition())
		: Entity(posicion, 0, ROJO), direccion(direccion), figura(sf::LinesStrip, 6) {

		figura[0].position = sf::Vector2f(0, 60);
		figura[1].position = sf::Vector2f(60, 0);
		figura[2].position = sf::Vector2f(30, -60);
		figura[3].position = sf::Vector2f(-30, -60);
		figura[4].position = sf::Vector2f(-60, 0);
		figura[5].position = figura[0].position;

		pintarFigura(color, figura);
	}

	void update(float deltaTime) override {
		posicion += BASE_VEL * direccion * deltaTime;
		angulo += BASE_GIRO * deltaTime;

		if (posicion.x < BASE_ANCHO / 2.0f) {
			direccion.x = abs(direccion.x);
		}
		else if (posicion.x > ANCHO - BASE_ANCHO / 2.0f) {
			direccion.x = -abs(direccion.x);
		}

		if (posicion.y < BASE_ALTO / 2.0f) {
			direccion.y = abs(direccion.y);
		}
		else if (posicion.y > ALTO - BASE_ALTO / 2.0f) {
			direccion.y = -abs(direccion.y);
		}
	}

	void render(sf::RenderWindow& window) override {
		window.draw(figura, sf::Transform().translate(posicion).rotate(angulo));
	}

	void pintarFigura(int color, sf::VertexArray& fig) {
		if (color == AMARILLO) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Yellow;
			}
		}
		else if (color == ROJO) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Red;
			}
		}
		else if (color == VERDE) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Green;
			}
		}
		else if (color == AZUL) {
			for (size_t i = 0; i < figura.getVertexCount(); i++) {
				figura[i].color = sf::Color::Blue;
			}
		}
	}

	static sf::Vector2f getRandomDirection() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);

		float angulo = dist(gen);
		return sf::Vector2f(cos(angulo), sin(angulo));
	}

	static sf::Vector2f getRandomPosition() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> xAxis(BASE_ANCHO / 2.0f, ANCHO - BASE_ANCHO / 2.0f);
		std::uniform_real_distribution<float> yAxis(BASE_ALTO / 2.0f, ALTO - BASE_ALTO / 2.0f);

		return sf::Vector2f(xAxis(gen), yAxis(gen));
	}

private:
	sf::VertexArray figura;
	sf::Vector2f direccion;
};

int main() {
	sf::RenderWindow window(sf::VideoMode(unsigned int(ANCHO),unsigned int(ALTO)), "ADNeroids Game", sf::Style::Close | sf::Style::Titlebar);
	sf::Clock clock;

	entidades.push_back(new Jugador());

	float baseSpawnTime = BASE_SPAWN_TIME;

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		sf::Event e{};
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}

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

		window.display();
	}
}