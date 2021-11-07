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
	//ruch z klawiatury
	void rusz(sf::Keyboard::Key klawisz)
	{
		std::cout <<klawisz<<std::endl;
		if (klawisz == sf::Keyboard::W)
		{

		}
		if (klawisz == sf::Keyboard::A)
		{
			if (predkosc.x > 0)
				predkosc.x = 0;
			if (predkosc.x > -2)
				predkosc.x -= 0.1;
			sprajt.move(predkosc);
		}
		if (klawisz == sf::Keyboard::S)
		{

		}
		if (klawisz == sf::Keyboard::D)
		{
			if (predkosc.x < 0)
				predkosc.x = 0;
			if (predkosc.x < 2)
				predkosc.x += 0.1;
			sprajt.move(predkosc);
		}
	}
private:
	sf::Texture tekturka;
	sf::Sprite sprajt;
	sf::Vector2f predkosc = sf::Vector2f(0, 0), pozycja;
};


int main()
{
	//sf::Clock zegar;
	//sf::Time czas = zegar.getElapsedTime();

	sf::RenderWindow window(sf::VideoMode(1600, 900), "proby mechanik");
	//na dobry start ucze sie mechanik ktore moga sie przydac
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);
	postac ludzik(sf::Vector2f(0,200));

	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		//poruszanie sie
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			ludzik.rusz(sf::Keyboard::W);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			ludzik.rusz(sf::Keyboard::A);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			ludzik.rusz(sf::Keyboard::S);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			ludzik.rusz(sf::Keyboard::D);
		
		window.clear();
		window.draw(ludzik.getPostac());

		window.display();
	}
	return 0;
}