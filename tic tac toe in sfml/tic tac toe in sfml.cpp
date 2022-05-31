#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <array>

class Player;

class Gameplay {
	bool active = true;
	// checks if the player winning condition is meet
	int winConditions(std::array <std::array<Player, 3>, 3>& players, char shape, int count);

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

	Gameplay() {

		//makes the lines white
		for (auto& i : lines) {
			i.setFillColor(sf::Color::White);
		}

		//set the position of all the lines to make the grid pattern
		lines[0].setPosition(266.6666f, 0);
		lines[0].rotate(90.f);
		lines[1].setPosition(266.6666f * 2.f, 0);
		lines[1].rotate(90.f);
		lines[2].setPosition(0, 266.6666f);
		lines[3].setPosition(0, 266.6666f * 2.f);

		//set the each square to the correct grid position
		for (int i = 0; i < 3; i++) {

			for (int k = 0; k < 3; k++) {
				blocks[i][k].setPosition((266.6666f * k) + 5.f, (266.6666f * i) + 5.f);
				blocks[i][k].setFillColor(sf::Color(0, 200, 255));
			}
		}
	}

	//will define the winningLine object
	void winner(std::array <std::array<Player, 3>, 3>& players, Gameplay& game, Player& player, int count);

	bool getActive() {
		return this->active;
	}

	//ends the game
	void gameOver(Player& player);

	//Resets the game
	void reset(std::array <std::array<Player, 3>, 3> &players, Player &player,int &count);
};

class Player : public sf::Text {
	//stores if the mouse button has been pressed
	bool pressed = false;
	char shape = ' ';

public:
	//stores the shape o or x
	sf::Font font;
	std::string fileName = "font/Roboto-Medium.ttf";

	Player() {
		//set the Font, Origin point and displays the shape
		if (font.loadFromFile(fileName)) {
			this->setFont(font);

			this->setCharacterSize(200);
			this->setString(shape);
			this->setOrigin(50.f, 150.f);
			this->setFillColor(sf::Color::White);
		}
		else {
			throw "can't find font";
		}
	}
	//set the Font, starting shape, Origin point and displays the shape
	Player(char shape):shape(shape) {

		if (font.loadFromFile(fileName)) {
			this->setFont(font);
			this->setCharacterSize(200);
			this->setOrigin(50.f, 150.f);
			this->setFillColor(sf::Color::White);
			this->setString(this->shape);
		}
		else {
			throw "can't find font";
		}
	}
	//Alternates between o and x
	void turn() {

		if (shape == 'o') {
			shape = 'x';
		}
		else {
			shape = 'o';
		}
		this->setString(shape);
	}
	void clear() {
		shape = ' ';
	}
	//places down the shape on the grid
	void placeDown(std::array <std::array<Player, 3>, 3>& players, Player& player, sf::Vector2f mousePosition, Gameplay& game,int &count) {
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {

				// check if the mouse has been pressed and if the mouse is inside the one of the grid blocks
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed &&
					game.blocks[i][k].getGlobalBounds().contains(mousePosition) && players[i][k].getShape() == ' ') {
					pressed = true;

					//Places down the down the shape in the middle of one of the grid blocks
					player.setPosition(game.blocks[i][k].getPosition().x + (game.blocks[i][k].getSize().x / 2),
						game.blocks[i][k].getPosition().y + (game.blocks[i][k].getSize().y / 2));
					players[i][k] = Player(player);

					player.turn();
					count++;
					break;

				}

			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			pressed = false;
		}
		
	}

	char getShape() {
		return this->shape;
	}
	void setShape(char shape) {
		this->shape = shape;
	}
};

void Gameplay::reset(std::array <std::array<Player, 3>, 3>& players, Player& player, int& count) {
	char shape = 'o';
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !active) {
		count = 0;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				players[i][k].clear();
				players[i][k].setString(' ');

			}
		}
		winningLine.setSize(sf::Vector2f(0.f, 0.f));
		winningLine.setRotation(0.f);
		player.setString(shape);
		player.setShape(shape);
		active = true;
	}
}

int Gameplay::winConditions(std::array <std::array<Player, 3>, 3>& players, char shape, int count) {
	int choice = -1;
	//OOO
	for (int i = 0; i < 3; i++) {
		if (players[i][0].getShape() == shape && players[i][1].getShape() == shape && players[i][2].getShape() == shape) {
			choice = i;
		}
	/*O
	  O
	  O*/
		else if (players[0][i].getShape() == shape && players[1][i].getShape() == shape && players[2][i].getShape() == shape) {
			choice = i + 3;
		}
	/*
	O
	XOX
	XXO
	*/
		
	}

	
	if (players[0][0].getShape() == shape && players[1][1].getShape() == shape && players[2][2].getShape() == shape) {
		choice = 6;
	}
	else if (players[0][2].getShape() == shape && players[1][1].getShape() == shape && players[2][0].getShape() == shape) {
		choice = 7;
	}
	else if(count == 9) {
		choice = 8;
	}
	return choice;
}

