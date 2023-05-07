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
		if (object->collider->type == 0)
		{
			return CircleCollisionCheck(player, object);
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
		return false;
	}

	bool Physics::PolygonCollisionCheck(SceneObject* player, SceneObject* object)
	{
		return false;
	}
}