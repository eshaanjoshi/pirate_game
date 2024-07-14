#include <cmath>
#include "../include/vector_math.hpp"
#include <stdio.h>

point P(float x, float y)
{
    point p = new point_t{};
    p->x = x;
    p->y = y;
    return p;
}

vec V(point base, point head)
{
    vec v = new vector_t{};
    v->base = base;
    v->head = head;
    return v;
}

void update(point V, float x, float y)
{
    V->x = x;
    V->y = y;
}

point add(point a, point b)
{
    return P(a->x + b->x, a->y+b->y);
}

point sub(point a, point b)
{
    return P(a->x - b->x, a->y - b->y);
}

point mul(point a, point b)
{
    return P(a->x * b->x, a->y * b->y);
}

float dist(point a, point b)
{
    point d = sub(a, b);
    return sqrt((pow(d->x, 2) + pow(d->y, 2)));
}

vec scale(vec a, float b)
{
    return V(P(a->head->x * b, a->head->y * b), a->base);
}

char *to_string(vec v)
{
    char *buffer = (char*)malloc(sizeof(char) * 50);
    sprintf(buffer, "BASE X: %f Y: %f -> X: %f Y: %f HEAD \n", v->base->x, v->base->y, v->head->x, v->head->y);
    return buffer;
}

char *to_string(point v)
{
    char *buffer = (char*)malloc(sizeof(char) * 30);
    sprintf(buffer, "X: %f Y: %f\n", v->x, v->y);
    return buffer;
}

vec unit(vec v)
{
    float d = dist(v->base, v->head);
    
    return scale(v, 1/d);
}