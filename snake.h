/**
snake.h
Purpose: Implements snake in c++.

@author  Joshua Varga
@version 1.1
*/

#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

class Snake
{
private:
	// Constants
	static const unsigned short int WIDTH = 800;
	static const unsigned short int PLAY_WIDTH = WIDTH - (WIDTH / 10);
	static const unsigned short int OFFSET = (WIDTH - PLAY_WIDTH) / 2;
	static const unsigned short int RECT_SIZE = PLAY_WIDTH / 100;

	sf::RenderWindow window;

	sf::RectangleShape playArea, player, food;

	// Stores coordinates of tail pieces.
	std::vector<sf::Vector2f> tail;

	sf::Font font;
	sf::Text text;

	// Direction player is moving (w, a, s, d).
	char direction = '?';

	unsigned int score = 0;

public:
	/**
		Generates a random vector within the play area.
	*/
	sf::Vector2f randomVector();

	/**
		Creates a new rectangle with a specified position and colour.

		@param  position Position to set rectangle to.
		@param  colour   Colour of the rectangle.
		@return			 Rectangle that matches the parameters.
	*/
	sf::RectangleShape newRect(sf::Vector2f position, sf::Color colour);

	/**
		Checks if a vector intersects any part of the tail.

		@param vector Vector to check against.
		@return		  True if it intersects, False otherwise.
	*/
	bool tailCollision(sf::Vector2f vector);

	/**
		Initializes the snake game.
	*/
	void init();

	/**
		Updates the snake game.
	*/
	void update();

	/**
		Polls events of the snake game.
	*/
	void pollEvents();

	/**
		Handles user input.
	*/
	void input();

	/**
		Runs the snake game.
	*/
	void run();

	/**
		Restarts the game.
	*/
	void restart();
};

#endif // SNAKE_H