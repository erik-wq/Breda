#pragma once
#include <vector>

namespace Tmpl8 {
	class vec2;

	class ColliderBase
	{
	public:
		virtual std::vector<vec2*> GetColliderPoints(vec2* position) = 0;
		ColliderType type;
	};

	enum ColliderType
	{
		circle,
		box,
		polygon
	};
}
