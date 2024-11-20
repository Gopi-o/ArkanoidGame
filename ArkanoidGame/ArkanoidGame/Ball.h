#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Platform.h"

namespace ArkanoidGame
{
	class Ball
	{
	public:
		Ball();
		void Update(float deltaTime, const Platform& platform);
		void Draw(sf::RenderWindow& window);
		bool HasCollisionWithBottom(float windowHeight) const {
			sf::FloatRect ballBounds = shape.getGlobalBounds();
			return (ballBounds.top + ballBounds.height >= windowHeight); // Проверка падения мяча
		}

		sf::FloatRect GetBounds() const {
			return shape.getGlobalBounds();
		}

	private:
		sf::CircleShape shape;
		sf::Vector2f velocity;
	};
}

