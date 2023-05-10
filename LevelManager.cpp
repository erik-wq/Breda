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
#include <ctime>

namespace Tmpl8 {
	LevelManager::LevelManager()
	{
		// setting default params
		moving = false;
		wasbarier = false;

		runing = false;
		maxBonuses = 10;

		// creating factory 
		fact = new Factory();

		// creating side colliders
		LeftWall = new SceneObject();
		LeftWall->collider = new BoxCollider(2, 900);
		LeftWall->SetPosition(1, 450);

		RightWall = new SceneObject();
		RightWall->collider = new BoxCollider(2, 900);
		RightWall->SetPosition(799, 450);

		BottomWall = new SceneObject();
		BottomWall->collider = new BoxCollider(900, 2);
		BottomWall->SetPosition(400, 899);

		TopWall = new SceneObject();
		TopWall->collider = new BoxCollider(900, 2);
		TopWall->SetPosition(400, 1);

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

		if (runing)
		{
			CheckTimer();
		}

		if (bonuses.size() < maxBonuses)
		{
			if (!runing)
			{
				toWait = time(nullptr) + RandomInt(1, 4);
				runing = true;
			}
		}

		// posible off screnn
		vec2* playerpos = player->GlobalPosition();
		if (playerpos->y > 920 || playerpos->y < -20)
		{
			Reset();
			delete(playerpos);
			return;
		}
		delete(playerpos);

		// moving player
		player->Move();

		// moving level
		if (moving)
		{
			// player->UpdatePosition(0, -1);
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
		Physics::CheckCollision(player, BottomWall);
		Physics::CheckCollision(player, TopWall);

		for (LevelObject* bonus : bonuses)
		{
			bonus->Render(screen);
		}

		// objects collision check and rendering
		for (LevelObject* object : objects)
		{
			Physics::CheckCollision(player, object);
			object->Render(screen);
		}
		player->Render(screen);

		// deleting objects that are not needed
		for (int i = 0; i < objects.size(); i++)
		{
			if (root->position->y + objects[i]->position->y > 1000)
			{
				delete(objects[i]);
				objects.erase(objects.begin() + i);
			}
		}

		for (int i = 0; i < bonuses.size(); i++)
		{
			if (Physics::CheckCollision(player, bonuses[i]))
			{
				delete(bonuses[i]);
				bonuses.erase(bonuses.begin() + i);
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

		for (int i = 0; i < bonuses.size(); i++)
		{
			delete(bonuses[i]);
		}
		bonuses.clear();

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

	LevelObject* LevelManager::SpawnBonus()
	{
		LevelObject* bonus = fact->Bonus();
		int x = RandomInt(50, 750);
		int y = RandomInt(50, 850);
		bonus->SetPosition(x, y);
		return bonus;
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
		int x = RandomInt(0, 1);
		// distance from previous wall
		int y;
		// one wall
		if (x == 0)
		{
			int x = RandomInt(100, 600);
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
		int x = RandomInt(100, 600);
		wall->SetPosition(x, DistanceY(wall));
		AddObject(wall);
	}
	// generate barier
	void LevelManager::GenerateBarier()
	{
		wasbarier = true;
		int bariertype = RandomInt(1, 4);
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
		// player->SetParent(root);

		objects.push_back(fact->HorizontalWall());
		objects.push_back(fact->VerticalWall());
		objects.push_back(fact->VerticalWall());

		objects[0]->SetParent(root);
		objects[0]->SetPosition(400, 805);

		objects[1]->SetParent(root);
		objects[1]->SetPosition(550, 500);

		objects[2]->SetParent(root);
		objects[2]->SetPosition(250, 220);

		for (int i = 0; i < maxBonuses; i++)
		{
			bonuses.push_back(SpawnBonus());
		}
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
	void LevelManager::CheckTimer()
	{
		if (toWait <= time(nullptr))
		{
			bonuses.push_back(SpawnBonus());
			runing = false;
		}
	}
}