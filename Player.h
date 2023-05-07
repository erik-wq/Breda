#pragma once
#include "SceneObject.h"

namespace Tmpl8 {
	class Sprite;
	class Surface;
	class vec2;

	class Player : public SceneObject
	{
	public:
		Player();
		void StartMove();
		void Stop();
		void Move();
		void Render(Surface* screen);
		void Player::UpdateDirection(vec2* cursor);
		~Player();
	private:
		int speed;
		bool moving;
		Sprite *picture;
		vec2* direction;
	};
}