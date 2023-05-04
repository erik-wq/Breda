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
		void Move(vec2* CursorPos);
		void Update(Surface* screen);
		~Player();
	private:
		int speed;
		bool moving;
		vec2 *position;
		Sprite *picture;
	};
}