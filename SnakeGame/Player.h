#pragma once
#include "Snake.h"
class Player: public Snake
{
private:
	unsigned int score = 0;
	sf::Vector2f score_display_position{ 10, 2 };
	sf::Vector2f breath_display_position{ 500, 2 };
	sf::Font font;
public:
	void InputHandler(sf::Event::KeyEvent keyPress);
	void PointScored();
	void RenderDetails(sf::RenderWindow& window);
	int getScore() { return score; }
	sf::Vector2f GetHeadPosition();
	Player();
	~Player();
};