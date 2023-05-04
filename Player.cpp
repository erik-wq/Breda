#include "Player.h"
#include "Vector2.h"
#include "surface.h"
#include <stdio.h>

namespace Tmpl8 {

	Player::Player()
	{
		speed = 1;
		moving = false;
		position = new Vector2(50, 50);
		picture = new Sprite(new Surface("assets/aagun.tga"), 36);
	}

	void Player::StartMove()
	{
		moving = true;
	}

	void Player::Stop()
	{
		moving = false;
	}
	void Player::Move(Vector2* CursorPos)
	{
		if (!moving)
		{
			return;
		}
		Vector2 direction = *CursorPos - *position;
		direction.normalize();
		position->x += direction.x;
		position->y += direction.y;
	}

	void Player::Update(Surface* screen)
	{
		picture->Draw(screen, position->x, position->y);
	}
	
	Player::~Player()
	{
		delete(position);
	}
}
