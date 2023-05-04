#include "CircleCollider.h"
#include <SDL2-2.0.3/include/SDL_stdinc.h>
#include "Vector2.h"
#include <stdlib.h>

namespace Tmpl8 {
	CircleCollider::CircleCollider(int pointsNum, float radius) : ColliderBase()
	{
		Vector2* direction = new Vector2(0,1);
		Vector2** points = (Vector2**)malloc(pointsNum * sizeof(Vector2));
		for (int i = 0; i < pointsNum; i++)
		{
			direction->rotate(i * (M_PI / pointsNum));
			points[i] = new Vector2(direction->x * radius, direction->y * radius);
		}
		count = pointsNum;
		colliderPoints = points;
		delete(direction);
	}
}