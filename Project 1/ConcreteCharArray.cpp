////////////////////////////////////////////
/// Kevin Porter
/// CS3100
/// ConcreteCharArray implementation
///////////////////////////////////////////

#include "ConcreteCharArray.h"
////////////////////
/// Constructor
///////////////////
ConcreteCharArray::ConcreteCharArray()
{
    // initialize variables
    length = 0;
    memory = NULL;
}

///////////////////
/// Destructor
///////////////////
ConcreteCharArray::~ConcreteCharArray()
{
    // be a good citizen, release memory on destruct
    if (memory != NULL) {
        free(memory);
    }
}

void ConcreteCharArray::setAt(const char &anElement, size_t index)
{
    // only allow set values inside the array or allow a new value at the end
    assert(index < size() + 1);
    // if the new value goes at the end, be sure to increase the array size
    if (index == size())
    {
        char *insert = NULL;
        length = size() + 1;
        insert = (char *)realloc(memory, (size() * sizeof(char)));

        if (insert != NULL)
        { // migrate the array if realloc was successful
            memory = insert;
        }
    }
    // always set the new element at the index
    memory[index] = anElement;

}

void ConcreteCharArray::insertAt(const char &anElement, size_t index)
{
    // only allow insertions within the array or at the end
    assert(index < size() + 1);
    char *insert = NULL;
    if (index < size() + 1)
    {
        length = size() + 1;
        insert = (char *)realloc(memory, (size() * sizeof(char)));

        if (insert != NULL)
        { // migrate the array if realloc was successful
            memory = insert;
            // size - 1 because size references the new array size, not the current array size
            for (size_t i = size() - 1; i > index; i--)
            { // make room for the new element
                memory[i] = memory[i - 1];
            }
            memory[index] = anElement;
        }
    }
}

void ConcreteCharArray::removeAt(size_t index)
{
    // only allow remove from existing parts of the array
    assert(index < size());
    char *remove = NULL;
    for (size_t i = index; i < size(); i++)
    { // remove element at index and close gap
        memory[i] = memory[i + 1];
    }
    length = size() - 1;
    remove = (char *)realloc(memory, (size() * sizeof(char)));

    if (remove != NULL)
    { // migrate array if realloc was successful
        memory = remove;
    }
}

char const &ConcreteCharArray::at(size_t index) const
{
    return memory[index];
}

char &ConcreteCharArray::at(size_t index)
{
    return memory[index];
}

size_t ConcreteCharArray::size() const
{
    const size_t return_value = length;
    return return_value;
}
