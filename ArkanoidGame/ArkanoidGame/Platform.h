#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

namespace ArkanoidGame
{
	enum class PlatformDirection
	{
		Stop = 0,
		Right,
		Left,
	};

	class Platform
	{
	public:
		Platform();


		void MovePlatform(float deltaTime);
		void DrawPlatform(sf::RenderWindow& window);
		bool HasCollisionWithRect(const sf::FloatRect& rect) const {
			return sprite.getGlobalBounds().intersects(rect);
		}

		void SetDirection(PlatformDirection direction);
		const sf::Vector2f& GetVelocity() const {
			return sf::Vector2f((direction == PlatformDirection::Left ? -INITIAL_SPEED : (direction == PlatformDirection::Right ? INITIAL_SPEED : 0)), 0);
		}
		const sf::Sprite& GetSprite() const {
			return sprite; 
		}


	private:
		sf::Sprite sprite;
		sf::Texture texture;
		PlatformDirection direction = PlatformDirection::Right;
		float SpeedX = 0.f;
		sf::Vector2f velocity;
	};
}


