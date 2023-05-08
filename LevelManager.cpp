#include "LevelManager.h"
#include "Factory.h"
#include "LevelObject.h"
#include "Player.h"

namespace Tmpl8 {
	LevelManager::LevelManager()
	{
		fact = new Factory();
		LeftWall = fact->LeftWall();
		LeftWall->SetPosition(20, 450);
		RightWall = fact->RightWall();
		RightWall->SetPosition(780, 450);

		player = new Player();
		player->SetPosition(400, 760);
		
	}
	void LevelManager::Update(Surface* screen)
	{
		for (LevelObject* object : objects)
		{
			object->Render(screen);
		}
		RightWall->Render(screen);
		LeftWall->Render(screen);
		player->Render(screen);
	}
}