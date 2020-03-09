#include "Pause.h"



Pause::Pause(const std::string & menuHeader, const sf::Font & font, sf::Vector2f headerPosition) : Menu(menuHeader, font, headerPosition)
{
	continueButton = Button(sf::String("Continue"), buttonSize, headerText.getPosition(), font);
	restartButton = Button(sf::String("Restart"), buttonSize, headerText.getPosition(), font);
	quitButton = Button(sf::String("Quit"), buttonSize, headerText.getPosition(), font);

	buttons.push_back(continueButton);
	buttons.push_back(restartButton);
	buttons.push_back(quitButton);

	InitializeButtons();
}

void Pause::ChangeSelected(sf::Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) {
		switch (current_selection) {
		case SelectedOption::Continue:
			current_selection = SelectedOption::Quit;
			break;
		case SelectedOption::Restart:
			current_selection = SelectedOption::Continue;
			break;
		case SelectedOption::Quit:
			current_selection = SelectedOption::Restart;
			break;
		}
	}
	else if (code == sf::Keyboard::Down) {
		switch (current_selection) {
		case SelectedOption::Continue:
			current_selection = SelectedOption::Restart;
			break;
		case SelectedOption::Restart:
			current_selection = SelectedOption::Quit;
			break;
		case SelectedOption::Quit:
			current_selection = SelectedOption::Continue;
			break;
		}
	}
}

void Pause::RenderMenu(sf::RenderWindow & window)
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


Pause::~Pause()
{
}
