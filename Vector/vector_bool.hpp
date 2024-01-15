// bool vector specialization

#define BYTE (sizeof(uint8_t) * 8) // macro for bool vector element size in bits

std::ostream& operator<<(std::ostream& os, const Vector<bool>& other) // global operator for printing whole bool vector
{
    return other.operator<<(os);
}

std::ostream& Vector<bool>::operator<<(std::ostream& os) const // class method for printing whole bool vector
{
    for (int i = 0; i < m_size; ++i) // printing whole bool vector
    {
        std::cout << at(i) << ' ';
    }
    return os;
}

Vector<bool>& Vector<bool>::operator=(std::initializer_list<bool> list) // assignment operator with initializer list
{
    m_size = list.size(); // assign new size;
    
    if (m_size > m_capacity) // checking for resize
    {
        resize(m_size);
    }    

    int index = 0;
    for (const auto& elem: list) // copying the elements from list
    {
        m_ptr[index] = elem;
    }

    return *this; // returning the object
}

Vector<bool>& Vector<bool>::operator=(const Vector& other) noexcept // assignment operator with copy
{
    if (this != &other) // checking for self-assignment
    {
        m_size = other.m_size; // assign the fields
        m_capacity = other.m_capacity;

        delete[] m_ptr; // delete old space
        m_ptr = new uint8_t [m_capacity]; // allocating new space
    
        for (int i = 0; i < m_size; ++i) // copying the elements
        {
            m_ptr[i] = other.m_ptr[i];
        }
    }

    return *this;
}

// Move assignment operator for Vector<bool>
Vector<bool>& Vector<bool>::operator=(Vector&& other) noexcept
{
    // Move size and capacity from 'other'
    m_size = std::move(other.m_size);
    m_capacity = std::move(other.m_capacity);

    // Move pointer and invalidate 'other'
    delete[] m_ptr;
    m_ptr = std::move(other.m_ptr);

    // Reset 'other' to a valid state
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_ptr = nullptr;

    return *this;
}

// Access element at the given index, with bounds checking
bool Vector<bool>::at(size_t index) const
{
    // Check if the index is out of bounds
    if (index >= m_size)
    {
        std::cerr << "Index >= m_size for [] operator:\n";
        exit(-1);
    }

    // Create a Reference object for the specified index
    Reference ref(m_ptr, index);
    return ref;
}

// Default constructor
Vector<bool>::Vector()
{
    m_ptr = nullptr;
    m_size = 0;
    m_capacity = 0;
}

// Constructor with size and default value
Vector<bool>::Vector(size_t size, bool obj)
{
    // Set size and calculate capacity
    m_size = size;
    m_capacity = m_size / BYTE + 1;
    m_ptr = new uint8_t[m_capacity]{}; // Initialize with zero

    // Initialize elements with the specified value
    for (int i = 0; i < size; ++i)
    {
        (*this)[i] = obj;
    }
}

// Constructor with an initializer list
Vector<bool>::Vector(std::initializer_list<bool> list)
{
    // Set size and calculate capacity
    m_size = list.size();
    m_capacity = m_size / BYTE + 1;
    m_ptr = new uint8_t[m_capacity]{}; // Initialize with zero

    int index = 0;
    // Iterate through the initializer list and set bits accordingly
    for (const auto& elem : list)
    {
        m_ptr[index / BYTE] |= elem << (index % BYTE);
        ++index;
    }
}

// Copy constructor
Vector<bool>::Vector(const Vector<bool>& other) noexcept
{
    // Copy size and capacity
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    // Allocate new memory and copy elements
    m_ptr = new uint8_t[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        m_ptr[i] = other.m_ptr[i];
    }
}

// Move constructor
Vector<bool>::Vector(Vector<bool>&& other) noexcept
{
    // Move size, capacity, and pointer
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_ptr = other.m_ptr;

    // Reset 'other' to a valid state
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_ptr = nullptr;
}

