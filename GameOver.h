#pragma once
#include "Menu.h"
class GameOver : public Menu
{
public:
	enum SelectedOption {
		Restart,
		Quit
	};
private:
	SelectedOption current_selection = SelectedOption::Restart;

	Button restart;
	Button quit;

	unsigned int score = 0;

	sf::Text scoreHeader{ "Score", menuFont, 30 };
	sf::Text scoreText{ std::to_string(score), menuFont,  30};

	sf::Vector2f scoreHeaderOffset{ 100, 120 };
	sf::Vector2f scoreTextOffset{ 100, 100 };

	sf::Vector2f buttonSize{ 70, 40 };

public:
	void ChangeSelected();
	SelectedOption SelectOption() { return current_selection; }
	void RenderMenu(sf::RenderWindow& window);
	void ResetState() { current_selection = SelectedOption::Restart; }
	GameOver(const std::string& menuHeader, const sf::Font& font, sf::Vector2f headerPosition);
	void SetScore(const int& score_);
	~GameOver();
};

