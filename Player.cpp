#include "Player.h"
#include "surface.h"
#include <stdio.h>
#include "template.h"
#include "CircleCollider.h"


namespace Tmpl8 {

	Player::Player() : SceneObject()
	{
		speed = 1;
		moving = false;
		picture = new Sprite(new Surface("assets/Player.png"), 4);
		printf("%d %d\n", picture->GetWidth(), picture->GetHeight());
		direction = new vec2(0, 0);
		collider = new CircleCollider(20);
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

	void Player::Render(Surface* screen)
	{
		picture->SetFrame(2);
		vec2* pos = GlobalPosition();
		// position of object is in midle of object, simulationg pivot
		picture->Draw(screen, 
			pos->x - picture->GetWidth() / 2, 
			pos->y - picture->GetHeight() / 2);
		delete(pos);
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
