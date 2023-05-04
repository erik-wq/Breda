#pragma once

namespace Tmpl8 {

class Surface;
class Sprite;
class Player;

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	// emgine loops
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	// input handling
	void MouseUp(int button) {}
	void MouseDown(int button) {}
	void MouseMove(int x, int y) {} // delta of cursor movement
	void MousePositionUpdate(int x, int y); // updating current position on game screen
	void KeyUp(int key);
	void KeyDown(int key);
private:
	Surface* screen;

	// Cursor coordinates on game screen
	int CursorX;
	int CursorY;

	// player refenrence
	Player* player;

};

}; // namespace Tmpl8