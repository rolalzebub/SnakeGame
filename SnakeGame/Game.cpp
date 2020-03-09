#include "Game.h"


void Game::MainLoop() {

	while (window.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					if (current_state == GameState::Paused) {
						current_state = GameState::Playing;
					}
					else if (current_state == GameState::Playing) {
						current_state = GameState::Paused;
					}
					break;
				case sf::Keyboard::Up:
				case sf::Keyboard::Down:
					if (current_state == GameState::Game_Over) {
						game_over.ChangeSelected();
					}
					else if (current_state == GameState::Paused) {
						pause_menu.ChangeSelected(event.key.code);
					}
					else if (current_state == GameState::Uninitialized) {
						main_menu.ChangeSelected();
					}
					break;
				case sf::Keyboard::Return:
					if (current_state == GameState::Game_Over) {
						GameOverHandler();
					}
					else if (current_state == GameState::Paused) {
						PauseMenuHandler();
					}
					else if (current_state == GameState::Uninitialized) {
						MainMenuHandler();
					}
					break;
				default:
					if (current_state == GameState::Playing) {
						snake.InputHandler(event.key);
					}
					break;
				}
				break;
			case sf::Event::LostFocus:
				state_before_focus = current_state;
				current_state = GameState::Minimized;
				break;
			case sf::Event::GainedFocus:
				current_state = state_before_focus;
				break;
			default:
				break;
			}
		}
		window.clear();
		switch (current_state) {					//Game State conditioning
		case GameState::Uninitialized:
		{
			main_menu.RenderMenu(window);
			break;
		}
		case GameState::Playing:
		{
			GameLogic();
			break;
		}
		case GameState::Game_Over:
		{
			game_over.RenderMenu(window);
			break;
		}
		case GameState::Paused:
			pause_menu.RenderMenu(window);
			break;
		}

		window.display();

	}
}

void Game::GameLogic() {			//Core game logic
	
	if (level.GetWaterLevel() > waterThreshold ||				//Check for game over
		snake.GetAlive() == false) {
		game_over.SetScore(snake.getScore());
		current_state == GameState::Game_Over;
		return;
	}
	level.UpdateLevel();		
	level.DrawLevel(window);
	if (breathUpdateClock.getElapsedTime().asSeconds() > breathUpdateInterval) {			//Check for snake breath update
		snake.UpdateBreath();
		breathUpdateClock.restart();
	}
	if (moveClock.getElapsedTime().asSeconds() >= moveDelay)				//Check for snake movement interval and level collisions to allow movement
	{
		snake.Move(moveClock);
		CheckSnakeLevelCollision();
	}
	snake.DrawSnake(window);
	snake.RenderDetails(window);
	CheckSnakeFoodCollision();
	CheckFood();
	for (int i = 0; i < PointsConsumables.size(); i++) {
		if (PointsConsumables[i].GetActiveStatus())					//Check if the food is all active
			PointsConsumables[i].RenderFood(window);
	}
	for (int i = 0; i < TimeConsumables.size(); i++)
	{
		if (TimeConsumables[i].GetActiveStatus()) {
			TimeConsumables[i].RenderFood(window);
		}
	}
}


void Game::InitFood()				//Scatter food across the level initially
{
	srand((unsigned int) time(NULL));
	int pointsFood = (rand() % 5) + 1;
	int timeFood = (rand() % 5) + 1;
	sf::Vector2f foodPos;
	PointsConsumables.clear();
	sf::FloatRect level_bounds = level.GetLevelBounds();
	for (int i = 0; i < maxPointConsumables; i++) {

		foodPos.x = (float) (rand() % (screenWidth));
		foodPos.x -= (int) foodPos.x % 10;
		foodPos.y = (float) (rand() % screenHeight);
		foodPos.y -= (int) foodPos.y % 10;
		for (int j = 0; j < PointsConsumables.size(); j++) {
			while (foodPos == PointsConsumables[j].GetPosition() ||
				foodPos.x < level_bounds.left ||
				foodPos.y < level_bounds.top) {
				foodPos.x = (float) (rand() % (int) level_bounds.width);
				foodPos.x -= (int) foodPos.x % 10;
				foodPos.y = (float) (rand() % (int) level_bounds.height);
				foodPos.y -= (int) foodPos.y % 10;
			}
		}
		PointsConsumable foodPiece;
		foodPiece.SetPosition(foodPos);
		PointsConsumables.push_back(foodPiece);
		consumablesPositions.push_back(foodPos);
	}
	TimeConsumables.clear();
	for (int i = 0; i < timeFood; i++) {

		foodPos.x = (float) (rand() % screenWidth);
		foodPos.x -= (int) foodPos.x % 10;
		foodPos.y = (float) (rand() % screenHeight);
		foodPos.y -= (int) foodPos.y % 10;
		for (int j = 0; j < TimeConsumables.size(); j++) {
			while (foodPos == TimeConsumables[j].GetPosition() ||
				foodPos.x < level_bounds.left ||
				foodPos.y < level_bounds.top) {
				foodPos.x = (float)(rand() % (int)level_bounds.width);
				foodPos.x -= (int)foodPos.x % 10;
				foodPos.y = (float)(rand() % (int)level_bounds.height);
				foodPos.y -= (int)foodPos.y % 10;
			}
		}
		TimeConsumable foodPiece;
		foodPiece.SetPosition(foodPos);
		TimeConsumables.push_back(foodPiece);
		consumablesPositions.push_back(foodPos);
	}
}

