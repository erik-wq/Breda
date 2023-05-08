#pragma once
#include <vector>

namespace Tmpl8 {
	class LevelObject;
	class Factory;
	class Surface;
	class Player;

	class LevelManager
	{
	public:
		LevelManager();
		void Update(Surface* screen);
		//void Reset();
		//void Finish();
	private:
		Factory* fact;
		std::vector<LevelObject*> objects;
		//SceneObject* player;
		int widht = 800;
		int height = 900;
		
		Player* player;
		LevelObject* LeftWall;
		LevelObject* RightWall;
	};
}

