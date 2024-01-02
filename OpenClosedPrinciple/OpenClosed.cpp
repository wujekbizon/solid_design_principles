#include <iostream>
#include <string>
#include <vector>

// Define an enum class `Color` to represent the colors of products.
enum class Color
{
    red,
    green,
    blue
};

// Define an enum class `Size` to represent the sizes of products.
enum class Size
{
    small,
    medium,
    large
};

// Define a struct `Product` to represent a product.
struct Product
{
    // The name of the product.
    std::string name;

    // The color of the product.
    Color color;

    // The size of the product.
    Size size;
};

// Define a class `ProductFilter` to represent a product filter.
class ProductFilter
{
    // Define a typedef `Items` for a vector of pointers to `Product` objects.
    typedef std::vector<Product *> Items;

  public:
    // Define a function `by_color()` to filter products by color.
    Items by_color(Items items, Color color)
    {
        // Define a vector `result` to store the filtered products.
        Items result;
        // Iterate over the `items` vector and add products to the `result` vector
        // if their color matches the specified `color`.
        for (auto &i : items)
            if (i->color == color)
                result.push_back(i);
        // Return the `result` vector containing the filtered products.
        return result;
    }

    // Define a function `by_size()` to filter products by size.
    Items by_size(Items items, Size size)
    {
        // Define a vector `result` to store the filtered products.
        Items result;
        /*
        Iterate over the `items` vector and add products to the `result` vector if
        their size matches the specified `size`.
        */
        for (auto &i : items)
            if (i->size == size)
                result.push_back(i);
        // Return the `result` vector containing the filtered products.
        return result;
    }

    // Define a function `by_size_and_color()` to filter products by both size and color.
    Items by_size_and_color(Items items, Color color, Size size)
    {
        // Define a vector `result` to store the filtered products.
        Items result;
        /*
        Iterate over the `items` vector and add products to the `result` vector if their
        size and color match the specified values.
        */
        for (auto &i : items)
            if (i->size == size && i->color == color)
                result.push_back(i);
        // Return the `result` vector containing the filtered products.
        return result;
    }
};

// template struct AndSpecification declaration
template <typename T> struct AndSpecification;

// `Specification` is a template class representing a generic filter
// condition for objects of type `T`.
template <typename T> class Specification
{
  public:
    // Destructor
    virtual ~Specification() = default;

    // `is_satisfied` checks whether the specified object meets the filter
    // condition.
    virtual bool is_satisfied(T *item) = 0;

    // new: breaks OCP if you add it post-hoc
    AndSpecification<T> operator&&(Specification<T> &&other)
    {
        return AndSpecification<T>(*this, other);
    }
};

// defines an overloaded operator for combining two Specification objects using the && operator. This operator takes two
// references to Specification objects (first and second) and returns a new AndSpecification object that combines the
// two filtering criteria.

template <typename T> AndSpecification<T> operator&&(Specification<T> &first, Specification<T> &second)
{
    /*
    This operator overload allows combining two specifications using
    the logical AND (`&&`) operator.
    It returns an `AndSpecification` object that represents the
    logical AND of the two input specifications.
    The `AndSpecification` object is constructed with references to
    the two input specifications, so it can access their member
    functions to check whether the specified object meets the filter
    condition.
    */
    return {first, second};
}

template <typename T> class Filter
{
    // A filter is a class that takes a collection of objects of type T and a
    // specification, and returns a new collection containing only the objects
    // that satisfy the specification.

    // The `filter` method is a pure virtual function that must be implemented
    // by any class that inherits from `Filter`. This method takes a
    // `std::vector<T *>` containing the objects to be filtered, and a
    // `Specification<T>` object that represents the filter criteria. The
    // method must return a new `std::vector<T *>` containing only the objects
    // that satisfy the filter criteria.
  public:
    virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> &spec) = 0;
};

class BetterFilter : Filter<Product>
{
    /*
     `BetterFilter` is a class that inherits from `Filter<Product>`, which
     means that it can be used to filter collections of products. This
     class overrides the `filter` method to provide a more efficient way
     to filter products.
     The `filter` method takes a `std::vector<Product *>` containing the
     products to be filtered, and a `Specification<Product>` object that
     represents the filter criteria. The method iterates through the
     products in the `items` vector and adds the products that satisfy the
     specifications to the `result` vector.
    */

