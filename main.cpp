#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
//--------------------------------------------klasa postaci-----------------------------------------------------------
class postac
{
public:
	postac(sf::Vector2f posw)
	{
		tekturka.loadFromFile("postac.png");
		sprajt.setTexture(tekturka);
		sprajt.setPosition(posw);
		sprajt.setScale(2, 2);
	}
	sf::Sprite getPostac() { return sprajt; }
	sf::Vector2f getPosition() //do przerobienia jak juz bedzie gotowa postac zeby zwracalo srodek postaci
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
		//podstawy ruchu
		if (klawisz == sf::Keyboard::W)
		{
			if (predkosc.y > 0)
				predkosc.y = 0;
			if (predkosc.y > -2.5)
				predkosc.y -= 0.5;
		}
		if (klawisz == sf::Keyboard::A)
		{
			if (predkosc.x > 0)
				predkosc.x = 0;
			if (predkosc.x > -2.5)
				predkosc.x -= 0.5;
		}
		if (klawisz == sf::Keyboard::S)
		{
			if (predkosc.y < 0)
				predkosc.y = 0;
			if (predkosc.y < 2.5)
				predkosc.y += 0.5;
		}
		if (klawisz == sf::Keyboard::D)
		{
			if (predkosc.x < 0)
				predkosc.x = 0;
			if (predkosc.x < 2.5)
				predkosc.x += 0.5;
		}
		//ruch po skosie
		float suma = sqrt(predkosc.x * predkosc.x + predkosc.y * predkosc.y);
		if (suma > 2.5)
		{
			if (predkosc.x > 0 && predkosc.y > 0)
			{
				predkosc.x = 1.58;
				predkosc.y = 1.58;
			}
			if (predkosc.x > 0 && predkosc.y < 0)
			{
				predkosc.x = 1.58;
				predkosc.y = -1.58;
			}
			if (predkosc.x < 0 && predkosc.y > 0)
			{
				predkosc.x = -1.58;
				predkosc.y = 1.58;
			}
			if (predkosc.x < 0 && predkosc.y < 0)
			{
				predkosc.x = -1.58;
				predkosc.y = -1.58;
			}
		}
		//obsuga bezruchu
		if (klawisz == sf::Keyboard::O)
			predkosc.y = 0;
		if (klawisz == sf::Keyboard::P)
			predkosc.x = 0;

		sprajt.move(predkosc);
		//std::cout << "\npredkosc x: " << predkosc.x << "\npredkosc y: " << predkosc.y << "\nsuma: " << suma; //pomoc
	}
private:
	sf::Texture tekturka;
	sf::Sprite sprajt;
	sf::Vector2f predkosc = sf::Vector2f(0, 0), pozycja;
};
//------------------------------------------klasy przeciwnikow-------------------------------------------------------
class pajak1 // zwykly pajak chodzi i pije
{
public:
	pajak1(int poziom, sf::Vector2f postac)
	{
		//ilosc pajakow zalezna od poziomu pozycja postaci aby uniknac pojawiania sie w postaci
	}
	sf::Sprite getPostac() { return sprajt; }
	sf::Vector2f getPosition()//tutaj to samo pozycja srodka
	{
		pozycja = sprajt.getPosition();
		return pozycja;
	}
	void move(sf::Vector2f ruch)
	{
		sprajt.move(ruch);
	}
private:
	sf::Texture tekturka;
	sf::Sprite sprajt;
	sf::Vector2f predkosc = sf::Vector2f(0, 0), pozycja;
};
//--------------------------------------------klasa meniu-------------------------------------------------------------
class meniu
{
public:
	meniu()
	{

	}
private:
	sf::Font czcionka;
	sf::Text menu;
	int wybranaPozycja = 0;
};
//------------------------------------------------main-----------------------------------------------------------------
int main()
{
	//okno
	sf::RenderWindow window(sf::VideoMode(1600, 900), "proby mechanik");
	window.setFramerateLimit(60); 
	//nie musze robic zegarow kazdej animacji bo czas klatki jest staly ale gra sie pewnie zepsuje jak komputer bedzie niedomagal

	//postacie i mapa w grze
	postac ludzik(sf::Vector2f(window.getSize().x/2, window.getSize().y / 2));

	//menu i pomoc
	int wybrana_opcja = 0, poz_trudnosci = 0;
	sf::Texture pomoc, tlo;
	//petla
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		if (wybrana_opcja == 0) // wyswietlam meniu
		{
			//eeee
		}
		if (wybrana_opcja == 1 || wybrana_opcja == 2)// wyswietlam gre
		{
			if (wybrana_opcja == 2)
			{
				//wczytanie zapisu gra trwa dalej
			}
			else if (poz_trudnosci == 0)
			{
				//menu wyboru poziomu trudnosci
				
			}
			//poruszanie sie
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				ludzik.rusz(sf::Keyboard::W);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				ludzik.rusz(sf::Keyboard::S);
			else
				ludzik.rusz(sf::Keyboard::O);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				ludzik.rusz(sf::Keyboard::A);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				ludzik.rusz(sf::Keyboard::D);
			else
				ludzik.rusz(sf::Keyboard::P);
			//klawisze o i p sa uzyte jako klawisze braku aktywnosci
			window.draw(ludzik.getPostac());
		}


		window.display();
	}
	return 0;
}