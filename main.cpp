#include <SFML/Graphics.hpp>
#include <iostream>

class postac
{
public:
	postac(sf::Vector2f posw)
	{
		tekturka.loadFromFile("postac.png");
		sprajt.setTexture(tekturka);
		sprajt.setPosition(posw);
		sprajt.setScale(4, 4);
	}
	sf::Sprite getPostac() { return sprajt; }
	sf::Vector2f getPosition() 
	{
		pozycja = sprajt.getPosition();
		return pozycja;
	}
	void move(sf::Vector2f ruch)
	{
		sprajt.move(ruch);
	}
	sf::Clock zegar;
	sf::Time czas = zegar.getElapsedTime();
	int poprzedni_klawisz = sf::Keyboard::Down;
	void rusz(sf::Keyboard::Key klawisz)
	{
		if (klawisz == poprzedni_klawisz)
		{
			
		}
		else {
			zegar.restart();
			poprzedni_klawisz = klawisz;
		}
		if (klawisz == 72)
			sprajt.move(1, 0);
		if (klawisz == 71)
			sprajt.move(-1, 0);
	}
private:
	sf::Texture tekturka;
	sf::Sprite sprajt;
	sf::Vector2f predkosc, pozycja;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "proby mechanik");
	//na dobry start ucze sie mechanik ktore moga sie przydac
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);
	postac ludzik(sf::Vector2f(0,200));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			std::cout << "kod: " << event.key.code << std::endl;
			/*if (event.key.code == sf::Keyboard::Up)
				ludzik.move(sf::Vector2f(0, -1));
			if (event.key.code == sf::Keyboard::Right)
				ludzik.move(sf::Vector2f(0.5, 0));
			if (event.key.code == sf::Keyboard::Left)
				ludzik.move(sf::Vector2f(-1, 0));
			if (event.key.code == sf::Keyboard::Down)
				ludzik.move(sf::Vector2f(0, 1));*/
			ludzik.rusz(event.key.code);
		}
		
		window.clear();
		window.draw(ludzik.getPostac());
		window.display();
	}
	return 0;
}