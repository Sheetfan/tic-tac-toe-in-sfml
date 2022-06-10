#include "Player.h"

Player::Player() {
	
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
	
Player::Player(char shape) :shape(shape) {
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

void Player::turn() {

	if (shape == 'o') {
		shape = 'x';
	}
	else {
		shape = 'o';
	}
	this->setString(shape);
}

void Player::clear() {
	shape = ' ';
}

void Player::placeDown(std::array <std::array<Player, 3>, 3>& players, Player& player, sf::Vector2f mousePosition, Gameplay& game, int& count) {
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

char Player::getShape() {
	return this->shape;
}

void Player::setShape(char shape) {
	this->shape = shape;
}
