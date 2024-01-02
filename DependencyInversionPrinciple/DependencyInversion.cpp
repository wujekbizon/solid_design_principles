#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <vector>

/*
Dependency Inversion Principle (DIP) is a crucial design principle that promotes loose
coupling and code maintainability. It advocates for high-level modules to depend on
abstractions rather than low-level implementations. This approach ensures that high-level
modules are not tied to specific low-level details, making them more adaptable to change
and easier to reuse.
In the provided code example, the RelationshipBrowser interface serves as the abstraction layer,
defining the high-level requirements for accessing family relationships. The Relationships
class implements the data storage and access logic, providing a concrete implementation of
the RelationshipBrowser interface.
The Research class, a high-level module, utilizes the RelationshipBrowser interface to retrieve
family information. This decoupling allows for different implementations of RelationshipBrowser to
be used without affecting the Research class, promoting flexibility and extensibility.
As beginners delve into design principles, this code example effectively illustrates DIP's concept
of abstraction and its impact on code maintainability. It demonstrates how to create flexible and
reusable software systems that can adapt to changing requirements.
*/

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details.
//    Details should depend on abstractions.

/**
 * An enum representing the different types of relationships between two persons.
 */
enum class Relationship
{
    parent,
    child,
    sibling
};

/**
 * A structure representing a person who has a name.
 */
struct Person
{
    std::string_view name;
};

/**
 * An interface for classes that can browse relationships between people.
 */
class RelationshipBrowser
{
  public:
    /**
     * Returns a vector of pointers to all the children of the person with the given name.
     *
     * @param name The name of the person whose children should be found.
     * @return A vector of pointers to the children of the given person.
     */
    virtual std::vector<Person *> findAllChildrenOf(const std::string_view &name) = 0;
};

// low-level module - what it does it is provides functionality for data storage.
// we have this vector of tuples and it has a couple of utility functions for actually populating that
// storage.

/**
 * A concrete implementation of the RelationshipBrowser interface that stores relationships
 * in a vector of tuples.
 */
class Relationships : public RelationshipBrowser
{
  public:
    /**
     * A vector of tuples representing the relationships between people.
     */
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    /**
     * Adds a parent-child relationship between the given parents and child.
     *
     * @param parent The parent person.
     * @param child The child person.
     */
    void addParentAndChild(const Person &parent, const Person &child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    /**
     * Overrides the findAllChildrenOf() method of the RelationshipBrowser interface.
     *
     * Returns a vector of pointers to all the children of the person with the given name.
     *
     * @param name The name of the person whose children should be found.
     * @return A vector of pointers to the children of the given person.
     */
    std::vector<Person *> findAllChildrenOf(const std::string_view &name) override
    {
        std::vector<Person *> result;

        for (auto &[first, rel, second] : relations)
        {
            if (first.name == name && rel == Relationship::parent)
            {
                result.push_back(&second);
            }
        }
        return result;
    }
};

// High-level module
class Research
{
  public:
    // Constructor - Accepts a `RelationshipBrowser` object to access the relationships
    Research(RelationshipBrowser &browser, std::string_view name)
    {
        // Iterate through the children of the person named "John"
        for (auto &child : browser.findAllChildrenOf(name))
        {
            // Print the name of each child
            std::cout << name << " has a child called " << child->name << std::endl;
        }
    }

    // Destructor - Empty as there are no resources to deallocate
    ~Research()
    {
    }

    /*
        // Alternative constructor that directly accesses the relationships data
         Research(Relationships &relationships)
        {
               // Access the relationships vector from the `relationships` object
             auto &relations = relationships.relations;
               // Iterate through the relationships, searching for the parent-child pair with "John" as the parent
             for (auto &&[first, rel, second] : relations)
             {
                   // Check if the first person is "John" and the relationship is "parent"
                 if (first.name == "John" && rel == Relationship::parent)
                 {
                     std::cout << "John has a child called " << second.name << std::endl;
                 }
             }
        }
    */
};

int main()
{
    // Create persons
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Person parent2{"Greg"};
    Person child3{"Dominic"};

    // Create a Relationships object to store the relationships
    Relationships relationships;
    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);
    relationships.addParentAndChild(parent2, child3);

    // Create an instance of the Research class using the Relationships object
    Research exploreRelationships(relationships, "Greg");

    return 0;
}