#pragma once

namespace Tmpl8 {
	class Sprite;
	class Surface;
	class vec2;

	class Player
	{
	public:
		Player();
		void StartMove();
		void Stop();
		void Move();
		void Update(Surface* screen);
		void Player::UpdateDirection(vec2* cursor);
		~Player();
	private:
		int speed;
		bool moving;
		vec2 *position;
		Sprite *picture;
		vec2* direction;
	};
}