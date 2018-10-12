#pragma once

struct position
{
    position(){}
    position(float x, float y, float z = -1)
        : x(x), y(y), z(z)
    {}
    float x{0};
    float y{0};
    float z{-1};
};
