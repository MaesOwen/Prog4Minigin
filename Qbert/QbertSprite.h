#pragma once
#include <unordered_map>

#include "Sprite.h"

namespace dae
{
	class QbertSprite: public Sprite
	{
	public:
		enum class SpritePose
		{
			topLeftJump, topRightJump, botLeftJump, botRightJump,
			topLeftLand, topRightLand, botLeftLand, botRightLand,
			ballLand, ballJump
		};
		void Render() const override;
		
		QbertSprite(int spriteWidth, int spriteHeight);
		void UseSpritePose(SpritePose spritePose);
		void AddSpritePose(SpritePose spritePose, int frameNr);
		void SetIsBall(bool isBall);
		bool GetIsBall() const;

	private:
		int m_BaseSpriteHeight;
		std::unordered_map<SpritePose, int> m_SpritePosMap;
		bool m_IsBall;
	};
}
