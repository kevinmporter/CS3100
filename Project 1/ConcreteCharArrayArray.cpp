////////////////////////////////////////////
/// Kevin Porter
/// CS3100
/// ConcreteCharArrayArray implementation
///////////////////////////////////////////

#include "ConcreteCharArray.h"
#include <assert.h>
#include "ConcreteCharArrayArray.h"

////////////////////
/// Constructor
///////////////////
ConcreteCharArrayArray::ConcreteCharArrayArray()
{
    length = 0;
    memory = NULL;
}

////////////////////
/// Destructor
///////////////////
ConcreteCharArrayArray::~ConcreteCharArrayArray()
{
    // be a good citizen, release memory on destruct
    if (memory != NULL) {
        free(memory);
    }
}

void ConcreteCharArrayArray::setAt(CharArray * const  &anElement, size_t index)
{
    // only allow new elements or changing elements
    assert(index < size() + 1);
    // if it's a new element, increase the array to allow for it
    if (index == size()) {
        CharArray **insert = NULL;
        length = size() + 1;
        insert = (CharArray **) realloc(memory, (size() * sizeof(CharArray *)));

        if (insert != NULL)
        { // migrate array if realloc was successful
            memory = insert;

        }
    }
    // always set the new element
    memory[index] = anElement;
}

void ConcreteCharArrayArray::insertAt(CharArray * const &anElement, size_t index)
{
    // only allow insertions within the array or at the end
    assert(index < size() + 1);
    CharArray **insert = NULL;
    if (index < size() + 1)
    {
        length = size() + 1;
        insert = (CharArray **) realloc(memory, (sizeof(CharArray *) * length));

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

void ConcreteCharArrayArray::removeAt(size_t index)
{
    // only allow removes from inside the array
    assert(index < size());
    CharArray **remove = NULL;
    for (size_t i = index; i < size(); i++)
    { // make remove element at index and close gap
        memory[i] = memory[i + 1];
    }
    length = size() - 1;
    remove = (CharArray **)realloc(memory, size() * sizeof(CharArray *));

    if (remove != NULL)
    { // migrate memory iff realloc was successful
        memory = remove;
    }
}

CharArray * const &ConcreteCharArrayArray::at(size_t index) const
{
    return memory[index];
}

CharArray * &ConcreteCharArrayArray::at(size_t index)
{
    return memory[index];
}

size_t ConcreteCharArrayArray::size() const
{
    const size_t return_value = length;
    return return_value;
}
