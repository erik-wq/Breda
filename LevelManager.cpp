#include "LevelManager.h"
#include "Factory.h"
#include "LevelObject.h"
#include "Player.h"
#include "Physics.h"
#include "template.h"
#include <random>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include "surface.h"
#include "BoxCollider.h"

namespace Tmpl8 {
	LevelManager::LevelManager()
	{
		// setting default params
		moving = false;
		wasbarier = false;

		// creating factory 
		fact = new Factory();
		
		// creating side colliders
		LeftWall = new SceneObject();
		LeftWall->collider = new BoxCollider(2, 900);
		LeftWall->SetPosition(1, 450);
		RightWall = new SceneObject();
		RightWall->collider = new BoxCollider(2, 900);
		RightWall->SetPosition(799, 450);

		// initializing random
		std::srand(std::time(nullptr));

		// creating player
		player = new Player();

		// creating root of level
		root = new SceneObject();

		// generating level
		GenerateStart();
		GenerateNextPart();
		
	}

	// update of game
	void LevelManager::Update(Surface* screen)
	{
		if (!player->live())
		{
			Reset();
			return;
		}

		// moving player
		player->Move();

		// moving level
		if (moving)
		{
			root->UpdatePosition(0, 1);
		}

		// check for generation of next part
		vec2* last = objects[objects.size() - 1]->GlobalPosition();
		if (last->y > 75)
		{
			GenerateNextPart();
		}
		delete(last);

		// side colision check
		Physics::CheckCollision(player, RightWall);
		Physics::CheckCollision(player, LeftWall);

		// objects collision check and rendering
		for (LevelObject* object : objects)
		{
			Physics::CheckCollision(player, object);
			object->Render(screen);
		}
		player->Render(screen);

		// deleting objects that are not needed
		if (root->position->y + objects[0]->position->y > 1000)
		{
			delete(objects[0]);
			objects.erase(objects.begin());
		}
		if (objects.size() > 2)
		{
			if (root->position->y + objects[1]->position->y > 1000)
			{
				delete(objects[1]);
				objects.erase(objects.begin() + 1);
			}
		}
	}

	void LevelManager::Reset()
	{
		moving = false;
		// deleting all objects
		for (int i = 0; i < objects.size(); i++)
		{
			delete(objects[i]);
		}
		objects.clear();

		// regenerating level and revinving player
		player->Stop();
		GenerateStart();
		player->Revive();
		GenerateNextPart();
	}

	void LevelManager::StartMoving()
	{
		if (!moving)
		{
			moving = true;
		}
	}

	// generating next part
	void LevelManager::GenerateNextPart()
	{
		// random to choose next part
		int max = ObjectPool();
		int randomInt = RandomInt(0, max);

		// bariers dont repeat
		if (wasbarier)
		{
			wasbarier = false;
			randomInt = randomInt == 2 ? 0 : randomInt;
		}
		// vertical wall
		if (randomInt == 0)
		{
			GenerateVertical();
		}
		// horizontall wall
		else if (randomInt == 1)
		{
			GenerateHorizontal();
		}
		// barier
		else
		{
			GenerateBarier();
		}
	}
	// generate vertical wall
	void LevelManager::GenerateVertical()
	{
		// choose type
		int x = RandomInt(0,1);
		// distance from previous wall
		int y;
		// one wall
		if (x == 0)
		{
			int x = RandomInt(100,600);
			LevelObject* wall = fact->VerticalWall();
			y = DistanceY(wall);
			wall->SetPosition(x, y);
			AddObject(wall);
		}
		// 2 wals
		else
		{
			LevelObject* first = fact->VerticalWall();
			y = DistanceY(first);
			first->SetPosition(250, y);
			AddObject(first);
			LevelObject* second = fact->VerticalWall();
			second->SetPosition(550, y);
			AddObject(second);
		}
	}
	// generate horizontal wall
	void LevelManager::GenerateHorizontal()
	{
		LevelObject* wall = fact->HorizontalWall();
		int x = RandomInt(100,600);
		wall->SetPosition(x, DistanceY(wall));
		AddObject(wall);
	}
	// generate barier
	void LevelManager::GenerateBarier()
	{
		wasbarier = true;
		int bariertype = RandomInt(1,4);
		LevelObject* barier = fact->Baricate(bariertype);
		int y = DistanceY(barier);
		barier->SetPosition(400, y);
		AddObject(barier);
	}
	// add object to rendering vector and parent object to root
	void LevelManager::AddObject(LevelObject* obj)
	{
		obj->SetParent(root);
		objects.push_back(obj);

	}
	// generate start of level
	void LevelManager::GenerateStart()
	{
		player->SetPosition(400, 760);

		root->SetPosition(0, 0);
		player->SetParent(root);

		objects.push_back(fact->HorizontalWall());
		objects.push_back(fact->VerticalWall());
		objects.push_back(fact->VerticalWall());

		objects[0]->SetParent(root);
		objects[0]->SetPosition(400, 805);

		objects[1]->SetParent(root);
		objects[1]->SetPosition(550, 500);

		objects[2]->SetParent(root);
		objects[2]->SetPosition(250, 220);
	}
	// check for possible object
	int LevelManager::ObjectPool()
	{
		// all
		if (root->position->y > BarierDist)
		{
			return 2;
		}
		// horizontal and vertical
		else if (root->position->y > horizontalWallDist)
		{
			return 1;
		}
		// vertical
		return 0;
	}
	// random from range
	int LevelManager::RandomInt(int min, int max)
	{
		int random = min + (std::rand() % (max - min + 1));
		return random;
	}
	// distance from last generated wall
	int LevelManager::DistanceY(LevelObject* nextObject)
	{
		int y = objects[objects.size() - 1]->position->y - RandomInt(minDistance, maxDistance);
		y -= objects[objects.size() - 1]->getPicture()->GetHeight() / 2;
		y -= nextObject->getPicture()->GetHeight() / 2;
		return y;
	}
}