// Destructor
Vector<bool>::~Vector()
{
    // Deallocate memory
    delete[] m_ptr;
    m_ptr = nullptr;
}

// Reference constructor with a pointer and index
Vector<bool>::Reference::Reference(uint8_t* ptr1, size_t index1) :
    ptr(ptr1), index(index1)
{
    // Initialize flag based on the bit at the specified index
    flag = (ptr[index / BYTE] >> (index % BYTE)) & 1;
}

// Copy constructor for Reference
Vector<bool>::Reference::Reference(const Reference& obj) noexcept
{
    // Copy index, pointer, and flag
    index = obj.index;
    ptr = obj.ptr;
    flag = obj.flag;
}

// Subscript operator for Vector<bool>
Vector<bool>::Reference Vector<bool>::operator[](size_t index)
{
    // Create and return a Reference object for the specified index
    return Vector::Reference(m_ptr, index);
}

// Move constructor for Reference
Vector<bool>::Reference::Reference(Reference&& obj) noexcept
{
    // Move index, pointer, and flag, and invalidate 'obj'
    index = obj.index;
    ptr = obj.ptr;
    flag = obj.flag;
    obj.ptr = nullptr;
    obj.index = 0;
    obj.flag = 0;
}

// Assignment operator for Reference
Vector<bool>::Reference& Vector<bool>::Reference::operator=(bool flag)
{
    // Set the bit at the specified index to the new flag value
    if (this->flag != flag)
    {
        ptr[index / BYTE] &= ~(1 << (index % BYTE));
        ptr[index / BYTE] |= (flag << (index % BYTE));
    }
    return *this;
}

// Assignment operator for Reference
Vector<bool>::Reference& Vector<bool>::Reference::operator=(const Reference& obj)
{
    // Assign the flag value from 'obj'
    if (flag != obj.flag)
    {
        (*this) = obj.flag;
    }
    return *this;
}

// Conversion operator to bool for Reference
Vector<bool>::Reference::operator bool() const
{
    return flag;
}

// Return a pointer to the underlying data
uint8_t* Vector<bool>::data() const
{
    return m_ptr;
}

// Reserve memory for a specified capacity
void Vector<bool>::reserve(size_t new_capacity)
{
    // Check if the new capacity is within bounds
    if (new_capacity > m_max_size)
    {
        std::cerr << "Erong size for reserve:\n"; // Typo: 'Er...'; should be 'Wrong size for reserve:'
        exit(-1);
    }

    // Calculate new capacity in bytes
    new_capacity = new_capacity / BYTE + static_cast<bool>(new_capacity % BYTE);

    // Check if reallocation is needed
    if (new_capacity > m_capacity)
    {
        m_capacity = new_capacity;

        // Allocate new memory and copy existing elements
        if (m_ptr == nullptr)
        {
            m_ptr = new uint8_t[m_capacity];
        }
        else
        {
            uint8_t* new_ptr = new uint8_t[m_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_ptr[i] = m_ptr[i];
            }

            // Deallocate old memory and update the pointer
            delete[] m_ptr;
            m_ptr = new_ptr;
            new_ptr = nullptr;
        }
    }
}

// Resize the vector to a new size
void Vector<bool>::resize(size_t new_size)
{
    // Check if the new size is within bounds
    if (new_size > m_max_size)
    {
        std::cerr << "new_size > m_max_size in resize:\n";
        exit(-1);
    }

    // Calculate new size in bytes
    new_size = new_size / BYTE + static_cast<bool>(new_size % 8);

    // Check if reallocation is needed
    if (m_ptr == nullptr)
    {
        // Allocate new memory if the vector is empty
        m_capacity = new_size;
        m_ptr = new uint8_t[m_capacity]{};
    }
    else if (new_size > m_capacity)
    {
        // Allocate new memory and copy existing elements
        m_capacity = new_size;
        uint8_t* new_ptr = new uint8_t[m_capacity]{};
        for (int i = 0; i < m_size; ++i)
        {
            new_ptr[i] = m_ptr[i];
        }

        // Deallocate old memory and update the pointer
        delete[] m_ptr;
        m_ptr = new_ptr;
        new_ptr = nullptr;
    }
    else
    {
        // Update the size if no reallocation is needed
        m_size = new_size;
    }
}

