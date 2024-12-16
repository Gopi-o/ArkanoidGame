#include "Block.h"
#include "Sprite.h"
#include "GameSettings.h"

#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
	const std::string TWO_TEXTURE_ID = "main";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
	{
		sprite.setColor(color);
	}

	bool Block::GetCollision(std::shared_ptr<IColladiable> collidableObject) const {
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit()
	{
		hitCount = 0;

	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	void Block::Update(float timeDelta)
	{

	}

	Block::~Block() {

	}





	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f position, const sf::Color& color)
		: Block(position, color)
		, color(color)
	{
	}

	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<IColladiable> collidableObject) const
	{
		if (isTimerStarted)
		{
		return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}


	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(BREAK_DELAY);
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}






	UnBreakableBlock::UnBreakableBlock(const sf::Vector2f position)
		: Block(position, sf::Color::Color(105, 105, 105))
	{
	}

	void UnBreakableBlock::OnHit()
	{
	}






	StrongDestroyableBlock::StrongDestroyableBlock(const sf::Vector2f position, const sf::Color& color)
		: Block(position, color)
		, color(color)
	{
	}

	void StrongDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool StrongDestroyableBlock::GetCollision(std::shared_ptr<IColladiable> collidableObject) const
	{
		if (isTimerStarted)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void StrongDestroyableBlock::FinalAction()
	{
		--hitCount_;
	}

	void StrongDestroyableBlock::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}

	void StrongDestroyableBlock::ChangeColorForHit()
	{
		if (hitCount_ > 2)
		{
			int red = rand() % 256;  
			int green = rand() % 256;
			int blue = rand() % 256;

			sprite.setColor(sf::Color(red, green, blue));
		}
		else
		{
			sprite.setColor(sf::Color::Cyan);
		}

	}

	void StrongDestroyableBlock::OnHit()
	{
		if (hitCount_ == 2)
		{
			StartTimer(BREAK_DELAY);
		}
		--hitCount_;
		ChangeColorForHit();
	}

	bool StrongDestroyableBlock::IsBroken()
	{
		return hitCount_ <= 0;
	}




	GlassDestroyableBlock::GlassDestroyableBlock(const sf::Vector2f position, const sf::Color& color)
		: Block(position, color)
		, color(color)
	{
	}
	void GlassDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}
	bool GlassDestroyableBlock::GetCollision(std::shared_ptr<IColladiable> collidableObject) const
	{
		if (isTimerStarted)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}
	void GlassDestroyableBlock::FinalAction()
	{
		--hitCount;
	}
	void GlassDestroyableBlock::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}


	void GlassDestroyableBlock::OnHit()
	{
		StartTimer(BREAK_DELAY);


	}
}