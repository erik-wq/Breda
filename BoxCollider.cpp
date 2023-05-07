#include "BoxCollider.h"
#include "template.h"

namespace Tmpl8 {
	BoxCollider::BoxCollider(int widht, int height)
	{
		extends = new vec2(widht / 2, height / 2);
	}
	BoxCollider::~BoxCollider()
	{
		delete(extends);
	}
	std::vector<vec2*> BoxCollider::GetColliderPoints(vec2* position)
	{
		std::vector<vec2*> points;
		points.push_back(new vec2(position->x + extends->x, position->y + extends->y));
		points.push_back(new vec2(position->x + extends->x, position->y - extends->y));
		points.push_back(new vec2(position->x - extends->x, position->y + extends->y));
		points.push_back(new vec2(position->x - extends->x, position->y - extends->y));
		return points;
	}
}