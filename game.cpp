#include "game.h"
#include "surface.h"
#include "Player.h"
#include "template.h"
#include <iostream>
#include <iostream>
#include "CircleCollider.h"
#include "Physics.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include <vector>
#include "LevelManager.h"

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		level = new LevelManager();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete(level);
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);

		level->Update(screen);
	}

	// cursor position
	void Game::MousePositionUpdate(int x, int y)
	{
		CursorX = x;
		CursorY = y;
	}

	void Game::KeyUp(int key)
	{
		if (key == 44)
		{
			level->player->UpdateDirection(new vec2((float)CursorX, (float)CursorY));
			level->player->StartMove();
			level->StartMoving();
		}
	}

	void Game::KeyDown(int key)
	{
		if (key == 44)
		{  
			level->player->Slow();
		}
	}
};