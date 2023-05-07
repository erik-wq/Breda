#include "game.h"
#include "surface.h"
#include "Player.h"
#include "template.h"
#include <iostream>
#include <iostream>

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		level = new SceneObject();
		level->SetPosition(100, 100);
		player = new Player();
		player->SetParent(level);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete(player);
		delete(level);
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	void Game::Tick(float deltaTime)
	{

		level->UpdatePosition(0, 1);
		// clear the graphics window
		screen->Clear(0);
		player->Move();
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