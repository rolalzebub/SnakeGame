#include "Main_Menu.h"


Main_Menu::Main_Menu(const std::string & menuHeader, const sf::Font & font, const sf::Vector2f& headerPosition): Menu(menuHeader, font, headerPosition)
{
	playButton = Button(sf::String("Play"), buttonSize, headerText.getPosition(), font);
	quitButton = Button(sf::String("Quit"), buttonSize, headerText.getPosition(), font);

	buttons.push_back(playButton);
	buttons.push_back(quitButton);

	InitializeButtons();
}

void Main_Menu::ChangeSelected()
{
	if (current_selection == SelectedOption::Play) {
		current_selection = SelectedOption::Quit;
	}
	else current_selection = SelectedOption::Play;
}

void Main_Menu::RenderMenu(sf::RenderWindow & window)
{
	window.draw(headerText);
	buttons[current_selection].SetFillColour(sf::Color::Blue);
	for (int i = 0; i < buttons.size(); i++) {
		if (i != current_selection) {
			buttons[i].SetFillColour(sf::Color::Red);
		}
		buttons[i].RenderButton(window);
	}
}

Main_Menu::~Main_Menu()
{
}
