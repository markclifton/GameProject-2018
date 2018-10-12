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

struct color
{
    color(){}
    color(float r, float g, float b)
        : r(r), g(g), b(b)
    {}
    float r{1};
    float g{1};
    float b{1};
};

struct vertex
{
    vertex(){}
    vertex(color c, position pos)
        : c(c), pos(pos)
    {}
    color c;
    position pos;
};
