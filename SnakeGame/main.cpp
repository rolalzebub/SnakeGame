/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/
// SFML header file for graphics, there are also ones for Audio, Window, System and Network

#include"Game.h"
#include <iostream>

int main()
{
    std::cout << "SnakeGame: Starting" << std::endl;

	Game game;
	game.MainLoop();
    

    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}