#include "Player.h"


void Player::InputHandler(sf::Event::KeyEvent keyPress)
{
	if (keyPress.code == sf::Keyboard::W &&
		current_dir != Direction::Down) {
		ChangeDirection(Direction::Up);
	}
	else if (keyPress.code == sf::Keyboard::A &&
		current_dir != Direction::Right) {
		ChangeDirection(Direction::Left);
	}
	else if (keyPress.code == sf::Keyboard::S &&
		current_dir != Direction::Up) {
		ChangeDirection(Direction::Down);
	}
	else if (keyPress.code == sf::Keyboard::D &&
		current_dir != Direction::Left) {
		ChangeDirection(Direction::Right);
	}
}

void Player::PointScored()
{
	score++;
	snake_length++;
	UpdateSnakeBody();
}

void Player::RenderDetails(sf::RenderWindow & window)
{
	sf::Text score_header = sf::Text("Score:", font);
	sf::Text score_text = sf::Text(std::to_string(score), font);
	score_header.setPosition(score_display_position);
	score_text.setPosition(sf::Vector2f(score_display_position.x, score_display_position.y + 3));
	score_header.setCharacterSize(10);
	score_text.setCharacterSize(20);

	sf::Text breath_header = sf::Text("Breath", font);
	sf::Text breath_text = sf::Text(std::to_string((int) Snake::remainingBreath), font);
	breath_header.setPosition(breath_display_position);
	breath_text.setPosition(sf::Vector2f(breath_display_position.x, breath_display_position.y + 3));
	breath_header.setCharacterSize(10);
	breath_text.setCharacterSize(20);

	window.draw(breath_header);
	window.draw(breath_text);
	window.draw(score_header);
	window.draw(score_text);
}

sf::Vector2f Player::GetHeadPosition()
{
	return snakeBody[0].position;
}

Player::Player()
{
	font.loadFromFile("Montserrat-Regular.ttf");
}


Player::~Player()
{
}