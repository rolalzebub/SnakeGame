#pragma once
#include "SFML/Graphics.hpp"
class Button
{
private:
	sf::Text label;
	sf::Vector2f screenPos;
	sf::RectangleShape buttonBounds;
public:
	Button(const sf::String& name, const sf::Vector2f& size, const sf::Vector2f& screenPos, const sf::Font& font);
	void RenderButton(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() { return label.getPosition(); }
	sf::RectangleShape GetBounds() { return buttonBounds;  }
	void SetFillColour(const sf::Color& color) { buttonBounds.setFillColor(color); }
	Button();
	~Button();
};