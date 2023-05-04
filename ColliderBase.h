#pragma once

namespace Tmpl8 {
	class Vector2;

	class ColliderBase
	{
	public:
		ColliderBase();
		~ColliderBase();
		// points of collider in local space
		Vector2** colliderPoints = nullptr;
		// number of points
		int count;
	};
}
