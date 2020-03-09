#pragma once
#include <SFML/Graphics.hpp>

class Food
{
public:
	enum Type {
		Points,
		Time
	};
protected:
	bool isActive = true;
	sf::Vector2f position;
	sf::CircleShape self;
	int radius = 5;
	Type food_type;
public:
	void SetPosition(sf::Vector2f new_position);
	sf::Vector2f GetPosition();
	virtual void Consumed();
	void RenderFood(sf::RenderWindow& window);
	void SetActiveStatus (bool activeState = true);
	bool GetActiveStatus();
	Food();
	~Food();
};

