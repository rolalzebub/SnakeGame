#include "GameOver.h"



void GameOver::ChangeSelected()
{
	if (current_selection == SelectedOption::Restart) {
		current_selection = SelectedOption::Quit;
	}
	else current_selection = SelectedOption::Restart;
}

void GameOver::RenderMenu(sf::RenderWindow & window)
{
	window.draw(headerText);
	window.draw(scoreHeader);
	window.draw(scoreText);
	buttons[current_selection].SetFillColour(sf::Color::Blue);
	for (int i = 0; i < buttons.size(); i++) {
		if (i != current_selection) {
			buttons[i].SetFillColour(sf::Color::Red);
		}
		buttons[i].RenderButton(window);
	}
}

GameOver::GameOver(const std::string& menuHeader, const sf::Font& font, sf::Vector2f headerPosition): Menu(menuHeader, font, headerPosition)
{
	restart = Button(sf::String("Restart"), buttonSize, headerText.getPosition(), font);
	quit = Button(sf::String("Quit"), buttonSize, headerText.getPosition(), font);

	buttons.push_back(restart);
	buttons.push_back(quit);

	InitializeButtons();

	scoreHeader.setPosition(headerPosition - scoreHeaderOffset);
	scoreText.setPosition(headerPosition - scoreTextOffset);
	scoreHeader.setFont(font);
	scoreText.setFont(font);
}

void GameOver::SetScore(const int & score_)
{
	score = score_;
	scoreText.setString(std::to_string(score));
}


GameOver::~GameOver()
{
}
