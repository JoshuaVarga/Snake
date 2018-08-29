/**
snake.h
Purpose: TODO

@author  Joshua Varga
@version 1.0
*/

#ifndef   SNAKE_H
#define   SNAKE_H

#include <random>

#include <SFML/Graphics.hpp>

class Snake
{
private:
	unsigned short int width  = 600;
	unsigned short int height = 600;

	sf::RenderWindow window;

	sf::RectangleShape playArea, player, food;
	std::vector<sf::Vector2f> tail;

	sf::Font font;
	sf::Text text;

	bool running = true;

	// Direction player is moving (w, a, s, d).
	char direction;

	unsigned int score = 0;

public:
	bool tailCollision(sf::Vector2f vector);

	void init();
	void update();
	void pollEvents();
	void input();
	void run();
};

#endif // SNAKE_H

