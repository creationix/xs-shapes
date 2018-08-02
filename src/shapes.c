#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "xsmc.h"
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

void my_shape_get_x(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_shape_get_x\n", c);
    assert(c->type & MyShapeMask);
    my_shape_t *shape = c->ptr;
    xsmcSetInteger(xsResult, shape->x);
}

void my_shape_get_y(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_shape_get_y\n", c);
    assert(c->type & MyShapeMask);
    my_shape_t *shape = c->ptr;
    xsmcSetInteger(xsResult, shape->y);
}

void my_rectangle_constructor(xsMachine *the)
{
    my_rectangle_t *s = malloc(sizeof(*s));
    s->x = xsmcToInteger(xsArg(0));
    s->y = xsmcToInteger(xsArg(1));
    s->w = xsmcToInteger(xsArg(2));
    s->h = xsmcToInteger(xsArg(3));
    my_container_t c = {MyRectangle, s};
    xsmcSetHostChunk(xsThis, &c, sizeof(c));
    printf("%p: my_rectangle_constructor\n", xsmcGetHostChunk(xsThis));
}

void my_rectangle_get_w(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_rectangle_area\n", c);
    assert(c->type & MyRectangleMask);
    my_rectangle_t *rectangle = c->ptr;
    xsmcSetInteger(xsResult, rectangle->w);
}

void my_rectangle_get_h(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_rectangle_area\n", c);
    assert(c->type & MyRectangleMask);
    my_rectangle_t *rectangle = c->ptr;
    xsmcSetInteger(xsResult, rectangle->h);
}

void my_rectangle_get_area(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_rectangle_area\n", c);
    assert(c->type & MyRectangleMask);
    my_rectangle_t *rectangle = c->ptr;
    xsmcSetInteger(xsResult, rectangle->x * rectangle->y);
}

void my_circle_constructor(xsMachine *the)
{
    my_circle_t *s = malloc(sizeof(*s));
    s->x = xsmcToInteger(xsArg(0));
    s->y = xsmcToInteger(xsArg(1));
    s->r = xsmcToInteger(xsArg(2));
    my_container_t c = {MyCircle, s};
    xsmcSetHostChunk(xsThis, &c, sizeof(c));
    printf("%p: my_circle_constructor\n", xsmcGetHostChunk(xsThis));
}

void my_circle_get_r(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_circle_area\n", c);
    assert(c->type & MyCircleMask);
    my_circle_t *circle = c->ptr;
    xsmcSetInteger(xsResult, circle->r);
}

void my_circle_get_area(xsMachine *the)
{
    my_container_t *c = xsmcGetHostChunk(xsThis);
    printf("%p: my_circle_area\n", c);
    assert(c->type & MyCircleMask);
    my_circle_t *circle = c->ptr;
    xsmcSetInteger(xsResult, 3141 * circle->r * circle->r / 1000);
}
