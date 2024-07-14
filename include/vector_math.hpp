#ifndef VECTOR
#define VECTOR

struct point_t{
    float x;
    float y;
};

typedef struct point_t *point;

struct vector_t{
    point base;
    point head;
};

typedef struct vector_t *vec;

point P(float x, float y);

vec V(point base, point head);

void update(point P, float x, float y);

point add(point a, point b);

point sub(point a, point b);
point mul(point a, point b);
point unit(point a, point b);
point scale(point a, float b);
float dist(point a, point b);
char *to_string(vec v);

char *to_string(point v);
vec unit(vec v);

#endif