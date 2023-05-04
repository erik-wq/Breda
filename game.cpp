#include "game.h"
#include "surface.h"
#include "Player.h"
#include "Vector2.h"
#include <iostream>

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player();
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
		player->Move(new Vector2(CursorX, CursorY));
		player->Update(screen);
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
			player->Stop();
		}
	}

	void Game::KeyDown(int key)
	{
		if (key == 44)
		{
			player->StartMove();
		}
	}

};