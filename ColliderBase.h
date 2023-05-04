#pragma once

namespace Tmpl8 {
	class vec2;

	class ColliderBase
	{
	public:
		ColliderBase();
		~ColliderBase();
		// points of collider in local space
		vec2** colliderPoints = nullptr;
		// number of points
		int count;
	};
}
