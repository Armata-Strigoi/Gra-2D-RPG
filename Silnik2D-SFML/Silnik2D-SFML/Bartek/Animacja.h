#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animacja
{
private:
	sf::Texture tekstura;
	int x = 0, y = 0, szerokosc, wysokosc, klatki, klatka, wysokoscMAX = 0, szerokoscMAX = 0;
	float przerwa, dt = 0; // Przerwa pomi�dzy klatkami
	bool pionowa; // Ustawienie klatek w pliku
	
	void zmienKlatke() { // Zmienia klatke na nast�pn�, po dotarciu na ostatni� klatke wraca do pierwszej.	
		if (dt > przerwa) { // Je�eli licznik jest wi�kszy ni� podana przerwa zmienia sie klatka animacji
			if (pionowa) {
				this->y += wysokosc;
				if (this->y >= wysokoscMAX)this->y = 0;
			}
			else {
				this->x += szerokosc;
				if (this->x >= wysokosc)this->x = 0;
			}
			dt = 0; // Licznik jest resetowany
		}
	}

public:
	sf::Sprite sprajt;
	Animacja(std::string sciezka, int pozx, int pozy, int szerokosc, int wysokosc, int klatki, float przerwa, bool pionowa = true) {
		this->szerokosc = szerokosc;
		this->wysokosc = wysokosc;
		this->klatki = klatki;
		if(!this->tekstura.loadFromFile(sciezka)) {
			std::cout << "Blad w ladowaniu animacji" << std::endl;
		}
		this->klatka = 1;
		this->pionowa = pionowa;
		this->przerwa = przerwa;
		if(pionowa) this->wysokoscMAX = wysokosc * klatki;
		else this->szerokoscMAX = szerokosc * klatki;

		//Sprite
		this->sprajt.setTexture(this->tekstura);
		this->sprajt.setTextureRect(sf::IntRect(this->x, this->y, this->szerokosc, this->wysokosc));
		this->sprajt.setPosition(sf::Vector2f(pozx, pozy));
	}

	void animuj(sf::RenderTarget *cel, const float& dtime) { // Rysuje i zmienia klatke na nast�pn�.
		cel->draw(this->sprajt);
		this->dt += dtime;
		zmienKlatke();
		this->sprajt.setTextureRect(sf::IntRect(this->x, this->y, this->szerokosc, this->wysokosc));
	}

	void rusz(sf::Vector2f gdzie) { // Zmienia pozycje sprite'a
		this->sprajt.setPosition(gdzie);
	}

};

