#include "CircleCollider.h"
#include <SDL2-2.0.3/include/SDL_stdinc.h>
#include <stdlib.h>
#include "template.h"

namespace Tmpl8 {
	CircleCollider::CircleCollider(int pointsNum, float radius) : ColliderBase()
	{
		vec2* direction = new vec2(0,1);
		vec2** points = (vec2**)malloc(pointsNum * sizeof(vec2));
		for (int i = 0; i < pointsNum; i++)
		{
			vec2::rotateVect2(direction,i * (M_PI / pointsNum));
			points[i] = new vec2(direction->x * radius, direction->y * radius);
		}
		count = pointsNum;
		colliderPoints = points;
		delete(direction);
	}
}