#include "CircleCollider.h"
#include <SDL2-2.0.3/include/SDL_stdinc.h>
#include <stdlib.h>
#include "template.h"

namespace Tmpl8 {
	CircleCollider::CircleCollider(int circleRadius)
	{
		radius = circleRadius;
		type = circle;
	}
}