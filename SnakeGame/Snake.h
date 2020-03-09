#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

using namespace std;

enum Direction {
	Right, Down, Left, Up
};
class Snake
{
	struct SnakeNode {
		sf::RectangleShape snakePart = sf::RectangleShape(sf::Vector2f(20, 5));
		Direction facing;
		sf::Vector2f position;
	};
protected:
	Direction current_dir = Direction::Right;
	int snake_length = 4;
	int snakePart_width = 10, snakePart_height = 10;
	float moveDelay = 0.5f;
	std::vector<SnakeNode> snakeBody;
	sf::Vector2f default_position{40,240};
	bool CheckBodyCollision();
	bool directionChangePending = false;
	int maxBreathCapacity = 10;
	float remainingBreath = maxBreathCapacity;
	float breathStep = 1;
	bool isAlive;
public:
	void UpdateBreath();
	void RefillBreath();
	float GetRemainingBreath();
	void ChangeDirection(Direction new_dir);
	void Move(sf::Clock& moveClock);
	void UpdateSnakeBody();
	void DrawSnake(sf::RenderWindow& window);
	void Death();
	bool GetAlive() { return isAlive; }
	Snake();
	~Snake();
};

