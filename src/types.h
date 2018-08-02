#ifndef MY_TYPES
#define MY_TYPES

// The concrete types that will have instances
typedef enum
{
    MyRectangle = 1 << 0,
    MyCircle = 1 << 1,
} my_type_t;

// All possible types that share fields (simulate inheritance)
typedef enum
{
    MyShapeMask = MyRectangle | MyCircle,
    MyRectangleMask = MyRectangle,
    MyCircleMask = MyCircle,
} my_mask_t;

// container that's allocated on the VM and managed by the GC
// We use a pointer for the actual object simulating an existing library that
// doesn't let us own the memory.
typedef struct
{
    my_type_t type;
    void *ptr;
} my_container_t;

#endif