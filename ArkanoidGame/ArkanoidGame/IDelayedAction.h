#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanoidGame
{
	class IDelayedAtion
	{
	protected:
		bool isTimerStarted = false;
		float destroyTime_ = 0;
		float currentTime_ = 0;

		virtual void UpdateTimer(float deltaTime)
		{
			if (!isTimerStarted)
				return;
			currentTime_ -= deltaTime;
			EachTickAction(deltaTime);
			if (currentTime_ <= 0)
			{
				FinalAction();
				isTimerStarted = false;
			}
		}

		virtual void FinalAction() = 0;
		virtual void EachTickAction(float deltaTime) = 0;
	public:
		void StartTimer(float destroyTime)
		{
			destroyTime_ = destroyTime;
			currentTime_ = destroyTime;
			isTimerStarted = true;
		}
	};
}