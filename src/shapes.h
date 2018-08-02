#ifndef MY_SHAPES
#define MY_SHAPES

#include "xs.h"

typedef struct Shape
{
    int x;
    int y;
} my_shape_t;

typedef struct Rectangle
{
    int x;
    int y;
    int w;
    int h;
} my_rectangle_t;

typedef struct Circle
{
    int x;
    int y;
    int r;
} my_circle_t;

// Union to force common layout for inheritance
union Shapes {
    my_shape_t shape;
    my_rectangle_t rect;
    my_circle_t circ;
};

void my_shape_destructor(void *c);
void my_shape_get_x(xsMachine *the);
void my_shape_get_y(xsMachine *the);
void my_circle_constructor(xsMachine *the);
void my_circle_get_r(xsMachine *the);
void my_circle_get_area(xsMachine *the);
void my_rectangle_constructor(xsMachine *the);
void my_rectangle_get_w(xsMachine *the);
void my_rectangle_get_h(xsMachine *the);
void my_rectangle_get_area(xsMachine *the);

#endif