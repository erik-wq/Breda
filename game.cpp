#include "game.h"
#include "surface.h"
#include "Player.h"
#include "template.h"
#include <iostream>
#include <iostream>
#include "CircleCollider.h"
#include "Physics.h"
#include "BoxCollider.h"

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player();
		level = new SceneObject();
		level->SetPosition(250, 250);
		level->collider = new BoxCollider(160, 40);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete(player);
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		Sprite sp = Sprite(new Surface("assets/Horizontal.png"), 1);

		vec2* t = level->GlobalPosition();
		sp.Draw(screen, t->x - sp.GetWidth() / 2, t->y - sp.GetHeight() / 2);

		player->Move();
		if (Physics::CheckCollision(player, level))
		{
			printf("collision detected\n");
		}
		player->Render(screen);
	}

	void Game::MousePositionUpdate(int x, int y)
	{
		CursorX = x;
		CursorY = y;
	}

	// space 44
	void Game::KeyUp(int key)
	{
		if (key == 44)
		{
			player->UpdateDirection(new vec2((float)CursorX, (float)CursorY));
			player->StartMove();
		}
	}

	void Game::KeyDown(int key)
	{
		if (key == 44)
		{  
			player->Stop();
		}
	}
};