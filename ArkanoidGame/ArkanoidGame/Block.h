#pragma once
#include "Ball.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "IDelayedAction.h"

namespace ArkanoidGame
{
	class Block : public GameObject, public IColladiable
	{
	protected:
		void OnHit();
		int hitCount = 1;
	public:
		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		virtual ~Block();
		bool GetCollision(std::shared_ptr<IColladiable> collidableObject) const override;
		void Update(float timeDelta) override;
		virtual bool IsBroken();
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAtion
	{
	protected:
		void OnHit() override;
		sf::Color color;

	public:
		SmoothDestroyableBlock(const sf::Vector2f position, const sf::Color& color = sf::Color::Cyan);
		~SmoothDestroyableBlock() = default;

		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<IColladiable> collidableObject) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;

	};

	class UnBreakableBlock : public Block
	{
	public:
		UnBreakableBlock(const sf::Vector2f position);
		
		void OnHit() override;
		void Update(float) {
			int i = 0;
			++i;
		}
	};


	class StrongDestroyableBlock : public Block, public IDelayedAtion
	{
	protected:
		void OnHit() override;
		sf::Color color;
		int hitCount_ = 4;

	public:
		StrongDestroyableBlock(const sf::Vector2f position, const sf::Color& color = sf::Color::Magenta);
		~StrongDestroyableBlock() = default;

		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<IColladiable> collidableObject) const override;
		bool IsBroken() override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;

		void ChangeColorForHit();
	};

	class GlassDestroyableBlock : public Block, public IDelayedAtion
	{
	protected:
		void OnHit() override;
		sf::Color color;

	public:
		GlassDestroyableBlock(const sf::Vector2f position, const sf::Color& color = sf::Color::Yellow);
		~GlassDestroyableBlock() = default;

		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<IColladiable> collidableObject) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;

	};
}

