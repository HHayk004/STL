#ifndef QUEUE_HPP
#define QUEUE_HPP

// Function template to overload << operator for Queue<T> objects
template <typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& other)
{
    return other.operator<<(os); // Calls the method to print the queue
}

// Default constructor for Queue
template <typename T>
Queue<T>::Queue()
{
    m_ptr = nullptr; // Initializes fields to default values
    m_start = 0;
    m_end = 0;
    m_capacity = 0;
}

// Constructor to initialize Queue from an initializer list
template <typename T>
Queue<T>::Queue(std::initializer_list<T> list)
{
    m_start = 0; // Initializes the beginning of the queue
    m_end = list.size(); // Initializes the end of the queue
    m_capacity = m_end + 10; // Calculates the capacity; 10 is for future pushes
    m_ptr = new T [m_capacity]{0}; // Allocates memory for the queue
    int i = 0; // Index for m_ptr
    for (auto& elem : list) // Copies elements from the initializer list to the queue
    {
        m_ptr[i] = elem;
        ++i;
    }
}

// Copy constructor for Queue
template <typename T>
Queue<T>::Queue(const Queue<T>& other) noexcept
{
    m_start = other.m_start;
    m_end = other.m_end;
    m_capacity = other.m_capacity;

    // Check if the queue is empty
    if (m_capacity == 0)
    {
        m_ptr = nullptr;
    }
    else
    {
        // Allocate memory and copy elements from the source queue
        m_ptr = new T [m_capacity]{0};
        for (int i = m_start; i < m_end; ++i)
        {
            m_ptr[i] = other.m_ptr[i];
        }
    }
}

// Move constructor for Queue
template <typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept
{
    m_start = std::move(other.m_start);
    m_end = std::move(other.m_end);
    m_capacity = std::move(other.m_capacity);
    m_ptr = std::move(other.m_ptr);

    // Reset the source queue
    other.m_start = 0;
    other.m_end = 0;
    other.m_capacity = 0;
    other.m_ptr = nullptr;
}

// Destructor for Queue
template <typename T>
Queue<T>::~Queue()
{
    // Deallocate memory and reset fields
    delete[] m_ptr;
    m_ptr = nullptr;
    m_start = 0;
    m_end = 0;
    m_capacity = 0;
}

// Overloaded << operator for printing the Queue
template <typename T>
std::ostream& Queue<T>::operator<<(std::ostream& os) const
{
    // Prints each element of the queue
    for (int i = m_start; i < m_end; ++i)
    {
        std::cout << m_ptr[i] << ' ';
    }
    return os;
}

// Assignment operator for initializer_list
template <typename T>
Queue<T>& Queue<T>::operator=(std::initializer_list<T> list)
{
    // Resets the queue and copies elements from the initializer list
    m_start = 0;
    m_end = list.size();

    if (m_end > m_capacity)
    {
        realloc(); // Resizes the queue if needed
    }

    int i = 0;
    for (auto& elem : list)
    {
        m_ptr[i] = elem; // Copies elements from the initializer list to the queue
        ++i;
    }

    return *this;
}

// Assignment operator for copying from another Queue
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) noexcept
{
    if (this != &other)
    {
        m_start = 0;
        m_end = other.size();

        if (m_end > m_capacity)
        {
            realloc(); // Resizes the queue if needed
        }

        for (int i = other.m_start, j = 0; i < other.m_end; ++i, ++j)
        {
            m_ptr[j] = other.m_ptr[i]; // Copies elements from the source queue to the current queue
        }
    }

    return *this;
}

// Assignment operator for moving from another Queue
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
{
    delete[] m_ptr; // deleting old memory

    m_start = std::move(other.m_start);
    m_end = std::move(other.m_end);
    m_capacity = std::move(other.m_capacity);
    m_ptr = std::move(other.m_ptr);

    // Reset the source queue
    other.m_start = 0;
    other.m_end = 0;
    m_capacity = 0;
    m_ptr = nullptr;

    return *this;
}

// Resizes the queue, either shrinking or expanding
template <typename T>
void Queue<T>::realloc()
{
    if (m_capacity / 2 > size())
    {
        for (int i = m_start, j = 0; i < m_end; ++i, ++j)
        {
            m_ptr[j] = m_ptr[i]; // Shifts elements to the beginning of the queue
        }

        m_end = size();
        m_start = 0;
    }
    else
    {
        m_capacity = size() + 10; // Calculates new capacity with some additional space
        T* new_ptr = new T [m_capacity];

        for (int i = m_start, j = 0; i < m_end; ++i, ++j)
        {
            new_ptr[j] = m_ptr[i]; // Copies elements to the new memory block
        }

        m_end = size();
        m_start = 0;

        delete[] m_ptr;
        m_ptr = new_ptr; // Updates the pointer to the new memory block
        new_ptr = nullptr;
    }
}

// Returns the size of the queue
template <typename T>
size_t Queue<T>::size() const
{
    return m_end - m_start;
}

// Returns the current capacity of the queue
template <typename T>
size_t Queue<T>::capacity() const
{
    return m_capacity;
}

// Returns the front element of the queue
template <typename T>
T Queue<T>::front() const
{
    if (isEmpty())
    {
        std::cerr << "Empty for front:\n"; // Displays an error message if the queue is empty
        exit(-1);
    }

    return m_ptr[m_start];
}

// Returns the rear element of the queue
template <typename T>
T Queue<T>::rear() const
{
    if (isEmpty())
    {
        std::cerr << "Empty for rear:\n"; // Displays an error message if the queue is empty
        exit(-1);
    }

    return m_ptr[m_end - 1];
}

// Adds a new element to the end of the queue
template <typename T>
void Queue<T>::push(T val)
{
    if (m_end == m_capacity)
    {
        realloc(); // Resizes the queue if needed before pushing
    }

    m_ptr[m_end] = val; // Adds the new element to the end of the queue
    ++m_end;
}

// Removes the front element from the queue
template <typename T>
void Queue<T>::pop()
{
    if (isEmpty())
    {
        std::cerr << "Empty for pop:\n"; // Displays an error message if the queue is empty
        exit(-1);
    }

    ++m_start; // Removes the front element by shifting the start index
}

// Checks if the queue is empty
template <typename T>
bool Queue<T>::isEmpty() const
{
    return m_start == m_end; // Returns true if the start index equals the end index, indicating an empty queue
}

#endif

