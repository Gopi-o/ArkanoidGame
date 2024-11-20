#include "Ball.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	Ball::Ball()
	{
		shape.setRadius(BALL_RADIUS);
		shape.setFillColor(sf::Color::Cyan);
		shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT / 2.f);
		velocity = { BALL_SPEED, -BALL_SPEED };

	}
	void Ball::Update(float deltaTime, const Platform& platform)
	{
		shape.move(velocity * deltaTime);

		sf::FloatRect ballBounds = shape.getGlobalBounds();
		sf::FloatRect platformBounds = platform.GetSprite().getGlobalBounds();

		if (shape.getPosition().x <= 0 || shape.getPosition().x + 2 * BALL_RADIUS >= SCREEN_WIDTH)
		{
			velocity.x = -velocity.y;
		}
		if (shape.getPosition().y <= 0)
		{
			velocity.y = -velocity.y;
		}

		//Check screen border 
		if (ballBounds.left <= 0.f) { // Left wall
			velocity.x = std::abs(velocity.x);
			shape.setPosition(0.f, ballBounds.top);
		}
		else if (ballBounds.left + ballBounds.width >= SCREEN_WIDTH) { // Right Wall
			velocity.x = -std::abs(velocity.x);
			shape.setPosition(SCREEN_WIDTH - (ballBounds.width), ballBounds.top);
		}
		if (ballBounds.top <= 0.f) { // Top Wall
			velocity.y = std::abs(velocity.y);
			shape.setPosition(ballBounds.left, 0.f);
		}

		//Check With platform intersection
		if (ballBounds.intersects(platformBounds)) {
			sf::Vector2f platformVelocity = platform.GetVelocity();

			shape.setPosition(ballBounds.left, platform.GetSprite().getPosition().y - ballBounds.height);

			// Change direction of the ball
			velocity.y = -std::abs(velocity.y); // rebound

			// Application speed of the platform
			velocity.x += platformVelocity.x * 1.f; // Reducing the reflection angle

			// Limit MaxSpeed
			float maxSpeed = 600.0f; // Max Speed
			float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
			if (speed > maxSpeed) {
				float ratio = maxSpeed / speed;
				velocity.x *= ratio;
				velocity.y *= ratio;
			}
		}

		//// Checking down outside the window
		//if (ballBounds.top + ballBounds.height >= SCREEN_HEGHT) {

		//	shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT / 2.f); 
		//	velocity = { BALL_SPEED, BALL_SPEED }; // Reset velocity vector
		//}
	}
	void Ball::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
}