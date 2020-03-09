#pragma once
#include<vector>
#include "Button.h"
#include <SFML/Graphics.hpp>

class Menu
{
protected:

	std::vector<Button> buttons;
	int buttonGap = 80;
	sf::Text headerText;
	sf::Font menuFont;
public:
	virtual void RenderMenu(sf::RenderWindow& window);
	void InitializeButtons();
	Menu(const std::string& menuHeader, const sf::Font& font, sf::Vector2f headerPosition);
	std::vector<sf::RectangleShape> GetButtonPositions();
	~Menu();
};

