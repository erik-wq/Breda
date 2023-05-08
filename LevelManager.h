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
		void Reset();
		//void Finish();
		void StartMoving();
		Player* player;
	private:
		bool moving;
		
		// level generation factory
		Factory* fact;

		// level objects
		std::vector<LevelObject*> objects;

		// screen size
		int widht = 800;
		int height = 900;
		
		// side colliders
		SceneObject* LeftWall;
		SceneObject* RightWall;
		SceneObject* BottomWall;
		SceneObject* TopWall;

		// root for all level objects
		SceneObject* root;

		// for 2 vertical walls
		int leftSide = 250;
		int rightSide = 550;

		// generation methods
		void GenerateNextPart();
		void GenerateVertical();
		void GenerateHorizontal();
		void GenerateBarier();
		void AddObject(LevelObject* obj);
		void GenerateStart();

		// check for posible objects
		int ObjectPool();

		// support methods
		int RandomInt(int min, int max);
		int DistanceY(LevelObject* nextObject);

		// distances
		const int horizontalWallDist = 1000;
		const int BarierDist = 2500;
		const int finish = 5000;

		const int maxDistance = 300;
		const int minDistance = 60;

		// to ensure 2 bariers dont spawn after each other
		bool wasbarier;
	};
}

