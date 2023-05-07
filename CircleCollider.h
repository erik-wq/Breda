#pragma once
#include "ColliderBase.h"

namespace Tmpl8 {
    class CircleCollider : public ColliderBase
    {
    public:
        CircleCollider(int circleRadius);
        int GetRadius() { return radius; }
        std::vector<vec2*> GetColliderPoints(vec2* position) override;
    private:
        int radius;
    };
}

