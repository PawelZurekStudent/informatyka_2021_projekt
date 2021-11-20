#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
//--------------------------------------------pomocne funkcje----------------------------------------------------------
bool sprawdz_myszke(sf::Vector2i myszka, sf::Vector2f pole, sf::Vector2f rozmiar)
{
	//std::cout << myszka.x << " " << pole.x << "\n";
	if (myszka.y > pole.y && myszka.y < pole.y + rozmiar.y)
		return true;
	else
		return false;
}
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
	pajak1()
	{
		tekturka.loadFromFile("pajak1.png");
	}
	void tworz(int poziom, sf::Vector2f pos_gracz)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		ilosc = poziom;
		pajak1T = new sf::Sprite[ilosc];
		for (int i = 0; i < ilosc; i++)
		{
			pajak1T[i].setTexture(tekturka);
			pajak1T[i].setPosition(sf::Vector2f(gen() % 1600, gen() % 900));
		}
	}
	void rysuj(sf::RenderWindow& okno)
	{
		for (int i = 0; i < ilosc; i++)
		{
			okno.draw(pajak1T[i]);
		}
	}
	void rusz(sf::Vector2f pos_gracz)
	{
		for (int i = 0; i < ilosc; i++)
		{
			pajak1T[i].move(pos_gracz.x+10*i,pos_gracz.y-10*i);
		}
	}
private:
	sf::Texture tekturka;
	sf::Sprite *pajak1T;
	sf::Vector2f predkosc = sf::Vector2f(0, 0), pozycja;
	bool atak = false;
	int ilosc = 0;
};
//--------------------------------------------klasa meniu-------------------------------------------------------------
class meniu
{
public:
	meniu(bool zapis)
	{
		//czciaka
		czcionka.loadFromFile("Scary Roots Font.otf");
		//tekst i bloki
		for (int i = 0; i < 4; i++)
		{
			//tekst menu
			menu[i].setFont(czcionka);
			menu[i].setCharacterSize(120);
			menu[i].setFillColor(sf::Color::White);
			menu[i].setPosition(sf::Vector2f(100, 120 + 130 * i));
			//prostokaty
			prostokat[i].setSize(sf::Vector2f(630, 125));
			prostokat[i].setPosition(sf::Vector2f(90, 140 + 130 * i));
			prostokat[i].setFillColor(sf::Color::Transparent);
		}
		menu[0].setString("Kontynuuj");
		menu[1].setString("Nowa Gra");
		menu[2].setString("Pomoc");
		menu[3].setString("Wyjscie");
		if (zapis == false)
		{
			prostokat[0].setPosition(sf::Vector2f(0,-500));
			menu[0].setPosition(0, -500);
		}
	}
	void draw(sf::RenderWindow& okno)
	{
		for (int i = 0; i < 4; i++)
		{
			okno.draw(prostokat[i]);
			okno.draw(menu[i]);
		}
	}
	int wybor_opcji(sf::Vector2i polozenie, bool wcisniety)
	{
		for (int i = 0; i < 4; i++)
		{
			if (sprawdz_myszke(polozenie, prostokat[i].getPosition(), prostokat[i].getSize()) == true)
			{
				//prostokat[i].setFillColor(sf::Color::Green);
				if (wcisniety == true)
				{
					//prostokat[i].setFillColor(sf::Color::Yellow);
					return i;
				}
			}
			//else
				//prostokat[i].setFillColor(sf::Color::Blue);
		}
		return -1;
	}
private:
	sf::Font czcionka;
	sf::Text menu[4];
	sf::RectangleShape prostokat[4];
	int wybranaPozycja = 0;
};
//------------------------------------------------main-----------------------------------------------------------------
int main()
{
	//pomoc i obluga
	bool zapis = true, trudnosc = false;
	//okno
	sf::RenderWindow window(sf::VideoMode(1600, 900), "proby mechanik");
	window.setFramerateLimit(60); 
	//nie musze robic zegarow kazdej animacji bo czas klatki jest staly ale gra sie pewnie zepsuje jak komputer bedzie niedomagal

	//postacie i mapa w grze
	postac ludzik(sf::Vector2f(window.getSize().x/2, window.getSize().y / 2));
	pajak1 pejok;

	//menu i zapis
	int wybrana_opcja = -1, poz_trudnosci = 0;
	sf::Texture pomoc, tlo;
	meniu menu(zapis);
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
		// wyswietlam meniu
		if (wybrana_opcja == -1)
		{
			wybrana_opcja = menu.wybor_opcji(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Left));
			menu.draw(window);
		}
		// wyswietlam gre
		if (wybrana_opcja == 0 || wybrana_opcja == 1)
		{
			if (wybrana_opcja == 0)
			{
				//wczytanie zapisu gra trwa dalej
			}
			else if (wybrana_opcja == 1)
			{
				//menu wyboru poziomu trudnosci
				if (trudnosc == false)
				{
					pejok.tworz(10, ludzik.getPosition());
					trudnosc = true;
				}
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
				ludzik.rusz(sf::Keyboard::P);	//klawisze o i p sa uzyte jako klawisze braku aktywnosci
			//ruch pajakami
			pejok.rusz(sf::Vector2f(1,1));// ludzik.getPosition());




			
			window.draw(ludzik.getPostac());
			pejok.rysuj(window);
		}

		

		window.display();
	}
	return 0;
}