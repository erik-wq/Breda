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
		float Move();
		void UpdateDirection(vec2* cursor);
		void Bounce(vec2* CollisionPoint);
		void Death();
		void Revive();
		bool live() { return !death; }
		void Slow();
	private:
		bool death;
		int speed;
		bool moving;
		bool slowed;
		vec2* direction;
	};
}