/**
	main.cpp
	Purpose: TODO

	@author  Joshua Varga
	@version 1.0
*/

#include <iostream>
#include <string>

#include "Snake/snake.h"

/**
	Clears a specified amount of characters from the console.

	@param backspaces Amount of characters to clear.
*/
void clearConsole(int backspaces);

int main()
{
	// Title
	std::cout << "   __   ____   ___   __   ____  ____ \n";
	std::cout << "  / _\\ (  _ \\ / __) / _\\ (    \\(  __)\n";
	std::cout << " /    \\ )   /( (__ /    \\ ) D ( ) _) \n";
	std::cout << " \\_/\\_/(__\\_) \\___)\\_/\\_/(____/(____)\n";

	std::cout << "\nBy: Joshua Varga\n";

	std::cout << "----------------------------------------\n";
                                                              
	// Games
	static const unsigned short int NUM_GAMES = 1;

	std::cout << "Games:\n";

	std::cout << "[1] Snake\n";
	std::cout << "[" << NUM_GAMES + 1 << "] Exit\n\n";

	// Selection
	std::string input;

selection:

	input = "input";

	while (input.length() != 1)
	{
		std::cout << "Choose a game: ";
		std::getline(std::cin, input);
	}
	
	char choice = input[0];

	switch (choice)
	{
		// Exit
		case (NUM_GAMES + 1 + '0'):
		{
			exit(0);
			break;
		}

		case ('1'):
		{
			std::unique_ptr<Snake> game = std::make_unique<Snake>();
			game.get()->run();
			goto selection;
			break;
		}

		default:
		{
			goto selection;
			break;
		}
	}

	return 0;
}

// Clears a specified amount of characters from the console.
void clearConsole(int backspaces)
{
	for (int i = 0; i < backspaces; i++)
	{
		std::cout << "\b";
	}
}