#pragma once
#include "SceneObject.h"

namespace Tmpl8 {
    class Sprite;
    class Surface;

    class LevelObject : public SceneObject
    {
    public:
        LevelObject();
        LevelObject(char* sprite, int num);
        void Render(Surface* screen);
        Sprite* getPicture() { return picture; }
    protected:
        Sprite* picture;
    };
}

