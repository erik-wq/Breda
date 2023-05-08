#include "Physics.h"
#include <cmath>
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include "SceneObject.h"
#include "template.h"
#include "Player.h"

namespace Tmpl8
{
	bool Physics::CheckCollision(SceneObject* player, SceneObject* object)
	{
		// checks for nullpointers
		if (player == nullptr || object == nullptr)
		{
			return false;
		}
		if (player->collider == nullptr || object->collider == nullptr)
		{
			return false;
		}
		// choosing best collision detection algorith
		if (object->collider->type == 0)
		{
			return CircleCollisionCheck(player, object);
		}
		else if (object->collider->type == 1)
		{
			return BoxCollisionCheck(player, object);
		}
		else if (object->collider->type == 2)
		{
			return PolygonCollisionCheck(player, object);
		}
		return false;
	}

	// circle circle colision
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
			return true; // Collision detected
		}
		return false; // No collision detected
	}

	// circle box colision
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
			vec2* pointOfCollision = new vec2(closestX, closestY);
			Player* pl = dynamic_cast<Player*>(player);
			pl->Bounce(pointOfCollision);
			delete(pointOfCollision);

 			return true;
		}

		return false;
	}

	// p[olygoon circle colision
	bool Physics::PolygonCollisionCheck(SceneObject* player, SceneObject* object)
	{
		CircleCollider* pCol = dynamic_cast<CircleCollider*>(player->collider);
		if (object->collider == nullptr || pCol == nullptr)
		{
			return false;
		}
		
		std::vector<vec2*> points = object->collider->GetColliderPoints(object->GlobalPosition());
		vec2* playerpos = player->GlobalPosition();

		// Check for edge-circle intersection
		for (int i = 0; i < points.size(); i++)
		{
			vec2 p1 = *points[i];
			vec2 p2 = *points[(i + 1) % points.size()];
			vec2* lineVec = new vec2(p2.x - p1.x, p2.y - p1.y);
			double lineLength = lineVec->length();
			vec2* lineDir = new vec2(lineVec->x / lineLength,
				lineVec->y / lineLength);

			vec2 circleVec = *player->GlobalPosition() - p1;
			double dotProduct = circleVec.dot(*lineDir);

			vec2 closestPoint;
			if (dotProduct < 0) {
				closestPoint = p1;
			}
			else if (dotProduct > lineLength) {
				closestPoint = p2;
			}
			else {
				closestPoint = p1 + *lineDir * dotProduct;
			}

			double distance = (closestPoint - *player->GlobalPosition()).length();
			delete(lineVec);
			delete(lineDir);
			if (distance <= 20)
			{
				return true;
			}
		}

		return false;
	}
}