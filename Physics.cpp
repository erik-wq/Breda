#include "Physics.h"
#include <cmath>
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include "SceneObject.h"
#include "template.h"

namespace Tmpl8
{
	bool Physics::CheckCollision(SceneObject* player, SceneObject* object)
	{
		if (player == nullptr || object == nullptr)
		{
			return false;
		}
		if (player->collider == nullptr || object->collider == nullptr)
		{
			return false;
		}
		if (object->collider->type == 0)
		{
			return CircleCollisionCheck(player, object);
		}
		else if (object->collider->type == 1)
		{
			return BoxCollisionCheck(player, object);
		}
		return false;
	}

	bool Physics::CircleCollisionCheck(SceneObject* player, SceneObject* object)
	{
		CircleCollider* pl = dynamic_cast<CircleCollider*>(player->collider);
		CircleCollider* other = dynamic_cast<CircleCollider*>(object->collider);
		if (pl == nullptr || other == nullptr)
		{
			return false;
		}
		vec2* positionPlayer = player->GlobalPosition();
		vec2* positionOther = object->GlobalPosition();
		double dist = (new vec2(positionPlayer->x - positionOther->x, positionPlayer->y - positionOther->y))->length();

		// Check if the distance is less than the sum of the radii
		int r1 = pl->GetRadius();
		int r2 = other->GetRadius();
		if (dist <= static_cast<double>(r1 + r2)) {
			printf("%p %p", positionOther, positionPlayer);
			return true; // Collision detected
		}
		return false; // No collision detected
	}

	bool Physics::BoxCollisionCheck(SceneObject* player, SceneObject* object)
	{
		BoxCollider* box = dynamic_cast<BoxCollider*>(object->collider);
		CircleCollider* circle = dynamic_cast<CircleCollider*>(player->collider);
		if (box == nullptr || circle == nullptr)
		{
			return false;
		}
		vec2* position = object->GlobalPosition();
		vec2* extends = box->GetBounds();
		vec2* playerPos = player->GlobalPosition();
		float closestX = std::max(position->x - extends->x, std::min(playerPos->x, position->x + extends->x));
		float closestY = std::max(position->y - extends->y, std::min(playerPos->y, position->y + extends->y));

		// Calculate the distance between the closest point and the circle center
		float distanceX = closestX - playerPos->x;
		float distanceY = closestY - playerPos->y;
		float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

		// Check if the distance is less than the circle radius (collision occurred)
		if (distance < circle->GetRadius())
		{
			// Set the collision point coordinates
			// collisionX = closestX;
			// collisionY = closestY;
			return true;
		}

		return false;
	}

	bool Physics::PolygonCollisionCheck(SceneObject* player, SceneObject* object)
	{
		return false;
	}
}