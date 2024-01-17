#ifndef LINKED_LIST_H
	#define LINKED_LIST_H
	#include <initializer_list>
    #include <iostream>
		
    template <typename T>
    class LinkedList {	
    public:
        class Node
    	{
            public:
                T m_val;
                Node* m_next;
    
    		    Node(T val = 0); 
        };
    
        class Iterator {
            private:
            	Node* ptr;
            
            public:
            	Iterator();
            	Iterator(Node*);
            
            	Iterator& operator=(const Iterator&);
            	Iterator operator++();
            	Iterator operator++(int);
            				
            	T& operator*() const;
            	Node* operator->() const;
            	bool operator==(const Iterator&) const;
            	bool operator!=(const Iterator&) const;
        };
    
        Iterator begin() const;
        Iterator end() const;
    
    	LinkedList();
    	LinkedList(T);
    	LinkedList(std::initializer_list<T>);	
    	LinkedList(const LinkedList<T>&) noexcept;
    	LinkedList(LinkedList<T>&&) noexcept;
    	~LinkedList();
    
        std::ostream& operator<<(std::ostream&) const;
        
    	LinkedList& operator=(std::initializer_list<T>);
    	LinkedList& operator=(const LinkedList<T>&) noexcept;
    	LinkedList& operator=(LinkedList<T>&&) noexcept;
    
        void push_front(T);
    	void push_back(T);
        void pop_front();
        void pop_back();
    
        size_t size() const;
        bool empty() const;
    
        void clear();
    
        void resize(size_t);
        void reverse();
        void swap(LinkedList<T>&);
    
        void insert(size_t, T);
        void insert(Iterator, T);
    
        void erase(size_t);
        void erase(Iterator);
    
    	void sort(); // bubble sort
    
    private:
        void free();
    
    	Node* head;
    };
	#include "linked_list.hpp"
#endif
