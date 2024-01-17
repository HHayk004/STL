#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>            // for cout
#include <limits>              // for m_max_size calculation
#include <initializer_list>    // for initializer list constructor and assignment operator

/**
 *  A template class representing a generic Queue.
 * tparam T Type of elements stored in the Queue.
 */
template <typename T>
class Queue
{
private:
    T* m_ptr;               // Pointer to dynamic memory
    size_t m_start;         // Beginning of the queue by index
    size_t m_end;           // One past the end of the queue by index
    const size_t m_max_size = std::numeric_limits<size_t>::max() / sizeof(T);  // Queue elements count limit
    size_t m_capacity;       // Capacity of dynamic memory

    /**
     *  Private method to reallocate memory for resizing the queue.
     */
    void realloc();

public:
    /**
     *  Default constructor for the Queue class.
     */
    Queue();

    /**
     *  Constructor for the Queue class with an initializer list.
     *  list An initializer list to initialize the Queue.
     */
    Queue(std::initializer_list<T>);

    /**
     *  Copy constructor for the Queue class.
     *  other The Queue to be copied.
     */
    Queue(const Queue<T>&) noexcept;

    /**
     *  Move constructor for the Queue class.
     *  other The Queue to be moved.
     */
    Queue(Queue<T>&&) noexcept;

    /**
     *  Destructor for the Queue class.
     */
    ~Queue();

    /**
     *  Overloaded stream insertion operator for outputting the Queue.
     *  os The output stream.
     *  return The modified output stream.
     */
    std::ostream& operator<<(std::ostream&) const;

    /**
     *  Assignment operator for initializing the Queue with an initializer list.
     *  list An initializer list to assign to the Queue.
     *  return A reference to the modified Queue.
     */
    Queue& operator=(std::initializer_list<T>);

    /**
     *  Copy assignment operator for the Queue class.
     *  other The Queue to be copied.
     *  return A reference to the modified Queue.
     */
    Queue& operator=(const Queue&) noexcept;

    /**
     *  Move assignment operator for the Queue class.
     *  other The Queue to be moved.
     *  return A reference to the modified Queue.
     */
    Queue& operator=(Queue&&) noexcept;

    /**
     *  Get the current size of the Queue.
     *  return The size of the Queue.
     */
    size_t size() const;

    /**
     *  Get the current capacity of the Queue.
     *  return The capacity of the Queue.
     */
    size_t capacity() const;

    /**
     *  Get the element at the front of the Queue.
     *  return The element at the front of the Queue.
     */
    T front() const;

    /**
     *  Get the element at the rear of the Queue.
     *  return The element at the rear of the Queue.
     */
    T rear() const;

    /**
     *  Add an element to the end of the Queue.
     *  value The value to be added to the Queue.
     */
    void push(T value);

    /**
     *  Remove the element from the front of the Queue.
     */
    void pop();

    /**
     *  Check if the Queue is empty.
     *  return True if the Queue is empty, false otherwise.
     */
    bool isEmpty() const;
};

#include "queue.hpp"
#endif // QUEUE_H

