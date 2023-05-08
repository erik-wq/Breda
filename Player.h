#pragma once
#include "LevelObject.h"

namespace Tmpl8 {
	class Sprite;
	class Surface;
	class vec2;

	class Player : public LevelObject
	{
	public:
		Player();
		~Player();
		void StartMove();
		void Stop();
		void Move();
		void Player::UpdateDirection(vec2* cursor);
		void Bounce(vec2* CollisionPoint);
	private:
		int speed;
		bool moving;
		vec2* direction;
	};
}