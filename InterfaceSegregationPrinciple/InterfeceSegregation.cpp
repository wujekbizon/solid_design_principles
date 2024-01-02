#include <iostream>

/*
Understanding the Interface Segregation Principle (ISP)
The Interface Segregation Principle (ISP) is a fundamental design principle in object-oriented
programming (OOP) that aims to modularize interfaces to make them more targeted and focused.
This helps to improve code maintainability, flexibility, and reusability.
In the example provided, the IMachine interface is broken down into smaller, more specific
interfaces: IPrinter, IScanner, and IFax. This allows implementers, such as Scanner and Printer
classes, to only implement the methods that are relevant to their functionality. This approach
decouples classes and reduces code duplication, making the code more maintainable and easier to modify.
The Machine class demonstrates how to combine multiple interfaces into a single object, effectively
representing a multi-functional device like a multifunction printer (MFP). By inheriting from both
IPrinter and IScanner, the Machine class can handle both printing and scanning tasks, offering a more
flexible and reusable solution compared to a monolithic interface.

By adhering to the ISP, developers can write cleaner, more modular, and maintainable code, leading to better-structured
and more flexible applications. The ISP is a valuable tool for OOP developers, particularly for beginners who are
learning about design principles and modularization.

The Interface Segregation Principle (ISP) is a way to avoid forcing implementors to implement methods that they don't
need. This can make code more modular and easier to maintain. The ISP can also improve code reuse. By breaking down
interfaces into smaller, more specific ones, you can create more reusable components. The ISP is often used in
conjunction with other design principles, such as the Dependency Inversion Principle (DIP).
*/

struct Document;

/*
struct IMachine
{
    virtual void print(Document &doc) = 0;
    virtual void scan(Document &doc) = 0;
    virtual void fax(Document &doc) = 0;
};

struct MFP : IMachine
{
    void print(Document &doc) override
    {
        // print logic
    }
    void scan(Document &doc) override
    {
        // scan logic
    }
    void fax(Document &doc) override
    {
        // fax logic
    }
};

struct Scanner : IMachine
{
    void print(Document &doc) override
    {
    }
    void scan(Document &doc) override
    {
        // ok
    }
    void fax(Document &doc) override
    {
    }
};
*/
// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

// design interface segregation

struct IPrinter
{
    virtual void print(Document &doc) = 0;
};

struct IScanner
{
    virtual void scan(Document &doc) = 0;
};

struct IFax
{
    virtual void fax(Document &doc) = 0;
};

struct Scanner : IScanner
{
    void scan(Document &doc) override
    {
    }
};

struct Printer : IPrinter
{
    void print(Document &doc) override
    {
    }
};

struct IMachine : IPrinter, IScanner
{
};

struct Machine : IMachine
{
    // build a decorator
    IPrinter &printer;
    IScanner &scanner;

    // constructor
    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner)
    {
    }

    // destructor
    ~Machine()
    {
    }

    void print(Document &doc) override
    {
        printer.print(doc);
    }

    void scan(Document &doc) override
    {
        scanner.scan(doc);
    }
};

int main()
{

    return 0;
}
