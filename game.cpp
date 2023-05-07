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

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player();
		player->SetPosition(300,50);
		level = new SceneObject();
		level->SetPosition(400, 400);
		sp = new Sprite(new Surface("assets/barier.png"), 1);
		std::vector<vec2*> points;
		points.push_back(new vec2(-150, -120));
		points.push_back(new vec2(50,-120));
		points.push_back(new vec2(150, 120));
		points.push_back(new vec2(-150,120));
		level->collider = new PolygonCollider(points);
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

		vec2* t = level->GlobalPosition();
		sp->Draw(screen, t->x - sp->GetWidth() / 2, t->y - sp->GetHeight() / 2);

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