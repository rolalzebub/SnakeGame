#pragma once
#include "Menu.h"

class Main_Menu: public Menu
{
public:
	enum SelectedOption {
		Play,
		Quit
	};
private:
	SelectedOption current_selection = SelectedOption::Play;
	Button playButton;
	Button quitButton;

	sf::Vector2f buttonSize{ 70, 40 };

public:
	Main_Menu(const std::string& menuHeader, const sf::Font& font, const sf::Vector2f& headerPosition);
	void ChangeSelected();
	void RenderMenu(sf::RenderWindow& window);
	SelectedOption SelectOption() { return current_selection; }
	void ResetState() { current_selection = SelectedOption::Play; }
	~Main_Menu();
};

