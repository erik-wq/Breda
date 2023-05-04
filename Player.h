#pragma once

namespace Tmpl8 {
	class Vector2;
	class Sprite;
	class Surface;

	class Player
	{
	public:
		Player();
		void StartMove();
		void Stop();
		void Move(Vector2* CursorPos);
		void Update(Surface* screen);
		~Player();
	private:
		int speed;
		bool moving;
		Vector2 *position;
		Sprite *picture;
	};
}