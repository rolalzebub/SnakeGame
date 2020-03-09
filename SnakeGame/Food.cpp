#include "Food.h"

void Food::SetPosition(sf::Vector2f new_position)
{
	position = new_position;
	self.setPosition((sf::Vector2f) position);
}

sf::Vector2f Food::GetPosition()
{
	return position;
}

void Food::Consumed()
{
	isActive = false;
}

void Food::RenderFood(sf::RenderWindow & window)
{
	if (isActive)
		window.draw(self);
}

void Food::SetActiveStatus(bool activeState)
{
	isActive = activeState;
}

bool Food::GetActiveStatus()
{
	return isActive;
}

Food::Food()
{
	self.setRadius(radius);
	self.setOrigin(sf::Vector2f( radius, radius ));
}

Food::~Food()
{
}
