#include "Player.h"
#include "surface.h"
#include <stdio.h>
#include "template.h"


namespace Tmpl8 {

	Player::Player()
	{
		speed = 1;
		moving = false;
		position = new vec2(50, 50);
		picture = new Sprite(new Surface("assets/aagun.tga"), 36);
		direction = new vec2(0, 0);
	}

	void Player::StartMove()
	{
		moving = true;
	}

	void Player::Stop()
	{
		moving = false;
	}
	void Player::Move()
	{
		if (!moving)
		{
			return;
		}
		position->x += direction->x;
		position->y += direction->y;
	}

	void Player::Update(Surface* screen)
	{
		// position of object is in midle of object, simulationg pivot
		picture->Draw(screen, 
			position->x - picture->GetWidth() / 2, 
			position->y - picture->GetHeight() / 2);
	}

	void Player::UpdateDirection(vec2* cursor)
	{
		direction->x = cursor->x - position->x;
		direction->y = cursor->y - position->y;
		direction->normalize();
	}
	
	Player::~Player()
	{
		delete(position);
	}
}
