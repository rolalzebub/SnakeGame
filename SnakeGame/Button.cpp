#include "Button.h"

Button::Button(const sf::String &name, const sf::Vector2f& size, const sf::Vector2f& screenPos, const sf::Font& font)
{

	buttonBounds.setPosition(screenPos);
	buttonBounds.setSize(size);
	buttonBounds.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	buttonBounds.setOutlineColor(sf::Color::White);
	buttonBounds.setOutlineThickness(2);
	buttonBounds.setFillColor(sf::Color(235, 15, 15, 180));

	label.setString(name);
	label.setPosition(screenPos);
	label.setFont(font);
	label.setOrigin(size.x / 2, size.y/2);
}

void Button::RenderButton(sf::RenderWindow& window)
{
	window.draw(buttonBounds);
	window.draw(label);
}

void Button::SetPosition(sf::Vector2f position)
{
	label.setPosition(position);
	buttonBounds.setPosition(position);
}


Button::Button()
{
}

Button::~Button()
{
}
