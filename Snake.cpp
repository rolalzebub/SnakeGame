#include "Snake.h"



void Snake::UpdateBreath()
{
	remainingBreath -= breathStep;
}

void Snake::RefillBreath()
{
	remainingBreath = maxBreathCapacity;
}

float Snake::GetRemainingBreath()
{
	return remainingBreath;
}

void Snake::ChangeDirection(Direction new_dir) {		//Changes the movement direction based on input received
	
	if (current_dir != new_dir &&
		directionChangePending == false) {
		directionChangePending = true;
		current_dir = new_dir;
		snakeBody[0].facing = new_dir;
	}
}

void Snake::Move(sf::Clock& moveClock) {	//Performs movement based on which direction the snake is facing
	
	if (remainingBreath <= 0.0f) {
		Death();
		return;
	}
	
	if (CheckBodyCollision()) {

		for (int i = snake_length - 1; i > 0; i--) {
			snakeBody[i].position = snakeBody[i - 1].position;
			snakeBody[i].facing = snakeBody[i - 1].facing;
		}

		switch (snakeBody[0].facing) {
		case Direction::Right:
			snakeBody[0].position.x += snakePart_width;
			break;
		case Direction::Down:
			snakeBody[0].position.y += snakePart_width;
			break;
		case Direction::Left:
			snakeBody[0].position.x -= snakePart_width;
			break;
		case Direction::Up:
			snakeBody[0].position.y -= snakePart_width;
			break;
		}

		for (int i = 0; i < snake_length; i++) {
			snakeBody[i].snakePart.setPosition(snakeBody[i].position);
			snakeBody[i].snakePart.setRotation(snakeBody[i].facing * 90);
		}
		moveClock.restart();
	}
	else {
		Death();
	}
	directionChangePending = false;
}

bool Snake::CheckBodyCollision() {		//Checks against self and updates body
	switch (current_dir) {
	case Direction::Right:
		if (snakeBody[0].position.x >= 1080)
			return false;
		for (int i = 1; i < snake_length; i++) {
			if (snakeBody[0].position.x + snakePart_width == snakeBody[i].position.x &&
				snakeBody[0].position.y == snakeBody[i].position.y) 
			{
				snake_length = snake_length - i;
				UpdateSnakeBody();
				return false;
			}
		}
		break;
	case Direction::Down:
		if (snakeBody[0].position.y >= 720)
			return false;
		for (int i = 1; i < snake_length; i++) {
			if (snakeBody[0].position.y + snakePart_width == snakeBody[i].position.y &&
				snakeBody[0].position.x == snakeBody[i].position.x)
			{
				snake_length = snake_length - i;
				UpdateSnakeBody();
				return false;
			}
		}
		break;
	case Direction::Left:
		if (snakeBody[0].position.x <= 0)
			return false;
		for (int i = 1; i < snake_length; i++) {
			if (snakeBody[0].position.x - snakePart_width == snakeBody[i].position.x &&
				snakeBody[0].position.y == snakeBody[i].position.y)
			{
				snake_length = snake_length - i;
				UpdateSnakeBody();
				return false;
			}
		}
		break;
	case Direction::Up:
		if (snakeBody[0].position.y <= 0)
			return false;
		for (int i = 1; i < snake_length; i++) {
			if (snakeBody[0].position.y - snakePart_width == snakeBody[i].position.y &&
				snakeBody[0].position.x == snakeBody[i].position.x)
			{
				snake_length = snake_length - i;
				UpdateSnakeBody();
				return false;
			}
		}
		break;
	}
	return true;
}

void Snake::UpdateSnakeBody()		//Changes the size of the snake when needed
{
	if (snake_length < 3) {
		Death();
		return;
	}
	if (snakeBody.size() < snake_length) {
		int fill_start = snakeBody.size();
		snakeBody.resize(snake_length);
		for (int i = fill_start; i < snake_length; i++) {
			snakeBody[i].snakePart = sf::RectangleShape(sf::Vector2f(snakePart_width, snakePart_height));
			snakeBody[i].snakePart.setOrigin(snakePart_width / 2, snakePart_height / 2);
			snakeBody[i].facing = snakeBody[i - 1].facing;
			snakeBody[i].position = snakeBody[i - 1].position;
			switch (snakeBody[i].facing) {
			case Direction::Right:
				snakeBody[i].position.x -= snakePart_width;
				snakeBody[i].snakePart.setRotation(0);
				break;
			case Direction::Down:
				snakeBody[i].position.y += snakePart_height;
				snakeBody[i].snakePart.setRotation(90);
				break;
			case Direction::Left:
				snakeBody[i].position.x += snakePart_width;
				snakeBody[i].snakePart.setRotation(180);
				break;
			case Direction::Up:
				snakeBody[i].position.y -= snakePart_height;
				snakeBody[i].snakePart.setRotation(270);
				break;
			}
			snakeBody[i].snakePart.setPosition(snakeBody[i].position);
		}
	}
	else if (snakeBody.size() > snake_length) {
		snakeBody.resize(snake_length);
	}
}

void Snake::DrawSnake(sf::RenderWindow& window)
{
	for (int i = 0; i < snakeBody.size(); i++) {
		snakeBody[i].snakePart.setFillColor(sf::Color::Blue);
		snakeBody[i].snakePart.setOutlineColor(sf::Color::White);
		snakeBody[i].snakePart.setOutlineThickness(1);

		window.draw(snakeBody[i].snakePart);
	}
}

void Snake::Death()
{
	cout << "Snake dead";
	isAlive = false;
}

Snake::Snake()
{
	isAlive = true;
	snakeBody.resize(snake_length);
	snakeBody[0].position = default_position;
	for (int i = 0; i < snake_length; i++) {
		snakeBody[i].snakePart = sf::RectangleShape(sf::Vector2f(snakePart_width, snakePart_height));
		snakeBody[i].facing = Direction::Right;
		snakeBody[i].position = default_position;
		snakeBody[i].position.x -= i * snakePart_width;
		snakeBody[i].snakePart.setPosition(snakeBody[i].position);
		snakeBody[i].snakePart.setOrigin(snakePart_width / 2, snakePart_height / 2);
	}
}


Snake::~Snake()
{
}
