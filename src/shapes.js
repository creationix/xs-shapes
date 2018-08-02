

export class Circle @ "my_shape_destructor" {
    constructor(x, y, r) @ "my_circle_constructor"
    position() @ "my_shape_position"
    area() @ "my_circle_area"
}

export class Rectangle @ "my_shape_destructor" {
    constructor(x, y, w, h) @ "my_rectangle_constructor"
    position() @ "my_shape_position"
    area() @ "my_rectangle_area"
}

// I want this, but it won't work because the subclass instances aren't host objects:

// class Shape @ "my_shape_destructor" {
//     position() @ "my_shape_position"
// }

// export class Circle extends Shape {
//     constructor(x, y, r) @ "my_circle_constructor"
//     area() @ "my_circle_area"
// }

// export class Rectangle extends Shape {
//     constructor(x, y, w, h) @ "my_rectangle_constructor"
//     area() @ "my_rectangle_area"
// }
