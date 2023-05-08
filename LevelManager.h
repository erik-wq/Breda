#pragma once
#include <vector>

namespace Tmpl8 {
	class LevelObject;
	class Factory;
	class Surface;
	class Player;
	class SceneObject;

	class LevelManager
	{
	public:
		LevelManager();
		void Update(Surface* screen);
		//void Reset();
		//void Finish();
		Player* player;
	private:
		bool moving;
		
		Factory* fact;
		std::vector<LevelObject*> objects;
		//SceneObject* player;
		int widht = 800;
		int height = 900;
		
		LevelObject* LeftWall;
		LevelObject* RightWall;

		SceneObject* root;

		int leftSide = 250;
		int rightSide = 550;

		void GenerateNextPart();
		void GenerateVertical();
		void GenerateHorizontal();
		void GenerateBarier();
		void AddObject(LevelObject* obj);

		void GenerateStart();

		int ObjectPool();

		// distances
		const int horizontalWallDist = 500;
		const int BarierDist = 100;
		const int finish = 1600;

		const int maxDistance = 550;
		const int minDistance = 260;
	};
}

