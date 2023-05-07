#pragma once

namespace Tmpl8
{
	class SceneObject;
	class vec2;

	class Physics
	{
	public:
		static bool CheckCollision(SceneObject* player, SceneObject* object);
	private:
		// collision between diferent types
		// circles are extra points or death
		static bool CircleCollisionCheck(SceneObject* player, SceneObject* object);
		// needs point of impact to bounce player
		static bool BoxCollisionCheck(SceneObject* player, SceneObject* object);
		// polygons are damage bariesrs so death
		static bool PolygonCollisionCheck(SceneObject* player, SceneObject* object);
	};
}
