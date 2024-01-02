#include <iostream>
#include <string>
#include <vector>

// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

/*

The Liskov Substitution Principle: Ensuring Subtypes Adhere to Expectations
In the realm of object-oriented programming, the Liskov Substitution Principle (LSP)
stands as a cornerstone of sound design. It asserts that objects of a superclass should
be replaceable with objects of its subtypes without affecting the correctness of the program.
This principle, derived from the work of Barbara Liskov, advocates for maintaining consistency
and predictability in the behavior of derived classes.
To illustrate the essence of LSP, consider a scenario where we represent shapes using
a class hierarchy. The Rectangle class defines the attributes and behaviors common to all
rectangles, such as width, height, and area calculation. A specific subtype, Square, inherits
from Rectangle and introduces the constraint that the width and height must be equal.
Implementing the Square class directly within the Rectangle hierarchy appears straightforward.
However, this approach can lead to potential LSP violations. For instance, if the set_width()
or set_height() methods of the Square class allow for unequal values, it would contradict the
inherent property of a square.
To circumvent this issue, consider employing a factory class like RectangleFactory.
This class serves as a centralized entity responsible for creating instances of either Rectangle
or Square objects. It maintains the distinction between the two shapes, ensuring that only valid
squares are created.
The RectangleFactory approach offers several advantages. It promotes modularity and decoupling,
separating the creation of shapes from their actual implementation. This allows for different
implementations of Rectangle and Square classes without affecting the code that uses them,
enhancing code reusability and flexibility.
Moreover, the RectangleFactory approach enhances code maintainability. By encapsulating the creation
process, it becomes easier to track object creation and ensure that objects are created correctly,
reducing the risk of errors and improving code quality overall.
In conclusion, the Liskov Substitution Principle serves as a guiding principle for
object-oriented design, ensuring that subtypes uphold the expectations of their base classes.
While directly inheriting from the base class may seem convenient, it can introduce potential LSP
violations. Employing a factory class like RectangleFactory provides a more flexible, maintainable,
and robust solution, promoting consistent and predictable behavior throughout the system.
*/
class Rectangle
{
  protected:
    int width, height;

  public:
    Rectangle(const int width, const int height) : width{width}, height{height}
    {
    }

    int get_width() const
    {
        return width;
    }
    virtual void set_width(const int width)
    {
        this->width = width;
    }
    int get_height() const
    {
        return height;
    }
    virtual void set_height(const int height)
    {
        this->height = height;
    }

    int area() const
    {
        return width * height;
    }
};

class Square : public Rectangle
{
  public:
    Square(int size) : Rectangle(size, size)
    {
    }

    void set_width(int width) override
    {
        this->width = this->height = width;
    }

    void set_height(int height) override
    {
        this->width = this->height = height;
    }
};

void process(Rectangle &r)
{
    int w = r.get_width();
    r.set_height(10);

    std::cout << "expected area = " << (w * 10) << ", got " << r.area() << std::endl;
}

// To do !!
struct RectangleFactory
{
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};

int main()
{
    Rectangle r{3, 4};
    process(r);

    Square sq{5};
    process(sq);

    return 0;
}