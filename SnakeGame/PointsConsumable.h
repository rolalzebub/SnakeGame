#pragma once
#include "Food.h"
class PointsConsumable: public Food
{
public:
	void Consumed();
	PointsConsumable();
	~PointsConsumable();
};

