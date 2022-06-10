#pragma once

#include "Gameplay.h"

class Gameplay;

class Player : public sf::Text {
	
	bool pressed = false; //stores if the mouse button has been pressed
	char shape = ' '; //stores the shape o or x

public:
	
	sf::Font font;

	std::string fileName = "font/Roboto-Medium.ttf";

	//set the Font, Origin point and displays the shape
	Player();
	
	//set the Font, starting shape, Origin point and displays the shape
	Player(char shape);
	
	//Alternates between o and x
	void turn();

	void clear();

	//places down the shape on the grid
	void placeDown(std::array <std::array<Player, 3>, 3>& players, Player& player, sf::Vector2f mousePosition, Gameplay& game, int& count);

	char getShape();

	void setShape(char shape);
};


