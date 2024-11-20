#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushGameState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			platform.SetDirection(PlatformDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			platform.SetDirection(PlatformDirection::Left);
		}

		// Update Platform
		platform.MovePlatform(timeDelta);
		ball.Update(timeDelta, platform);

		Game& game = Application::Instance().GetGame();

		const bool isGameFinished = numEatenApples == MAX_APPLES && !Application::Instance().GetGame().IsEnableOptions(GameOptions::InfiniteApples);
		
		if (isGameFinished
			//|| !HasSnakeCollisionWithRect(snake.body, background.getGlobalBounds()) 
			|| !platform.HasCollisionWithRect(background.getGlobalBounds())  // Check collision with screen border
			|| ball.HasCollisionWithBottom(background.getGlobalBounds().top + background.getGlobalBounds().height))

		{
			gameOverSound.play();

			Game& game = Application::Instance().GetGame();

			// Find snake in records table and update his score
			game.UpdateRecord(PLAYER_NAME, numEatenApples);
			Application::Instance().GetGame().PushGameState(GameStateType::GameOver, false);
		}

		scoreText.setString("Apples eaten: " + std::to_string(numEatenApples));
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw snake DrawSnake(snake, window);
		// Draw Platform
		platform.DrawPlatform(window);
		// Draw Ball
		ball.Draw(window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
