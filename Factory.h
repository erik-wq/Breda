#pragma once

namespace Tmpl8 {
	class LevelObject;
	class Factory
	{
	public:
		LevelObject* LeftWall();
		LevelObject* RightWall();
		// static LevelObject* PlayerWall();
		LevelObject* HorizontalWall();
		LevelObject* VerticalWall();
		LevelObject* Baricate(int type);
	};
}

