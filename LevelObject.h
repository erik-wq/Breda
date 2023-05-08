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
        ~LevelObject();
        void Render(Surface* screen);
    protected:
        Sprite* picture;
    };
}

