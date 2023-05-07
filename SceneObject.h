#pragma once

namespace Tmpl8 {
	class vec2;
	class ColliderBase;

	class SceneObject
	{
	public:
		SceneObject();
		vec2* position;
		SceneObject* parent = nullptr;
		ColliderBase* collider;
		vec2* GlobalPosition();
		void SetParent(SceneObject* object);
		void SetPosition(int x, int y);
		void UpdatePosition(int deltaX, int deltaY);
	};
}

