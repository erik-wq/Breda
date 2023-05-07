#pragma once
#include "ColliderBase.h"

namespace Tmpl8 {
    class CircleCollider : public ColliderBase
    {
    public:
        CircleCollider(int circleRadius);
    private:
        int radius;
    };
}

