#include "Gameplay.h"


Gameplay::Gameplay() {

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

bool Gameplay::getActive() {
	return this->active;
}

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

void Gameplay::winner(std::array <std::array<Player, 3>, 3>& players, Gameplay& game, Player& player, int count) {
	sf::Vector2f middleBlock = sf::Vector2f(game.blocks[0][0].getSize().x / 2, game.blocks[0][0].getSize().y / 2);

	std::array <char, 2> shapes = { 'x','o' };

	for (int i = 0; i < 2; i++) {
		switch (winConditions(players, shapes[i], count)) {

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
			game.winningLine.setPosition(sf::Vector2f(game.blocks[0][0].getPosition().x + middleBlock.x / 2.f, game.blocks[0][0].getPosition().y + middleBlock.y / 2.f));
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

void Gameplay::gameOver(Player& player) {
		player.setString(' ');
		this->active = false;
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
	else if (count == 9) {
		choice = 8;
	}
	return choice;
}

