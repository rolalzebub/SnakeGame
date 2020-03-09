#pragma once
#include<SFML/Graphics.hpp>
class GameLevel
{
private:
	sf::RectangleShape wall_left, wall_bottom, wall_right, water;
	int wall_height = 0, wall_width = 0;
	float waterUpdateTime = 2.0f;
	sf::Clock waterUpdateClock;
	int water_height;
	int waterHeightStep = 10;
	int breathRefillZoneHeight = 10;
public:
	GameLevel(int screenWidth, int screenHeight);
	void DrawLevel(sf::RenderWindow& window);
	int GetWaterLevel();
	int GetSurfaceZone();
	void UpdateLevel();
	~GameLevel();
	sf::FloatRect GetLevelBounds();
};