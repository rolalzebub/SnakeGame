#pragma once
#include "Food.h"
class TimeConsumable: public Food
{
public:
	void Consumed();
	TimeConsumable();
	~TimeConsumable();
};

