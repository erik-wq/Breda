#include "LevelObject.h"
#include "template.h"
#include "surface.h"

namespace Tmpl8 {
	LevelObject::LevelObject()
	{
		picture = nullptr;
	}
	LevelObject::LevelObject(char* sprite, int num) : SceneObject()
	{
		picture = new Sprite(new Surface(sprite), num);
	}
	LevelObject::~LevelObject()
	{
		delete(picture);
	}
	void LevelObject::Render(Surface* screen)
	{
		vec2* position = GlobalPosition();
		picture->Draw(screen, position->x - picture->GetWidth() / 2, position->y - picture->GetHeight() / 2);
		delete(position);
	}
}
