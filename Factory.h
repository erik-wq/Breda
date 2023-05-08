#pragma once

namespace Tmpl8 {
	class LevelObject;
	class Factory
	{
	public:
		LevelObject* LeftWall();
		LevelObject* RightWall();
		// static LevelObject* PlayerWall();
		// static LevelObject* HorizontalWall();
		// static LevelObject* VerticalWall();
	};
}

