#include "Player.h"
#include "surface.h"
#include <stdio.h>
#include <cmath>
#include "template.h"
#include "CircleCollider.h"
#include <SDL2-2.0.3/include/SDL_stdinc.h>


namespace Tmpl8 {

	Player::Player() : LevelObject()
	{
		speed = 1;
		moving = false;
		picture = new Sprite(new Surface("assets/Player.png"), 5);
		direction = new vec2(0, 0);
		collider = new CircleCollider(20);
	}

	Player::~Player()
	{
		delete(position);
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
		position->x += direction->x * speed;
		position->y += direction->y * speed;
	}

	void Player::UpdateDirection(vec2* cursor)
	{
		direction->x = cursor->x - position->x;
		direction->y = cursor->y - position->y;
		direction->normalize();
	}

	void Player::Bounce(vec2* CollisionPoint)
	{
		vec2* pos = GlobalPosition();
		float right = pos->x - CollisionPoint->x;
		float up = pos->y - CollisionPoint->y;
		if (right != 0 && up != 0)
		{
			*direction *= -1;
		}
		else if (right != 0)
		{
			direction->x *= -1;
		}
		else if (up != 0)
		{
			direction->y *= -1;
		}
		
		speed *= 2;
		Move();
		speed /= 2;
		delete(pos);
	}

}
