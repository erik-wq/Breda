#pragma once
#include "ColliderBase.h"
#include <vector>

namespace Tmpl8 {
    class vec2;

    class PolygonCollider :
        public ColliderBase
    {
    public:
        PolygonCollider(std::vector<vec2*> ColliderPoints);
        std::vector<vec2*> GetColliderPoints(vec2* position) override;
    private:
        std::vector<vec2*> points;
    };
}
