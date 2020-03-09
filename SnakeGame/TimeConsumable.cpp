#include "TimeConsumable.h"



void TimeConsumable::Consumed()
{
	Food::Consumed();
}

TimeConsumable::TimeConsumable()
{
	food_type = Type::Time;
	self.setFillColor(sf::Color::Yellow);
}


TimeConsumable::~TimeConsumable()
{
}
