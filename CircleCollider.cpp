#include "CircleCollider.h"
#include <SDL2-2.0.3/include/SDL_stdinc.h>
#include <stdlib.h>
#include "template.h"
#include "ColliderBase.h"

namespace Tmpl8 {
	CircleCollider::CircleCollider(int circleRadius) : ColliderBase()
	{
		radius = circleRadius;
		type = 0;
	}
	std::vector<vec2*> CircleCollider::GetColliderPoints(vec2* position)
	{
		return std::vector<vec2*>();
	}
}