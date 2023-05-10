#pragma once

namespace Tmpl8 {
	class LevelObject;

	// creates default objects for level with default parameters
	class Factory
	{
	public:
		LevelObject* LeftWall();
		LevelObject* RightWall();
		LevelObject* HorizontalWall();
		LevelObject* VerticalWall();
		LevelObject* Baricate(int type);
		LevelObject* Bonus();
	};
}

