#include "SceneObject.h"
#include "template.h"

namespace Tmpl8 {

	SceneObject::SceneObject()
	{
		position = new vec2(0, 0);
		collider = nullptr;
	}
	vec2* SceneObject::GlobalPosition()
	{
		vec2* global = new vec2(position->x,position->y);
		SceneObject* root = parent;
		while (root != nullptr)
		{
			global->x += root->position->x;
			global->y += root->position->y;
			root = root->parent;
		}
		return global;
	}
	void SceneObject::SetParent(SceneObject* object)
	{
		parent = object;
	}
	void SceneObject::SetPosition(float x, float y)
	{
		position->x = x;
		position->y = y;
	}
	void SceneObject::UpdatePosition(int deltaX, int deltaY)
	{
		position->x = position->x + deltaX;
		position->y = position->y + deltaY;
	}
}