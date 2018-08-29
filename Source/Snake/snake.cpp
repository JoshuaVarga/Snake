/**
snake.cpp
Purpose: Implements snake in c++.

@author  Joshua Varga
@version 1.1
*/

#include "snake.h"

// Generates a random vector within the play area.
sf::Vector2f Snake::randomVector()
{
	return sf::Vector2f((float)((rand() % 100) * RECT_SIZE + OFFSET),
		(float)((rand() % 100) * RECT_SIZE + OFFSET));
}

// Creates a new rectangle with a specified position and colour.
sf::RectangleShape Snake::newRect(sf::Vector2f position, sf::Color colour)
{
	sf::RectangleShape rect;
	rect.setPosition(position);
	rect.setSize(sf::Vector2f(RECT_SIZE, RECT_SIZE));
	rect.setFillColor(colour);

	return rect;
}

// Checks if a vector intersects any part of the tail.
bool Snake::tailCollision(sf::Vector2f vector)
{
	for (int i = 0; i < (int)tail.size(); i++)
	{
		if (tail[i] == vector)
		{
			return true;
		}
	}
	return false;
}

// Initializes the snake game.
void Snake::init()
{
	// Random seed.
	srand((unsigned int)time(NULL));

	// Initialize window.
	window.create(sf::VideoMode(WIDTH, WIDTH), "Snake",
		sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);

	// Initialize font/text.
	font.loadFromFile("Snake/arial.ttf");
	text.setFont(font);
	text.setCharacterSize((OFFSET / 2));
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(OFFSET, OFFSET / 4));

	// Initialize playArea.
	playArea.setFillColor(sf::Color::Black);
	playArea.setOutlineColor(sf::Color::White);
	playArea.setOutlineThickness(RECT_SIZE);
	playArea.setPosition(sf::Vector2f(OFFSET, OFFSET));
	playArea.setSize(sf::Vector2f(PLAY_WIDTH, PLAY_WIDTH));

	// Initialize player.
	player = newRect(randomVector(), sf::Color::Green);

	// Initialize food.
	sf::Vector2f foodVector(randomVector());
	// Ensures food doesn't move onto snake.
	while (foodVector == player.getPosition())
	{
		foodVector = sf::Vector2f(randomVector());
	}
	food = newRect(foodVector, sf::Color::Red);
}

// Updates the snake game.
void Snake::update()
{
	text.setString("Score: " + std::to_string(score));

	// Updates tail coordinates.
	if (tail.size() > 0)
	{
		for (int i = tail.size() - 1; i > 0; i--)
		{
			tail[i] = tail[i - 1];
		}

		tail[0] = player.getPosition();
	}

	// Snake always moves forward until direction changes.
	if (direction == 'w')
	{
		player.move(sf::Vector2f(0, -RECT_SIZE));
	}

	if (direction == 'a')
	{
		player.move(sf::Vector2f(-RECT_SIZE, 0));
	}

	if (direction == 's')
	{
		player.move(sf::Vector2f(0, RECT_SIZE));
	}

	if (direction == 'd')
	{
		player.move(sf::Vector2f(RECT_SIZE, 0));
	}

	// Wall Collisions
	unsigned short int player_x   = (unsigned short int)player.getPosition().x;
	unsigned short int player_y   = (unsigned short int)player.getPosition().y;

	unsigned short int playArea_x = (unsigned short int)playArea.getPosition().x;
	unsigned short int playArea_y = (unsigned short int)playArea.getPosition().y;

	if (player_x < playArea_x						   ||
		player_x > playArea_x + PLAY_WIDTH - RECT_SIZE ||
		player_y < playArea_y						   ||
		player_y + RECT_SIZE > playArea_y + PLAY_WIDTH)
	{
		player.setFillColor(sf::Color::Black);
		restart();
	}

	// Tail Collisions.
	else if (tailCollision(player.getPosition()))
	{
		player.setFillColor(sf::Color::Black);
		restart();
	}

	// Food Collisions
	else if (player.getPosition() == food.getPosition())
	{
		score++;

		sf::Vector2f foodVector(randomVector());
		// Ensures food doesn't move onto snake.
		while (foodVector == player.getPosition() && tailCollision(foodVector))
		{
			foodVector = sf::Vector2f(randomVector());
		}
		food.setPosition(foodVector);

		// Increase size of tail.
		for (int i = 0; i < 10; i++)
		{
			tail.push_back(sf::Vector2f(-RECT_SIZE, -RECT_SIZE));
		}
	}
}

// Polls events of the snake game.
void Snake::pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case (sf::Event::Closed):
			{
				window.close();
			}
		}
	}
}

// Handles user input.
void Snake::input()
{
	// Move up.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != 's')
	{
		direction = 'w';
	}

	// Move left.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != 'd')
	{
		direction = 'a';
	}

	// Move down.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != 'w')
	{
		direction = 's';
	}

	// Move right.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != 'a')
	{
		direction = 'd';
	}

	// Restart.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (direction != '?')
		{
			restart();
		}
	}

	// Close.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
}

// Runs the snake game.
void Snake::run()
{
	// Controls
	std::cout << "\nControls:\n";
	std::cout << "WASD - Movement\n";
	std::cout << "R    - Restart\n";
	std::cout << "ESC  - Close\n\n";

	init();

	// For frame independant gameplay.
	sf::Clock clock;
	double update_interval = 0.0833333333333333; // 1 / frames.
	double total_time = 0;
	double current_time = clock.getElapsedTime().asSeconds();
	double new_time;
	double frame_time;

	while (window.isOpen())
	{
		// Update times.
		new_time = clock.getElapsedTime().asSeconds();
		frame_time = new_time - current_time;
		current_time = new_time;
		total_time += frame_time;

		pollEvents();

		input();

		// Game only updates at a cetain interval.
		while (total_time >= update_interval)
		{
			update();

			total_time -= update_interval;
		}

		window.clear();

		window.draw(text);
		window.draw(playArea);
		window.draw(food);
		window.draw(player);

		// Draw tail.
		for (int i = 0; i < (int)tail.size(); i++)
		{
			sf::RectangleShape rect = newRect(tail[i], sf::Color::Green);
			window.draw(rect);
		}

		window.display();
	}
}

// Restarts the game.
void Snake::restart()
{
	score = 0;
	tail.resize(0);
	player.setPosition(randomVector());
	player.setFillColor(sf::Color::Green);
	food.setPosition(randomVector());
	direction = '?';
}
