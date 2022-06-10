#include "Player.h"
#include "Gameplay.h"

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