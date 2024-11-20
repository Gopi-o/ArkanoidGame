#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace ArkanoidGame
{
	Game::Game()
	{
		// Generate fake records table
		recordsTable =
		{
			{"John", MAX_APPLES / 2},
			{"Jane", MAX_APPLES / 3 },
			{"Alice", MAX_APPLES / 4 },
			{"Bob", MAX_APPLES / 5 },
			{"Clementine", MAX_APPLES / 5 },
		};

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(GameStateType::MainMenu);

	}

	Game::~Game()
	{
		ShutdownGame();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (gameStateStack.size() > 0)
			{
				gameStateStack.back().HandleWindowEvent(event);
			}
		}
	}

	bool Game::UpdateGame(float timeDelta)
	{
		if (gameStateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (gameStateStack.size() > 0)
			{
				gameStateStack.pop_back();
			}
		}
		else if (gameStateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (gameStateStack.size() > 0)
			{
				gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			gameStateStack.push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));
		}

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (gameStateStack.size() > 0)
		{
			gameStateStack.back().Update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::DrawGame(sf::RenderWindow& window)
	{
		if (gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = gameStateStack.rbegin(); it != gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->bIsExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::ShutdownGame()
	{
		// Shutdown all game states
		while (gameStateStack.size() > 0)
		{
			gameStateStack.pop_back();
		}

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushGameState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		gameStateChangeType = GameStateChangeType::Push;
	}

	void Game::PopGameState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchGameState(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = GameStateChangeType::Switch;
	}

	void Game::SetOption(GameOptions option, bool value)
	{

		if (value)
		{
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else
		{
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}

	}

	int Game::GetRecordsByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}


	bool Game::IsEnableOptions(GameOptions option)
	{
		bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}
}