void Gameplay::winner(std::array <std::array<Player, 3>, 3>& players, Gameplay &game, Player &player, int count) {
	sf::Vector2f middleBlock = sf::Vector2f(game.blocks[0][0].getSize().x / 2, game.blocks[0][0].getSize().y / 2);

	std::array <char, 2> shapes = { 'x','o' };

	for (int i = 0; i < 2; i++) {
		switch (winConditions(players, shapes[i],count)) {

		case 0:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[0][0].getPosition().x + middleBlock.x / 2.f, game.blocks[0][0].getPosition().y + middleBlock.y));
			game.winningLine.setSize(sf::Vector2f(game.blocks[0][2].getPosition().x + middleBlock.x, 5.f));
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 1:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[1][0].getPosition().x + middleBlock.x / 2.f, game.blocks[1][0].getPosition().y + middleBlock.y));
			game.winningLine.setSize(sf::Vector2f(game.blocks[1][2].getPosition().x + middleBlock.x, 5.f));
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 2:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[2][0].getPosition().x + middleBlock.x / 2.f, game.blocks[2][0].getPosition().y + middleBlock.y));
			game.winningLine.setSize(sf::Vector2f(game.blocks[2][2].getPosition().x + middleBlock.x, 5.f));
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 3:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[0][0].getPosition().x + middleBlock.x, game.blocks[0][0].getPosition().y + middleBlock.y / 2.f));
			game.winningLine.setSize(sf::Vector2f(5.f, game.blocks[2][0].getPosition().y + middleBlock.y));
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 4:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[0][1].getPosition().x + middleBlock.x, game.blocks[0][1].getPosition().y + middleBlock.y / 2.f));
			game.winningLine.setSize(sf::Vector2f(5.f, game.blocks[2][1].getPosition().y + middleBlock.y));
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 5:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[0][2].getPosition().x + middleBlock.x, game.blocks[0][1].getPosition().y + middleBlock.y / 2.f));
			game.winningLine.setSize(sf::Vector2f(5.f, game.blocks[2][2].getPosition().y + middleBlock.y));
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 6:
			game.winningLine.setPosition(sf::Vector2f(game.blocks[0][0].getPosition().x + middleBlock.x / 2.f , game.blocks[0][0].getPosition().y + middleBlock.y / 2.f));
			game.winningLine.setSize(sf::Vector2f(game.blocks[2][2].getPosition().x + middleBlock.x * 3.f, 5.f));
			game.winningLine.setRotation(45);
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 7:
			game.winningLine.setPosition(sf::Vector2f(middleBlock.x + (game.blocks[0][2].getPosition().x + middleBlock.x / 2.f), middleBlock.x - (game.blocks[0][2].getPosition().y + middleBlock.y / 2.f)));
			game.winningLine.setSize(sf::Vector2f(game.blocks[2][2].getPosition().x + middleBlock.x * 3.f, 5.f));
			game.winningLine.setRotation(90 + 45);
			game.winningLine.setFillColor(sf::Color::White);
			gameOver(player);
			break;
		case 8:
			gameOver(player);
		}
	}
}

void Gameplay::gameOver(Player &player) {
	player.setString(' ');
	this->active = false;
}

int main() {

	sf::RenderWindow window(sf::VideoMode(800.f, 800.f), "tic tac toe", sf::Style::Close);
	Gameplay game;

	Player player('o');
	
	int counter = 0;
	//represents the positions of the players in the grid
	std::array <std::array<Player, 3>, 3> players;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}
		game.reset(players,player,counter);

		while (game.getActive()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == event.Closed) {
					window.close();
				}
			}
			sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

			//update
			window.clear(sf::Color(0, 200, 255));

			player.setPosition(mousePosition);

			player.placeDown(players, player, mousePosition, game, counter);
			game.winner(players, game, player, counter);

			//draw
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {

					window.draw(game.blocks[i][k]);

				}

			}

			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {

					window.draw(players[i][k]);

				}

			}

			for (auto& i : game.lines) {
				window.draw(i);
			}
			window.draw(game.winningLine);
			window.draw(player);

			window.display();
		}
		
		
	}
}