#include "Factory.h"
#include "LevelObject.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include "CircleCollider.h"
#include "template.h"
#include <ctime>
#include "LevelManager.h"

namespace Tmpl8 {
	LevelObject* Factory::LeftWall()
	{
		LevelObject* wall = new LevelObject("assets/LeftWall.png", 1);
		return wall;
	}
	LevelObject* Factory::RightWall()
	{
		LevelObject* wall = new LevelObject("assets/RightWall.png", 1);
		return wall;
	}
	LevelObject* Factory::HorizontalWall()
	{
		LevelObject* platf = new LevelObject("assets/Horizontal.png", 1);
		platf->collider = new BoxCollider(170, 40);
		return platf;
	}
	LevelObject* Factory::VerticalWall()
	{
		LevelObject* platf = new LevelObject("assets/Vertical.png", 1);
		platf->collider = new BoxCollider(40, 170);
		return platf;
	}

	LevelObject* Factory::Baricate(int type)
	{
		LevelObject* platf = nullptr;
		std::vector<vec2*> points;
		switch (type)
		{
		case 1:
			platf = new LevelObject("assets/Barier1.png", 1);
			points.push_back(new vec2(-400, -70));
			points.push_back(new vec2(0, -70));
			points.push_back(new vec2(205, 70));
			points.push_back(new vec2(-400, 70));
			break;
		case 2:
			platf = new LevelObject("assets/Barier2.png", 1);
			points.push_back(new vec2(195, -70));
			points.push_back(new vec2(400, -70));
			points.push_back(new vec2(400 , 70));
			points.push_back(new vec2(401, 70));
			break;
		case 3:
			platf = new LevelObject("assets/Barier3.png", 1);
			points.push_back(new vec2(-400, -120));
			points.push_back(new vec2(10, -120));
			points.push_back(new vec2(-100, 120));
			points.push_back(new vec2(-400, 120));
			break;
		case 4:
			platf = new LevelObject("assets/Barier4.png", 1);
			points.push_back(new vec2(125, -120));
			points.push_back(new vec2(400, -120));
			points.push_back(new vec2(400, 120));
			points.push_back(new vec2(13, 120));
			break;
		}
		if (platf != nullptr)
		{
			platf->collider = new PolygonCollider(points);
		}
		return platf;
	}

}