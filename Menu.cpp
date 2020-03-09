#include "Menu.h"



void Menu::RenderMenu(sf::RenderWindow & window)
{

	window.draw(headerText);

	for (int i = 0; i < buttons.size(); i++){
		buttons[i].RenderButton(window);
	}
}


void Menu::InitializeButtons()
{
	if (buttons.size() < 1) {
		return;
	}
	sf::Vector2f next_pos = headerText.getPosition();
	next_pos.y += buttonGap;
	for (int i = 0; i <= buttons.size() - 1; i++) {
		buttons[i].SetPosition(next_pos);
		next_pos.y += buttonGap;
	}
}


Menu::Menu(const std::string& menuHeader, const sf::Font& font, sf::Vector2f headerPosition)
{
	headerText.setString(menuHeader);
	headerText.setFont(font);
	menuFont = font;
	headerText.setOrigin(sf::Vector2f((headerText.getLocalBounds().left + headerText.getLocalBounds().width) / 2, (headerText.getLocalBounds().top + headerText.getLocalBounds().height) / 2));
	headerText.setPosition(headerPosition);
}

std::vector<sf::RectangleShape> Menu::GetButtonPositions()
{
	std::vector <sf::RectangleShape> buttonBounds;

	for (Button b : buttons) {
		buttonBounds.push_back(b.GetBounds());
	}

	return buttonBounds;
}

Menu::~Menu()
{
}
