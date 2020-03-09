#pragma once
#include "TimeConsumable.h"
#include "PointsConsumable.h"
#include "Player.h"
#include "GameLevel.h"
#include <time.h>
#include <random>
#include "Button.h"
#include "Main_Menu.h"
#include "GameOver.h"
#include "Pause.h"
class Game
{
private:
	enum GameState {
		Uninitialized, Playing, Paused, Game_Over, Minimized
	} current_state = GameState::Uninitialized;
	GameState state_before_focus = current_state;
	int screenHeight = 720, screenWidth = 1080;
	Player snake;
	int player_count = 1;
	sf::RenderWindow window;
	sf::Clock moveClock;
	sf::Clock foodClock;
	float moveDelay = 0.3f;
	float foodCheckDelay = 2.0f;
	std::vector<PointsConsumable> PointsConsumables;
	std::vector<TimeConsumable> TimeConsumables;
	std::vector<sf::Vector2f> consumablesPositions;
	int maxPointConsumables = 8;
	sf::Font menuFont;
	int waterThreshold = 1500;
	GameLevel level = GameLevel(screenWidth, screenHeight);

	float breathUpdateInterval = 2.0f;
	sf::Clock breathUpdateClock;

	Main_Menu main_menu{ "Snektacular Game", menuFont, sf::Vector2f(screenWidth / 2, screenHeight / 2) };
	Pause pause_menu{ "Pause", menuFont, sf::Vector2f(screenWidth/2, screenHeight/2) };
	GameOver game_over{ "Game Over", menuFont, sf::Vector2f(screenWidth / 2, screenHeight / 2) };

	void GameLogic();
	void GameOverHandler();
	void PauseMenuHandler();
	void MainMenuHandler();
	void Restart();
	void QuitGame();
public:
	void MainLoop();
	void InitFood();
	void CheckFood();
	void CheckSnakeFoodCollision();
	bool CheckSnakeLevelCollision();
	Game();
	~Game();
};

