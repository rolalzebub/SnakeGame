#include "GameLevel.h"

GameLevel::GameLevel(int screenWidth, int screenHeight)
{
	wall_width = screenWidth / 50;
	wall_height = screenHeight * 0.75f;

	wall_left = sf::RectangleShape(sf::Vector2f(wall_width, wall_height));
	wall_bottom = sf::RectangleShape(sf::Vector2f(screenWidth, wall_width));
	wall_right = sf::RectangleShape(sf::Vector2f(wall_width, wall_height + 45));

	wall_left.setOrigin(wall_width / 2, wall_height / 2);
	wall_bottom.setOrigin(screenWidth / 2, wall_width / 2);
	wall_right.setOrigin(wall_width / 2, wall_height / 2);

	wall_left.setPosition(sf::Vector2f(0 + (wall_width / 2), screenHeight / 1.8));
	wall_bottom.setPosition(sf::Vector2f(screenWidth / 2, screenHeight - (wall_width / 2)));
	wall_right.setPosition(sf::Vector2f(screenWidth - (wall_width / 2), screenHeight / 1.8));

	wall_left.setFillColor(sf::Color::Green);
	wall_left.setOutlineColor(sf::Color::White);
	wall_left.setOutlineThickness(3);
	wall_bottom.setFillColor(sf::Color::Green);
	wall_bottom.setOutlineColor(sf::Color::White);
	wall_bottom.setOutlineThickness(3);
	wall_right.setFillColor(sf::Color::Green);
	wall_right.setOutlineColor(sf::Color::White);
	wall_right.setOutlineThickness(3);

	water_height = wall_height;
	water = sf::RectangleShape(sf::Vector2f(screenWidth, water_height));
	water.setPosition(0, screenHeight / 4.5);
	water.setFillColor(sf::Color(135, 206, 250, 180));
	water.setOrigin(0, water.getLocalBounds().top);
	water.setOutlineThickness(20);
	water.setOutlineColor(sf::Color::White);
}

void GameLevel::DrawLevel(sf::RenderWindow& window) {
	window.draw(water);
	window.draw(wall_left);
	window.draw(wall_right);
	window.draw(wall_bottom); 
}

int GameLevel::GetWaterLevel() {
	return water.getGlobalBounds().top;
}

int GameLevel::GetSurfaceZone()
{
	return breathRefillZoneHeight;
}

void GameLevel::UpdateLevel()
{
	if (waterUpdateClock.getElapsedTime().asSeconds() < waterUpdateTime) {
		return;
	}

	else {
		water.setPosition(sf::Vector2f(water.getPosition().x, water.getPosition().y + waterHeightStep));
		waterUpdateClock.restart();
	}
}

sf::FloatRect GameLevel::GetLevelBounds() {
	sf::FloatRect level_bounds;
	level_bounds.top = water.getGlobalBounds().top;
	level_bounds.left = wall_left.getGlobalBounds().width;
	level_bounds.width = wall_right.getGlobalBounds().left;
	level_bounds.height = wall_bottom.getGlobalBounds().top;

	return level_bounds;
}

GameLevel::~GameLevel()
{
}
