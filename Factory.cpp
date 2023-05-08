#include "Factory.h"
#include "LevelObject.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include "CircleCollider.h"
#include "template.h"

namespace Tmpl8 {
	LevelObject* Factory::LeftWall()
	{
		LevelObject* wall = new LevelObject("assets/LeftWall.png", 1);
		return wall;
	}
	LevelObject* Factory::RightWall()
	{
		LevelObject* wall = new LevelObject("assets/RightWall.png", 1);
		return wall;
	}
}