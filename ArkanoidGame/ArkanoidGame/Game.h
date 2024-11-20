#pragma once
#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Sprite.h"
#include "GameSettings.h"
#include "GameState.h"
#include <unordered_map>

namespace ArkanoidGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool UpdateGame(float timeDelta); // Return false if game should be closed
		void DrawGame(sf::RenderWindow& window);
		void ShutdownGame();

		bool IsEnableOptions(GameOptions option);
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordsByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);


		// Add new game state on top of the stack
		void PushGameState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopGameState();

		// Remove all game states from the stack and add new one
		void SwitchGameState(GameStateType newState);




	private:
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;
	};


}