  public:
    std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> &spec) override
    {
        std::vector<Product *> result;
        for (auto &item : items)
            if (spec.is_satisfied(item))
                result.push_back(item);
        return result;
    }
};

// `ColorSpecification` is a struct that inherits from `Specification<Product>`,
// which means it can be used to filter products based on their color.
struct ColorSpecification : Specification<Product>
{
    // `color` is a member variable that stores the color of the products
    // to be filtered.
    Color color;

    // Constructor initializes the `color` member to the specified color.
    explicit ColorSpecification(Color color) : color{color}
    {
    }

    // `is_satisfied` checks whether the specified product's color matches
    // the specified color.
    bool is_satisfied(Product *item) override
    {
        // Returns `true` if the product's color is equal to the specified
        // color, and `false` otherwise.
        return item->color == color;
    }
};

// `SizeSpecification` is a structure that inherits from `Specification<Product>`,
// which means that it can be used to filter products based on their size.
struct SizeSpecification : Specification<Product>
{
    // `size` is a member variable that stores the size of the products
    // to be filtered.
    Size size;

    // Constructor initializes the `size` member to the specified size.
    explicit SizeSpecification(Size size) : size(size)
    {
    }

    // `is_satisfied` checks whether the specified product's size matches
    // the specified size.
    bool is_satisfied(Product *item) override
    {
        // Returns `true` if the product's size is equal to the specified
        // size, and `false` otherwise.
        return item->size == size;
    }
};

template <typename T> struct AndSpecification : Specification<T>
{
    // `first` and `second` are references to the two specifications to be
    // combined. These references allow the `AndSpecification` object to
    // access the member functions of the specifications being combined.
    Specification<T> &first;
    Specification<T> &second;

    // The constructor initializes the `first` and `second` members with
    // the references to the specifications passed to the constructor.
    AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second)
    {
    }

    // `is_satisfied` checks whether the specified object meets the filter
    // condition. This function returns `true` if both of the specifications
    // being combined are satisfied for the specified object.
    bool is_satisfied(T *item) override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main()
{
    // Create three products with different colors and sizes:
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    // Create a vector of pointers to the products:
    std::vector<Product *> items{&apple, &tree, &house};

    // Create a `BetterFilter` object to filter products:
    BetterFilter bf;
    // Create a `ColorSpecification` object to filter for green products:
    ColorSpecification green(Color::green);

    // Use the `filter` method to get a list of green products:
    for (auto &item : bf.filter(items, green))
    {
        // Print the name of each green product:
        std::cout << item->name << " is green \n";
    }

    // Create a `SizeSpecification` object to filter for large products:
    SizeSpecification large(Size::large);

    // Create an `AndSpecification<Product>` object to combine the green and large criteria:
    AndSpecification<Product> green_and_large(green, large);

    // Use the `filter` method to get a list of green and large products:
    for (auto &item : bf.filter(items, green_and_large))
    {
        std::cout << item->name << " is green and large \n";
    }

    // Alternatively, combine the specifications using the && operator and store the result in a temporary variable:
    auto spec = green && large;

    // Use the `filter` method with the combined specification:
    for (auto &item : bf.filter(items, spec))
    {
        // Print the name of each product that meets both criteria:
        std::cout << item->name << " is green and large\n";
        // **Note:** This explicitly creates an AndSpecification<Product> object using the && operator.
    }
    // Create an explicit `ColorSpecification` object for blue:
    auto colorSpec = ColorSpecification(Color::blue);

    // Create an explicit `SizeSpecification` object for large:
    auto sizeSpec = SizeSpecification(Size::large);

    //  Combine the specifications using the && operator, creating an AndSpecification<Product> object:
    auto spec4 = colorSpec && sizeSpec;

    for (auto &item : bf.filter(items, spec4))
        // Print the name of each product that meets both criteria:
        std::cout << item->name << " is blue and large\n";

    std::cout << "Done!" << std::endl;
    return 0;
}