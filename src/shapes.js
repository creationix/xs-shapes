
class Shape @ "my_shape_destructor" {
    constructor(...args) {
        this.construct(...args)
    }
    get x() @ "my_shape_get_x"
    get y() @ "my_shape_get_y"
}

export class Circle extends Shape {
    constructor(x, y, r) @ "my_circle_constructor"
    get r() @ "my_circle_get_r"
    get area() @ "my_circle_get_area"
}

export class Rectangle extends Shape {
    constructor(x, y, w, h) @ "my_rectangle_constructor"
    get w() @ "my_rectangle_get_w"
    get h() @ "my_rectangle_get_h"
    get area() @ "my_rectangle_get_area"
}
