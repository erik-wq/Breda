#pragma once
#include "ColliderBase.h"

namespace Tmpl8 {
    class CircleCollider : public ColliderBase
    {
    public:
        CircleCollider(int pointsNum, float radius); // count of point in polligon shape for circle
    };
}

