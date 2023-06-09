#pragma once
#include <vector>

namespace Tmpl8 {
	class vec2;

	class ColliderBase
	{
	public:
		// calculates points of collider relative to position
		virtual std::vector<vec2*> GetColliderPoints(vec2* position) = 0;
		int type; // 0 circle, 1 box , 2 polygon
	};
}
