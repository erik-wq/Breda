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

namespace Tmpl8 {
	LevelManager::LevelManager()
	{
		moving = false;
		fact = new Factory();
		LeftWall = fact->LeftWall();
		RightWall = fact->RightWall();

		player = new Player();

		root = new SceneObject();
		GenerateStart();
		GenerateNextPart();
	}
	void LevelManager::Update(Surface* screen)
	{
		player->Move();


		//root->UpdatePosition(0, 1);

		vec2* last = objects[objects.size() - 1]->GlobalPosition();
		if (last->y > 75)
		{
			GenerateNextPart();
		}
		delete(last);

		for (LevelObject* object : objects)
		{
			if (Physics::CheckCollision(player, object))
			{
    				printf("fd\n");
			}
			object->Render(screen);
		}
		RightWall->Render(screen);
		LeftWall->Render(screen);
		player->Render(screen);

		printf("objects %d\n", objects.size());
		
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
	void LevelManager::GenerateNextPart()
	{
		int max = ObjectPool();
		std::srand(std::time(nullptr));
		int randomInt = std::rand() % (max - 0 + 1);
		if (randomInt == 1)
		{
			GenerateVertical();
		}
		else if (randomInt == 2)
		{
			GenerateHorizontal();
		}
		else
		{
			GenerateBarier();
		}
	}
	void LevelManager::GenerateVertical()
	{
		std::srand(std::time(nullptr));
		int x = (std::rand() % (3 - 0 + 1));
		int y = objects[objects.size() - 1]->position->y;
		std::srand(std::time(nullptr));
		y -= minDistance + (std::rand() % (maxDistance - minDistance + 1));
		printf("%d\n", x);
		if (x < 3)
		{
			x = x < 1 ? 250 : 550;
			LevelObject* wall = fact->VerticalWall();
			wall->SetPosition(x, y);
			AddObject(wall);
		}
		else
		{
			LevelObject* first = fact->VerticalWall();
			first->SetPosition(250, y);
			AddObject(first);
			LevelObject* second = fact->VerticalWall();
			second->SetPosition(550, y);
			AddObject(second);
		}
	}
	void LevelManager::GenerateHorizontal()
	{
		LevelObject* wall = fact->HorizontalWall();
		wall->SetPosition(400, objects[objects.size() - 1]->position->y - 340);
		AddObject(wall);
	}
	void LevelManager::GenerateBarier()
	{
	}
	void LevelManager::AddObject(LevelObject* obj)
	{
		obj->SetParent(root);
		objects.push_back(obj);

	}
	void LevelManager::GenerateStart()
	{
		LeftWall->SetPosition(20, 450);
		RightWall->SetPosition(780, 450);

		player->SetPosition(400, 760);

		root->SetPosition(0, 0);
		player->SetParent(root);

		objects.push_back(fact->VerticalWall());
		objects.push_back(fact->VerticalWall());

		objects[0]->SetParent(root);
		objects[0]->SetPosition(550, 500);

		objects[1]->SetParent(root);
		objects[1]->SetPosition(250, 220);

		objects.push_back(fact->Baricate(3));
		objects[2]->SetParent(root);
		objects[2]->SetPosition(400 , 300);

		objects.push_back(fact->Baricate(4));
		objects[3]->SetParent(root);
		objects[3]->SetPosition(400, 300);
	}
	int LevelManager::ObjectPool()
	{
		if (root->position->y > horizontalWallDist)
		{
			return 2;
		}
		else if (root->position->y > BarierDist)
		{
			return 3;
		}
		return 0;
	}
}