/**
snake.cpp
Purpose: TODO

@author  Joshua Varga
@version 1.0
*/

#include "snake.h"
#include <iostream>

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

void Snake::init()
{
	// Random seed.
	srand((unsigned int)time(NULL));

	// Initialize window.
	window.create(sf::VideoMode(width, height), "Snake", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);

	// Initialize font/text.
	font.loadFromFile("Snake/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(50,25));

	// Initialize playArea.
	playArea.setFillColor(sf::Color::Black);
	playArea.setOutlineColor(sf::Color::White);
	playArea.setOutlineThickness(5);
	playArea.setPosition(sf::Vector2f(50, 50));
	playArea.setSize(sf::Vector2f(500, 500));

	// Initialize player.
	player.setPosition(sf::Vector2f(((float)(rand() % 100) * 5 + 50), (float)((rand() % 100) * 5 + 50)));
	player.setSize(sf::Vector2f(5, 5));
	player.setFillColor(sf::Color::Green);

	// Initialize food.
	sf::Vector2f foodVector(sf::Vector2f(((float)(rand() % 100) * 5 + 50), (float)((rand() % 100) * 5 + 50)));
	while (foodVector == player.getPosition())
	{
		foodVector = sf::Vector2f(sf::Vector2f(((float)(rand() % 100) * 5 + 50), (float)((rand() % 100) * 5 + 50)));
	}
	food.setPosition(foodVector);
	food.setSize(sf::Vector2f(5, 5));
	food.setFillColor(sf::Color::Red);
}

void Snake::update()
{
	text.setString("Score: " + std::to_string(score));

	if (tail.size() > 0)
	{
		for (int i = tail.size() - 1; i > 0; i--)
		{
			tail[i] = tail[i - 1];
		}

		tail[0] = player.getPosition();
	}

	if (direction == 'w')
	{
		player.move(sf::Vector2f(0, -5));
	}

	if (direction == 'a')
	{
		player.move(sf::Vector2f(-5, 0));
	}

	if (direction == 's')
	{
		player.move(sf::Vector2f(0, 5));
	}

	if (direction == 'd')
	{
		player.move(sf::Vector2f(5, 0));
	}

	// Wall Collisions
	if (player.getPosition().x     < playArea.getPosition().x       ||
		player.getPosition().x     > playArea.getPosition().x + 495 ||
		player.getPosition().y     < playArea.getPosition().y       ||
		player.getPosition().y + 5 > playArea.getPosition().y + 500)
	{
		player.setFillColor(sf::Color::Black);
		running = false;
	}

	else if (tailCollision(player.getPosition()))
	{
		running = false;
	}

	else if (player.getPosition() == food.getPosition())
	{
		score++;

		sf::Vector2f foodVector(sf::Vector2f(((float)(rand() % 100) * 5 + 50), (float)((rand() % 100) * 5 + 50)));
		while (foodVector == player.getPosition() && tailCollision(foodVector))
		{
			foodVector = sf::Vector2f(sf::Vector2f(((float)(rand() % 100) * 5 + 50), (float)((rand() % 100) * 5 + 50)));
		}
		food.setPosition(foodVector);

		tail.push_back(sf::Vector2f(-5, -5));
	}

	else
	{
		player.setFillColor(sf::Color::Green);
	}
}

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

void Snake::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != 's')
	{
		direction = 'w';
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != 'd')
	{
		direction = 'a';
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != 'w')
	{
		direction = 's';
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != 'a')
	{
		direction = 'd';
	}
}

void Snake::run()
{
	init();

	sf::Clock clock;

	// For frame independant gameplay.
	double update_interval = 0.1;
	double total_time = 0;
	double current_time = clock.getElapsedTime().asSeconds();
	double new_time;
	double frame_time;

	while (running)
	{
		new_time = clock.getElapsedTime().asSeconds();
		frame_time = new_time - current_time;
		current_time = new_time;
		total_time += frame_time;

		pollEvents();

		input();

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
		for (int i = 0; i < (int)tail.size(); i++)
		{
			sf::RectangleShape rect;
			rect.setPosition(tail[i]);
			rect.setSize(sf::Vector2f(5, 5));
			rect.setFillColor(sf::Color::Green);
			window.draw(rect);
		}

		window.display();
	}
}