// Reduce the capacity to fit the actual size
void Vector<bool>::shrink_to_fit()
{
    // Calculate the wanted size in bytes
    size_t wanted_size = m_size / BYTE + static_cast<bool>(m_size % BYTE);

    // Check if shrinking is necessary
    if (wanted_size < m_capacity)
    {
        m_capacity = wanted_size;

        // Allocate new memory and copy existing elements
        uint8_t* new_ptr = new uint8_t[m_capacity];
        for (int i = 0; i < wanted_size; ++i)
        {
            new_ptr[i] = m_ptr[i];
        }

        // Deallocate old memory and update the pointer
        delete[] m_ptr;
        m_ptr = new_ptr;
        new_ptr = nullptr;
    }
}

// Add an element to the end of the vector
void Vector<bool>::push_back(bool val)
{
    // Check if the vector is close to its maximum size
    if (m_size > m_max_size - 10)
    {
        std::cerr << "m_size > m_max_size - 10 in push_back:\n";
        exit(-1);
    }

    // Check if reallocation is needed
    if (m_size / BYTE == m_capacity && m_size % BYTE == 0)
    {
        resize(m_capacity + 2);
    }

    // Set the new element at the end of the vector
    (*this)[m_size] = val;
    ++m_size;
}

// Add an element to the front of the vector
void Vector<bool>::push_front(bool val)
{
    // Check if the vector is close to its maximum size
    if (m_size > m_max_size - 10)
    {
        std::cerr << "m_size > m_max_size - 10 in push_back:\n";
        exit(-1);
    }

    // Check if reallocation is needed
    if (m_size / BYTE == m_capacity && m_size % BYTE == 0)
    {
        resize(m_capacity + 2);
    }
    
    // moving back each element by one
    for (int i = m_size; i > 0; --i)
    {
    	(*this)[i] = (*this)[i - 1];
    }
    
    // Set the new element at the front of the vector and increment the m_size
    (*this)[0] = val;
    ++m_size;
}

// Remove the last element from the vector
void Vector<bool>::pop_back()
{
    // Check if the vector is empty
    if (m_size == 0)
    {
        std::cerr << "Size is 0 for pop:\n";
        exit(-1);
    }

    // Decrease the size to remove the last element
    --m_size;
}

// Remove the last element from the vector
void Vector<bool>::pop_front()
{
    // Check if the vector is empty
    if (m_size == 0)
    {
        std::cerr << "Size is 0 for pop:\n";
        exit(-1);
    }

    // moving front each element by one
    for (int i = 1; i < m_size; ++i)
    {
    	(*this)[i - 1] = (*this)[i];
    }

    // Decrease the size to remove the last element
    --m_size;
}

// Swap contents with another vector
void Vector<bool>::swap(Vector<bool>& other)
{
    // Swap size, capacity, and pointer
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_ptr, other.m_ptr);
}

// Return the current size of the vector
size_t Vector<bool>::size() const
{
    return m_size;
}

// Return the current capacity of the vector
size_t Vector<bool>::capacity() const
{
    return m_capacity;
}

// Return the maximum size the vector can reach
const size_t Vector<bool>::max_size() const
{
    return m_max_size;
}

// Clear all elements in the vector
void Vector<bool>::clear()
{
    // Set all bytes to zero and reset the size
    int size = m_size / BYTE + static_cast<bool>(m_size % BYTE);
    for (int i = 0; i < size; ++i)
    {
        m_ptr[i] = 0;
    }
    m_size = 0;
}

// Check if the vector is empty
bool Vector<bool>::empty() const
{
    return m_size == 0;
}
