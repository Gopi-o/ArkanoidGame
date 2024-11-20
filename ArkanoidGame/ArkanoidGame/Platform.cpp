#include "Platform.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"


namespace ArkanoidGame
{
	Platform::Platform()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "platform.jpg"));

		InitSprite(sprite, PLATFORM_XSIZE, PLATFORM_YSIZE, texture);
		sprite.setPosition(INITIAL_POZITION);
		SetSpriteRelativeOrigin(sprite, 0.f, 0.f);
		velocity = { INITIAL_SPEED, -INITIAL_SPEED };
	}

	void Platform::MovePlatform(float deltaTime)
	{
		float movement = INITIAL_SPEED * deltaTime;

		if (direction == PlatformDirection::Right && sprite.getPosition().x < SCREEN_WIDTH - PLATFORM_XSIZE) {
			sprite.move(movement, 0);
		}
		else if (direction == PlatformDirection::Left && sprite.getPosition().x > 0)
		{
			sprite.move(-movement, 0);
		}
		else
		{
			sprite.move(0, 0);
		}

	}

	void Platform::DrawPlatform(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}

	void Platform::SetDirection(PlatformDirection ShareDirection)
	{
		direction = ShareDirection;
	}

	
}

