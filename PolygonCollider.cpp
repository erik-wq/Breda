#include "PolygonCollider.h"
#include "template.h"

namespace Tmpl8 {
	PolygonCollider::PolygonCollider(std::vector<vec2*> ColliderPoints) : ColliderBase()
	{
		points = ColliderPoints;
		type = 2;
	}

	std::vector<vec2*> PolygonCollider::GetColliderPoints(vec2* position)
	{
		std::vector<vec2*> globalpoints;
		for (vec2* point : points)
		{
			globalpoints.push_back(new vec2(point->x + position->x, point->y + position->y));
		}
		return globalpoints;
	}
}