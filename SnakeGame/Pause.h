#pragma once
#include "Menu.h"
class Pause : public Menu
{
public:
	enum SelectedOption {
		Continue,
		Restart,
		Quit
	};
private:
	SelectedOption current_selection = SelectedOption::Continue;
	Button continueButton;
	Button restartButton;
	Button quitButton;

	sf::Vector2f buttonSize{ 70, 40 };
public:
	Pause(const std::string & menuHeader, const sf::Font & font, sf::Vector2f headerPosition);
	void ChangeSelected(sf::Keyboard::Key code);
	void RenderMenu(sf::RenderWindow& window);
	SelectedOption SelectOption() { return current_selection; }
	void ResetState() { current_selection = SelectedOption::Continue; }
	~Pause();
};

