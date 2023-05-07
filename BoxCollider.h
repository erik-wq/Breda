#pragma once
#include "ColliderBase.h"

namespace Tmpl8 {
	class BoxCollider :
		public ColliderBase
	{
	public:
		BoxCollider(int widht, int height);
		~BoxCollider();
		std::vector<vec2*> GetColliderPoints(vec2* position) override;
	private:
		vec2* extends;
	};
}
