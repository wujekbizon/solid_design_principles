#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
Applying the Single Responsibility Principle to Journal Entry Management
The single responsibility principle (SRP) is a fundamental design guideline in object-oriented programming
that advocates for classes to have a single reason to change. This means that each class should focus on a
specific responsibility and delegate other functionalities to separate classes. By adhering to the SRP,
developers can create more maintainable, reusable, and testable code.
In the context of managing journal entries, the SRP suggests that the Journal class should focus solely on
managing the journal entries themselves, such as adding, removing, and retrieving entries. It should not be
responsible for saving the entries to a file. Instead, the saving functionality should be delegated to a
separate class, such as PersistenceManager.
This separation of concerns promotes code modularity and improves maintainability. The Journal class remains
focused on its core responsibility of managing entries, while the PersistenceManager class handles the specific
details of file operations, such as opening, reading, and writing the file. This separation prevents the Journal
class from becoming cluttered with file-related code, making it easier to reason about and modify the core
journal management logic.
In the example code, the PersistenceManager class encapsulates the logic for saving journal entries to a file.
It utilizes a stringstream object to efficiently buffer the entries before writing them to the file.
It also handles memory allocation errors gracefully using a try-catch block.
The revised code effectively applies the SRP by delegating the saving functionality to a separate class, allowing
the Journal class to focus on its primary responsibility of managing journal entries. This demonstrates a good
understanding of the SRP and its application in object-oriented programming.
By following the SRP, developers can create more maintainable, reusable, and testable code, leading to more robust
and efficient software solutions.
*/

class Journal
{
    // Represents a journal with a title and a list of entries
  public:
    std::string_view title;
    std::vector<std::string> entries{};

    // Constructor that sets the title of the journal
    Journal(const std::string &entry) : title(title)
    {
    }

    // Adds an entry to the journal
    void add_entry(const std::string &entry);

    // Saves the journal entries to a file but to keep Single Responsibility Principle
    // is better to delegates the saving functionality to the `PersistenceManager` class
    void save(const std::string &filename);
};

// Adds an entry to the journal
void Journal::add_entry(const std::string &entry)
{
    // Assigns a unique entry number
    static int count{1};
    // Adds the entry to the list with a numbered prefix
    entries.push_back(std::to_string(count++) + ": " + entry);
}

// Saves the journal entries to a file
void Journal::save(const std::string &filename)
{
    // Creates a file stream to write to the specified filename
    std::ofstream ofs{filename};
    // Iterates through the list of entries and writes each entry to the file
    for (auto &e : entries)
        ofs << e << std::endl; // Writes each entry to the file with a newline
}

// Class for managing the persistence of journal entries
class PersistenceManager
{
  public:
    // Saves the journal entries from the specified `journal` object to the specified `filename`
    void save(const Journal &j, const std::string &filename);
};

// Saves the journal entries from the specified `journal` object to the specified `filename`
void PersistenceManager::save(const Journal &j, const std::string &filename)
{
    try
    {
        // Allocate memory for the stringstream object
        std::stringstream buffer;

        // Writes the journal entries to the string stream object
        for (auto &s : j.entries)
            buffer << s << std::endl; // Writes each entry to the buffer

        // Write the contents of the stringstream to the file
        std::ofstream ofs{filename};
        ofs << buffer.str(); // Writes the buffer's contents to the file
    }
    catch (const std::bad_alloc &e)
    {
        // Handles memory allocation errors by printing an error message to the console
        std::cerr << "Failed to allocate memory: " << e.what() << std::endl;
        return;
    }
}

int main()
{
    // Creates a journal with the title
    Journal journal{"Dear Diary"};
    // Adds entries to the journal
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");
    journal.add_entry("I implemented single responsibility design principle");

    // Instead of calling the `save` method directly on the `Journal` object,
    // delegates the saving functionality to the `PersistenceManager` class
    PersistenceManager pm;
    pm.save(journal, "diary.txt");

    // Gets user input to prevent the program from exiting prematurely
    getchar();
    return 0;
}