void Game::CheckFood() {				//Check if all food pieces are in valid positions
	sf::FloatRect level_bounds = level.GetLevelBounds();
	if (foodClock.getElapsedTime().asSeconds() >= foodCheckDelay) {
		int SpeedOrPoints = rand() % 2;
		switch (SpeedOrPoints) {
		case 0:
			if(moveDelay > 0.2f){
				for (int i = 0; i < TimeConsumables.size(); i++) {
					if (TimeConsumables[i].GetActiveStatus() == false) {
						TimeConsumables[i].SetActiveStatus(true);
						sf::Vector2f foodPos;
						foodPos.x = (float)(rand() % (int)level_bounds.width);
						foodPos.x -= (int)foodPos.x % 10;
						foodPos.y = (float)(rand() % (int)level_bounds.height);
						foodPos.y -= (int)foodPos.y % 10;
						for (int j = 0; j < TimeConsumables.size(); j++) {
							while (foodPos == TimeConsumables[j].GetPosition() ||
								foodPos.x < level_bounds.left ||
								foodPos.y < level_bounds.top) {
								foodPos.x = (float)(rand() % (int)level_bounds.width);
								foodPos.x -= (int)foodPos.x % 10;
								foodPos.y = (float)(rand() % (int)level_bounds.height);
								foodPos.y -= (int)foodPos.y % 10;
							}
						}
						TimeConsumables[i].SetPosition(foodPos);
						break;
					}
				}
			}
			foodClock.restart();
			break;
		case 1:
			for (int i = 0; i < PointsConsumables.size(); i++) {
				if (PointsConsumables[i].GetActiveStatus() == false) {
					PointsConsumables[i].SetActiveStatus(true);
					sf::Vector2f foodPos;
					foodPos.x = (float)(rand() % (int)level_bounds.width);
					foodPos.x -= (int)foodPos.x % 10;
					foodPos.y = (float)(rand() % (int)level_bounds.height);
					foodPos.y -= (int)foodPos.y % 10;
					for (int j = 0; j < PointsConsumables.size(); j++) {
						while (foodPos == PointsConsumables[j].GetPosition() ||
							foodPos.x < level_bounds.left ||
							foodPos.y < level_bounds.top) {
							foodPos.x = (float)(rand() % (int)level_bounds.width);
							foodPos.x -= (int)foodPos.x % 10;
							foodPos.y = (float)(rand() % (int)level_bounds.height);
							foodPos.y -= (int)foodPos.y % 10;
						}
					}
					PointsConsumables[i].SetPosition(foodPos);
					break;
				}
			}
			foodClock.restart();
			break;
		}
	}
}

void Game::CheckSnakeFoodCollision()
{
	sf::Vector2f snakePos = snake.GetHeadPosition();
	for (int i = 0; i < PointsConsumables.size(); i++)
	{
		if (snakePos == PointsConsumables[i].GetPosition() &&
			PointsConsumables[i].GetActiveStatus() == true) {
			PointsConsumables[i].Consumed();
			snake.PointScored();
		}
	}
	for (int i = 0; i < TimeConsumables.size(); i++)
	{
		if (snakePos == TimeConsumables[i].GetPosition() &&
			TimeConsumables[i].GetActiveStatus() == true) {
			TimeConsumables[i].Consumed();
			snake.PointScored();
			moveDelay -= 0.05f;
		}
	}
}


bool Game::CheckSnakeLevelCollision()
{
	sf::Vector2f snakePos = snake.GetHeadPosition();
	sf::FloatRect level_bounds = level.GetLevelBounds();

	if (snakePos.x <= level_bounds.left ||
		snakePos.x >= level_bounds.width ||
		snakePos.y >= level_bounds.height) {
		
		game_over.SetScore(snake.getScore());
		snake.Death();
		current_state = GameState::Game_Over;
		return false;
	}

	else if (snakePos.y <= level_bounds.top + level.GetSurfaceZone() + 1 &&
		snakePos.y >= level_bounds.top) {
		snake.RefillBreath();
	}

	else if (snakePos.y < level_bounds.top) {
		game_over.SetScore(snake.getScore());
		snake.Death();
		current_state = GameState::Game_Over;
		return false;
	}

	return true;
}

void Game::GameOverHandler() {
	GameOver::SelectedOption option = game_over.SelectOption();
	game_over.ResetState();
	switch (option) {
	case GameOver::SelectedOption::Restart:
		Restart();
		break;
	case GameOver::SelectedOption::Quit:
		current_state = GameState::Uninitialized;
		break;
	}
}

void Game::PauseMenuHandler()
{
	Pause::SelectedOption option = pause_menu.SelectOption();
	pause_menu.ResetState();
	switch (option) {
	case Pause::SelectedOption::Continue:
		current_state = GameState::Playing;
		break;
	case Pause::SelectedOption::Restart:
		Restart();
		break;
	case Pause::SelectedOption::Quit:
		current_state = GameState::Uninitialized;
		break;
	}
}

Game::Game()
{
	window.create(sf::VideoMode(screenWidth, screenHeight), "C++ Snake ICA : V8179602");
	window.setFramerateLimit(60);
	menuFont.loadFromFile("Montserrat-Regular.ttf");
	
	InitFood();

}

void Game::MainMenuHandler()
{
	Main_Menu::SelectedOption option = main_menu.SelectOption();
	main_menu.ResetState();
	switch (option) {
	case Main_Menu::SelectedOption::Play: {
		Restart();
		break;
	}
	case Main_Menu::SelectedOption::Quit: {
		window.close();
		break;
	}
	}
}

void Game::Restart()
{
	snake = Player();
	level = GameLevel(screenWidth, screenHeight);
	InitFood();
	current_state = GameState::Playing;
}

void Game::QuitGame()
{
}

Game::~Game()
{
}
