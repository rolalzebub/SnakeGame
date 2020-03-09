#include "PointsConsumable.h"

void PointsConsumable::Consumed()
{
	Food::Consumed();
}

PointsConsumable::PointsConsumable()
{
	food_type = Type::Points;
	self.setFillColor(sf::Color::Red);
}


PointsConsumable::~PointsConsumable()
{
}
