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
		if (object->collider->type == 0) // circle
		{
			return CircleCollisionCheck(player, object);
		}
		else if (object->collider->type == 1) // box
		{
			return BoxCollisionCheck(player, object);
		}
		else if (object->collider->type == 2) // polygon
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
		// postions
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
		// casting colliders
		BoxCollider* box = dynamic_cast<BoxCollider*>(object->collider);
		CircleCollider* circle = dynamic_cast<CircleCollider*>(player->collider);
		if (box == nullptr || circle == nullptr)
		{
			return false;
		}
		// collider position
		vec2* position = object->GlobalPosition();
		// box collider extends
		vec2* extends = box->GetBounds();
		// player global position
		vec2* playerPos = player->GlobalPosition();
		// calculating closest point
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
		
		// collision points
		std::vector<vec2*> points = object->collider->GetColliderPoints(object->GlobalPosition());
		// player global postion
		vec2* playerpos = player->GlobalPosition();

		// Check for edge-circle intersection
		for (int i = 0; i < points.size(); i++)
		{
			// line points
			vec2 p1 = *points[i];
			vec2 p2 = *points[(i + 1) % points.size()];
			// calculate vector, length and direction
			vec2* lineVec = new vec2(p2.x - p1.x, p2.y - p1.y);
			double lineLength = lineVec->length();
			vec2* lineDir = new vec2(lineVec->x / lineLength,lineVec->y / lineLength);

			// vector from first player to first position
			vec2 circleVec = *player->GlobalPosition() - p1;
			// dot produst of vector from player to first position
			double dotProduct = circleVec.dot(*lineDir);

			// calculating closest point
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

			// distance of closest point
			double distance = (closestPoint - *player->GlobalPosition()).length();
			delete(lineVec);
			delete(lineDir);
			// radius check
			if (distance <= 20)
			{
				Player* pl = dynamic_cast<Player*>(player);
				if (pl != nullptr)
				{
					pl->Death();
				}
				return true;
			}
		}

		return false;
	}
}