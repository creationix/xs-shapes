#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "shapes.h"
#include "types.h"

void my_shape_destructor(void *data)
{
    printf("%p: my_shape_destructor\n", data);
    if (!data)
    {
        return;
    }
    my_container_t *c = data;
    free(c->ptr);
    c->ptr = NULL;
}

void my_shape_position(xsMachine *the)
{
    my_container_t *c = xsGetHostChunk(xsThis);
    printf("%p: my_shape_position\n", c);
    assert(c->type & MyShapeMask);
    my_shape_t *shape = c->ptr;
    printf("Shape position x=%d y=%d\n", shape->x, shape->y);
}

void my_rectangle_constructor(xsMachine *the)
{
    my_rectangle_t *s = malloc(sizeof(*s));
    s->x = xsToInteger(xsArg(0));
    s->y = xsToInteger(xsArg(1));
    s->w = xsToInteger(xsArg(2));
    s->h = xsToInteger(xsArg(3));
    my_container_t c = {MyRectangle, s};
    xsSetHostChunk(xsThis, &c, sizeof(c));
    printf("%p: my_rectangle_constructor\n", xsGetHostChunk(xsThis));
}

void my_rectangle_area(xsMachine *the)
{
    my_container_t *c = xsGetHostChunk(xsThis);
    printf("%p: my_rectangle_area\n", c);
    assert(c->type & MyRectangleMask);
    my_rectangle_t *rectangle = c->ptr;
    int a = rectangle->x * rectangle->y;
    printf("Rectangle area w=%d * h=%d = a=%d\n", rectangle->x, rectangle->y, a);
}

void my_circle_constructor(xsMachine *the)
{
    my_circle_t *s = malloc(sizeof(*s));
    s->x = xsToInteger(xsArg(0));
    s->y = xsToInteger(xsArg(1));
    s->r = xsToInteger(xsArg(2));
    my_container_t c = {MyCircle, s};
    xsSetHostChunk(xsThis, &c, sizeof(c));
    printf("%p: my_circle_constructor\n", xsGetHostChunk(xsThis));
}

void my_circle_area(xsMachine *the)
{
    my_container_t *c = xsGetHostChunk(xsThis);
    printf("%p: my_circle_area\n", c);
    assert(c->type & MyCircleMask);
    my_circle_t *circle = c->ptr;
    int a = 3141 * circle->r * circle->r / 1000;
    printf("Circle area PI * r=%d ^ 2 = a=%d\n", circle->r, a);
}
