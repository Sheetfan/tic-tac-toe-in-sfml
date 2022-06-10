#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <array>
#include "Player.h"

class Player;

class Gameplay {
private:
	bool active = true;

public:
	// sets the lines
	std::array < sf::RectangleShape, 4>lines = {
		sf::RectangleShape(sf::Vector2f(800.f,5.f)),
		sf::RectangleShape(sf::Vector2f(800.f,5.f)),
		sf::RectangleShape(sf::Vector2f(800.f,5.f)),
		sf::RectangleShape(sf::Vector2f(800.f,5.f)),
	};

	//create the grid and each RectangleShape object will repcent a block in the grid
	std::array <std::array<sf::RectangleShape, 3>, 3> blocks = { {
		{
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f)),
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f)),
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f))
		},

		{
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f)),
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f)),
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f))
		}
		,
		{
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f)),
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f)),
			sf::RectangleShape(sf::Vector2f(266.6666f - 5.f,266.6666f - 5.f))
		}
	}
	};

	sf::RectangleShape winningLine;

	Gameplay();

	bool getActive();

	//Resets the game
	void reset(std::array <std::array<Player, 3>, 3>& players, Player& player, int& count);

	//will define the winningLine object
	void winner(std::array <std::array<Player, 3>, 3>& players, Gameplay& game, Player& player, int count);

	//ends the game
	void gameOver(Player& player);

private:

	// checks if the player winning condition is meet
	int winConditions(std::array <std::array<Player, 3>, 3>& players, char shape, int count);
};