#ifndef VECTOR_PROTO_H
    #define VECTOR_PROTO_H

    #include <iostream>
	#include <initializer_list>
    #include <utility>
	#include <limits>

    template <typename T>
    class Vector 
    {
        private: // private members of our vector
            T* m_ptr; 
            size_t m_size;
		    const size_t m_max_size = std::numeric_limits<size_t>::max() / sizeof(T); // max_size of size
            size_t m_capacity;
        
        public:
		    Vector(); // 5 constructors of vector
		    Vector(size_t, T);
		    Vector(std::initializer_list<T>);
		    Vector(const Vector&) noexcept;
            Vector(Vector&&) noexcept;

		    ~Vector(); // destructor
 
			class Iterator { // random access iterator subclass
				private:
					T* ptr; // iterator is represented as pointer
				
				public:
					Iterator(); // 2 constructors
					Iterator(T*);
				
					Iterator& operator=(const Iterator&); // operators as in random access iterator
					Iterator& operator++(); // ++it
					Iterator operator++(int); // it++
					Iterator operator+(size_t);
					Iterator operator+=(size_t);
					Iterator operator-(size_t);
                    size_t operator-(Iterator);
					Iterator operator-=(size_t);
					Iterator& operator--(); // --it
					Iterator operator--(int); // it--

					T& operator[](int) const; 
					T& operator*() const;
					T* operator->() const;
					
					bool operator<(const Iterator&) const;
					bool operator<=(const Iterator&) const;
					
					bool operator>(const Iterator&) const;
					bool operator>=(const Iterator&) const;
					
					bool operator==(const Iterator&) const;
					bool operator!=(const Iterator&) const;
			};

			Iterator begin() const; // 2 functions that return iterator 
			Iterator end() const;

            T& operator[](const size_t) const;

            Vector& operator=(std::initializer_list<T>); // assignment operator 3 overloadings
            Vector& operator=(const Vector&); 
            Vector& operator=(Vector&&);

            std::ostream& operator<<(std::ostream&) const; // for printint whole vector by << operator

            T* data() const; // return m_ptr value
            T& at(size_t) const; // same as subsctipt operator
    
            T& back() const; // reference to first element in vector
            T& front() const; // reference to last element in vector

            void shrink_to_fit(); // if capacity > size, copying to smaller memory, then capacity = size
        
            void reserve(size_t); // for increasing of capacity
            void resize(size_t); // changing the size;
            bool empty() const; // checks if vector is empty
        
            void push_back(T); // adding element from back
            void push_front(T); // adding element from front
            void pop_back(); // deleting element from back
            void pop_front(); // deleting element from front
        
            void insert(Iterator it, T); // for element insert;
            void insert(Iterator, std::initializer_list<T>);
            void erase(Iterator);
            void erase(Iterator, Iterator);

            void swap(Vector&); // swaping 2 vectors

            size_t size() const; // returns m_size value
            const size_t max_size() const; // returns m_max_size value
            size_t capacity() const; // returns m_capacity value

            void clear(); // clearing the whole vector
    };

    #include "vector_bool.h" // including bool vector specialization interface

    #include "vector_T.hpp" // including template vector implementation
    #include "vector_bool.hpp" // including bool vector specializetion implementation
#endif
