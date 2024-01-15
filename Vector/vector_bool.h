// Specialized class template for Vector with bool elements

template <>
class Vector<bool>
{
private:
    size_t m_size; // Current size of the vector
    size_t m_capacity; // Current capacity of the vector
    const size_t m_max_size = std::numeric_limits<size_t>::max() / sizeof(bool); // Maximum size the vector can reach
    uint8_t* m_ptr; // Pointer to the underlying data

public:
    // Default constructor
    Vector();

    // Constructor with size and default value
    Vector(size_t, bool);

    // Constructor with an initializer list
    Vector(std::initializer_list<bool>);

    // Copy constructor
    Vector(const Vector<bool>&) noexcept;

    // Move constructor
    Vector(Vector<bool>&&) noexcept;

    // Destructor
    ~Vector();

    // Nested class for reference to individual bool elements
    class Reference
    {
    private:
        uint8_t* ptr; // Pointer to the underlying data
        size_t index; // Index of the referenced bool element
        bool flag; // Value of the referenced bool element

    public:
        // Reference constructor with a pointer and index
        Reference(uint8_t*, size_t);

        // Copy constructor for Reference
        Reference(const Reference&) noexcept;

        // Move constructor for Reference
        Reference(Reference&&) noexcept;

        // Conversion operator to bool for Reference
        operator bool() const;

        // Assignment operator for Reference
        Reference& operator=(const Reference& obj);

        // Assignment operator for Reference
        Reference& operator=(bool flag);
    };

    // Subscript operator for Vector<bool> returning a Reference
    Reference operator[](size_t index);

    // Output stream operator overload for Vector<bool>
    std::ostream& operator<<(std::ostream&) const;

    // Assignment operator from initializer list
    Vector& operator=(std::initializer_list<bool>);

    // Copy assignment operator
    Vector& operator=(const Vector&) noexcept;

    // Move assignment operator
    Vector& operator=(Vector&&) noexcept;

    // Return a pointer to the underlying data
    uint8_t* data() const;

    // Access element at the given index with bounds checking
    bool at(size_t) const;

    // Reduce the capacity to fit the actual size
    void shrink_to_fit();

    // Reserve memory for a specified capacity
    void reserve(size_t);

    // Resize the vector to a new size
    void resize(size_t);

    // Check if the vector is empty
    bool empty() const;

    // Add an element to the end of the vector
    void push_back(bool);
    
    // Add an element to the front of the vector
    void push_front(bool);

    // Remove the last element from the vector
    void pop_back();
    
    // Remove the first element from the vector
    void pop_front();

    // Swap contents with another vector
    void swap(Vector<bool>&);

    // Return the current size of the vector
    size_t size() const;

    // Return the maximum size the vector can reach
    const size_t max_size() const;

    // Return the current capacity of the vector
    size_t capacity() const;

    // Clear all elements in the vector
    void clear();
};

