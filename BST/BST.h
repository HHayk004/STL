#ifndef BST_H
    #define BST_H

    #include <iostream> // including for cout
    #include <initializer_list> // for initializer list constructor
    #include <queue> // for implement some functions
    #include <vector> // for implement some functions

    template <typename T>
    class BST {
        private:
            struct Node { // our node class
                public:
                    T val; // node's value
                    Node* left; // node's left pointer
                    Node* right; // node's right pointer

                    Node(T& val = 0); // parametr constuctor
                    ~Node(); // destructor
            };

        private:
            Node* m_root; // beginning of our root
            
            void drop(Node* root); // tree deleter

            void copyImpl(Node* root1, Node* root2); // implemetation of copy

            void inOrderImpl(Node* root) const; // implementation of inOrder printing
            void preOrderImpl(Node* root) const; // implementation of preOrder printing
            void postOrderImpl(Node* root) const; // implementation of postOrder printing

            size_t sizeImpl(Node* root) const; // implementation of size
            size_t heightImpl(Node* root) const; // implementation of height
            
            bool is_valid_bstImpl(Node* root) const; // implementation of is_valid

			void range_queryImpl(Node* root, const T& start, const T& end, std::vector<T>& vec) const;	// implementation of range_query

			T kth_smallestImpl(Node* root, int k, int& index) const; // implementation of kth_smallest
			T kth_largestImpl(Node* root, int k, int& index) const; // implementation of kth_largest

        public:
            BST(); // standart default constructor
            BST(std::initializer_list<T> list); // initializer list constructor
            
            BST(const BST<T>& tree) noexcept; // copy constructor
            BST(BST<T>&& tree) noexcept; // move constructor

            void copy(const BST<T>& tree); // deep copy function

            ~BST(); // destructor
            
            void insert(T value); // for insert element 
            void remove(T value); // for remove element (without destroy the BST structure)

            void clear(); // for clear the tree

            void update(const T& value, const T& new_value); // for changing the value

            bool search(const T& value) const; // for searching the value
            bool contains(const T& value) const; // same as search

            void inOrder() const;   // for printing tree in this order: left, root, right
            void preOrder() const;  // for printing tree in this order: root, left, right
            void postOrder() const; // for printing tree in this order: left, right, root
            void level_order() const; // for printing tree in level order
			void print_tree() const; // for printing tree in normal style for users

            Node* find_min() const; // for finding node with min value
            Node* find_max() const; // for finding node with max value

            Node* successor(T value) const; // the smallest bigger node
            Node* predecessor(T value) const; // the biggest smaller node

            size_t size() const; // returning elements count
            size_t height() const; // returning max height of tree

            bool is_valid_bst() const; // checking if tree is valid
    
            std::vector<T> serialize() const; // inorder vector

			std::vector<T> range_query(const T& start, const T& end) const;

			T kth_smallest(int k) const; // retruning the kth smallest node
			T kth_largest(int k) const; // returning the kth biggest node

			void print_node_val(Node* root) const; // my function for tests
    };

    #include "BST.hpp" // including the implementation
#endif
