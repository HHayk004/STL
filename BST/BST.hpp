#ifndef BST_HPP
    #define BST_HPP

    template <typename T>
    BST<T>::BST() : m_root(nullptr) {} // default constructor, that defines m_root to nullptr 

    template <typename T>
    BST<T>::BST(std::initializer_list<T> list) // initializer list constructor
    {
        m_root = nullptr; // defining m_root to nullptr
        for (auto& elem : list) // insert the element of list to tree
        {
            insert(elem); // using insert for initializer list
        }
    }

    template <typename T>
    BST<T>::BST(const BST<T>& tree) noexcept // copy constructor
    {
        if (tree.m_root) // if tree has at least one node, do copy
        {
            m_root = new Node(tree.m_root->val); // allocating memory for m_root
            copyImpl(m_root, tree.m_root); // call copy
        }    
    }

    template <typename T>
    BST<T>::BST(BST<T>&& tree) noexcept // move constructor
    {
        if (this != &tree)
        {
            m_root = std::move(tree.m_root); // moving our tree
            tree.m_root = nullptr; // remove the ownership
        }
    }

    template <typename T>
    void BST<T>::copy(const BST<T>& tree) // copy public method
    {
        if (this != &tree) // checking for self-assignment
        {
            if (m_root) // if there are nodes, delete the memory of tree
            {
                drop(m_root); // clearing before copying
                m_root = nullptr; // removing the dangling pointer
            }

            if (tree.m_root) // if tree isn't empty, make the copy
            {
                m_root = new Node(tree.m_root->val); // initializing the m_root
                copyImpl(m_root, tree.m_root); // call the copy
            }
        }
    }

    template <typename T>
    void BST<T>::copyImpl(Node* root1, Node* root2) // copy impl method
    {
        // recursive compying of tree
        if (root2->left) // check node for left side
        {
            root1->left = new Node(root2->left->val); // allocate memory for left side
            copyImpl(root1->left, root2->left); // call the copy for the left side
        }

        if (root2->right) // check node for right side
        {
            root1->right = new Node(root2->right->val); // allocate memory for right side
            copyImpl(root1->right, root2->right); // call the copy for right side
        }
    }

    template <typename T>
    void BST<T>::drop(Node* root) // destructor helper method
    {
        // recursive deleting of tree
        if (root->left) // check node for left side
        {
            drop(root->left); // call drop for left side
        }
 
        if (root->right) // check node for right side
        {
            drop(root->right); // call drop for right side
        }

        delete root; // delete the memory
        root = nullptr; // assign root to nullptr
    }

    template <typename T>
    BST<T>::~BST() // destructor
    {
        if (m_root) // if there are dynamic memory, call drop method
        {
            drop(m_root); // calling drop for delete the memory
            m_root = nullptr; // remove the dangling pointer
        }
    }

    template <typename T>
    BST<T>& BST<T>::operator=(const BST<T>& tree) noexcept // assignment operator for copy
    {
        if (this != &tree) // checking for self-assignment
        {
            if (m_root) // if there are nodes, delete the memory of tree
            {
                drop(m_root); // clearing before copying
                m_root = nullptr; // removing the dangling pointer
            }

            if (tree.m_root) // if tree isn't empty, make the copy
            {
                m_root = new Node(tree.m_root->val); // initializing the m_root
                copyImpl(m_root, tree.m_root); // call the copy
            }
        }

        return *this; // returning the object
    }

    template <typename T>
    BST<T>& BST<T>::operator=(BST<T>&& tree) noexcept // assignment operator for move
    {
        if (this != &tree) // checking for self-assignment
        {
            if (m_root) // if there are nodes, delete the memory of tree
            {
                drop(m_root); // clearing the memory before move
                m_root = nullptr; // removing the dangling pointer
            }

            if (tree.m_root) // if tree isn't empty
            {
                m_root = std::move(tree.m_root); // move the tree
                tree.m_root = nullptr; // removing dangling pointer
            }
        }

        return *this; // returning the object
    }

    template <typename T>
    BST<T>::Node::Node(T& value) // parameter constructor for node
    {
        if (value >= 0) // if value is valid
        {
            val = value;
            left = nullptr;
            right = nullptr;
        }

        else // otherwise throw exception
        {
            std::cerr << "Invalid value for root:\n";
            exit(-1);
        }
    }

    template <typename T>
    BST<T>::Node::~Node() // destructor for node subclass, it isn't nessesary
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    template <typename T>
    void BST<T>::insert(T value) // element insert method
    {
        // inserting value by rules of BST with iterative method
        if (value < 0) // checking for value validity
        {
            std::cerr << "Invalid value for insert:\n";
            exit(-1);
        }

        if (!m_root) // if it's empty tree 
        {
            m_root = new Node(value); // allocate memory for m_root
            return;
        }

        Node* root = m_root; // otherwise we find where our node should be
        while (root->val != value) // find and put our value in tree
        {
            if (value < root->val) // for left node
            {
                if (!root->left) // if we find the place
                {
                    root->left = new Node(value); // using parameter constructor
                    break; // end of cycle
                }
                root = root->left; // else cintinue searching
            }

            else if (value > root->val) // the same but for right node
            {
                if (!root->right) // if we find the place
                {
                    root->right = new Node(value); // using parameter constructor
                    break; // end of cycle
                }
                root = root->right; // else continue searching
            }
        }
    }
 
    template <typename T>
    void BST<T>::remove(T value) // element remove method
    {
        if (value < 0) // if it's invalid value, return error message
        {
            std::cerr << "Invalid value for remove:\n";
            exit(-1);
        }

        Node* prev = nullptr; // our removing node's previous node
        Node* root = m_root; // creating temprorary node for searching

        while (root && root->val != value) // finding our removing node
        {
            prev = root; // assign prev to root, because the end of cycle it will be the previous node of root
            
            // by value choose the direction 
            if (value < root->val)
            {
                root = root->left;
            }

            else
            {
                root = root->right;
            }
        }

        if (!root) // if it doesn't find, return error message
        {
            std::cerr << "Invalid input for remove:\n";
            exit(-1);
        }

        Node* prev1 = root; // replaced node's previous node
        Node* root1 = root->right; // replaced node

        if (!root1) // if it doesn't have right node
        {
            if (root == m_root) // if we removing the m_root
            {
                m_root = m_root->left; // assign the left node as m_root
            }

            else if (prev->left == root) // if root is left side of prev
            {
                prev->left = root->left; // link the nodes
            }

            else // else root is right side of prev
            {
                prev->right = root->right; // linked nodes
            }
        }

        else
        {
            while (root1->left) // find replaced node 
            {
                prev1 = root1;
                root1 = root1->left;
            }

            prev1->left = nullptr; // linking the root to nullptr

            root1->left = root->left; // assigning root nodes to root1
            root1->right = root->right;

            if (prev->left == root) // if root is left side of prev
            {
                prev->left = root1; // link the nodes
            }

            else // else root is right side of prev
            {
                prev->right = root1; // linked nodes
            }

            if (root == m_root) // if we must delete m_root
            {
                m_root = root1; // assign root1 to m_root
            }
        }

        delete root; //deleting the node
    }

    template <typename T>
    void BST<T>::clear() // same logic as for destructor
    {
        if (m_root) // if it isn't empty, call drop
        {
            drop(m_root); // drop method call
            m_root = nullptr; // remove dangilng pointer
        }
    }

    template <typename T>
    void BST<T>::update(const T& value, const T& new_value) // simple update method
    {
        remove(value); // remove the node
        insert(new_value); // insert the new node
    }
        
    template <typename T>
    bool BST<T>::search(const T& value) const // searching using the rules of bst and with iterative
    {
        if (value < 0) // checking validity of our value
        {
            return false;
        }

        Node* root = m_root; // creating tmp node
        while (root && root->val != value) // searching the node by values
        {
            if (value < root->val)
            {
                root = root->left;
            }

            else
            {
                root = root->right;
            }
        }

        return root; // if root is nullptr - false, else it's true
    }

    template <typename T>
    bool BST<T>::contains(const T& value) const // same as search
    {
        return search(value); // using previous method
    }

    template <typename T>
    void BST<T>::inOrder() const // inOrder printing public method
    {
        inOrderImpl(m_root); // calling the impl method
        std::cout << std::endl; // for clearity output
    }

    template <typename T>
    void BST<T>::inOrderImpl(BST<T>::Node* root) const // inOrder printing implementation
    {
        if (root) // root validity checking
        {
            inOrderImpl(root->left); // call for left side
            std::cout << root->val << ' '; // printing root->val and ' ' for output clearity
            inOrderImpl(root->right); // call for right side
        }
    }

    template <typename T>
    void BST<T>::preOrder() const // preOrder printing public method
    {
        preOrderImpl(m_root); // calling the impl method
        std::cout << std::endl; // for output clearity
    }

    template <typename T>
    void BST<T>::preOrderImpl(BST<T>::Node* root) const // preOrder printing implementation
    {
        if (root) // root validity checking
        {
            std::cout << root->val << ' '; // printing root->val and ' ' for output clearity
            preOrderImpl(root->left); // call for left side 
            preOrderImpl(root->right); // call for right side
        }
    }

    template <typename T>
    void BST<T>::postOrder() const // postOrder printing
    {
        postOrderImpl(m_root); // calling the impl method
        std::cout << std::endl; // for output clearity
    }

    template <typename T>
    void BST<T>::postOrderImpl(BST<T>::Node* root) const // postOrder private method implementation
    {
        if (root) // checking for root validity
        {
            postOrderImpl(root->left); // call for left side
            postOrderImpl(root->right); // call for right side
            std::cout << root->val << ' '; // printing root->val and ' ' for output clearity
        }
    }

    template <typename T>
    void BST<T>::level_order() const // level order method with my queue
    {
        std::queue<Node*> roots; // creating roots queue
        roots.push(m_root); // pushing root to roots

        while (!roots.isEmpty()) // cycle while roots isn't empty
        {
            Node* root = roots.front(); // take first element of roots
            
            // pushing nodes to roots if there are
            if (root->left) 
            {
                roots.push(root->left);
            }

            if (root->right)
            {
                roots.push(root->right);
            }

            std::cout << root->val << ' '; // printing the root's value
            roots.pop(); // removing the root from roots
        }
        std::cout << std::endl; // for output clearity 
    }

	template <typename T>
	void BST<T>::print_tree() const // printing tree (levelOrder + endl + nullptr nodes)
	{
		int count = 0; // current count of nodes
		int n = 1; // level nodes count
		bool check = false; // check for not nullptr nodes
		std::queue<Node*> roots; // same mean as in level order
		if (m_root) // if tree isn't empty, push m_root to roots and initialize count
		{
            std::cout << ":";
			roots.push(m_root);
			count = 1;
		}

		while (count) // cycle while there are valid nodes
		{
			Node* root = roots.front(); // root to roots first value
			if (root) // if root is valid
			{
				check |= (root->left || root->right); // for finding valid node
				roots.push(root->left); // pushing the nodes
				roots.push(root->right);
				std::cout << root->val << ':'; // printing nodes value
			}

			else // printing ' '
			{
				roots.push(nullptr); // for printing tree in appropriate way
				roots.push(nullptr);
				std::cout << " :";
			}

			--count; // decrease the count of nodes
			if (!count) // if count = 0, check if there are any valid nodes that wasn't printed
			{
				if (!check) // if there aren't break from cycle
				{
					break;
				}
				
				check = false; // refresh check value

				std::cout << std::endl << ':'; // for output clearity
				
				count = 2 * n; // nodes count in current level
				n *= 2; // for next count initialization
			}

			roots.pop(); // removing root from roots
		}

        std::cout << std::endl; // for output clearity
	}

    template <typename T>
    typename BST<T>::Node* BST<T>::find_min() const // find the minimum node (the left one)
    {
        if (!m_root) // checking m_root validity
        {
            return nullptr;
        }

        Node* root = m_root; // create tmp root with m_root value 
        while (root->left) // min node is the leftest node
        {
            root = root->left; // go to left
        }

        return root; // return the root;
    }
    
    template <typename T>
    typename BST<T>::Node* BST<T>::find_max() const // find the maximum node (the right one)
    {
        if (!m_root) // checking m_root validity
        {
            return nullptr;
        }

        Node* root = m_root; // create tmp root with m_root validity
        while (root->right) // max node is the rightest node
        {
            root = root->right; // go to right
        }

        return root; // return the root
    }

    template <typename T>
    typename BST<T>::Node* BST<T>::successor(T value) const // finding the smallest node than has bigger value than value
    {
        Node* root = m_root; // create tmp root with m_root
		Node* result = nullptr; // if root doesn't have right node, result will contain the answer
        while (root && root->val != value) // finding the value node and saving bigger nodes
        {
            if (value < root->val)
            {
				if (!result || result->val > root->val)
				{
					result = root;
				}
                root = root->left;
            }

            else
            {
                root = root->right;
            }
        }

        if (!root) // if there isn't node with this value
        {
            return result;
        }

        if (root->right) // if there is root->right, forget about result node
        {
			root = root->right; // go one right, then in cycle go full left
			while (root->left)
			{
				root = root->left;
			}
            
			return root; // return the root
        }

        return result; // return the result
    }

    template <typename T>
    typename BST<T>::Node* BST<T>::predecessor(T value) const // finding the biggest node that has smaller value than value
    {
        // same lagic as in successor but in opposite
		Node* root = m_root;
		Node* result = nullptr;
    	while (root && root->val != value)
        {
            if (value < root->val)
            {
                root = root->left;
            }

            else
            {
				if (!result || result->val < root->val)
				{
					result = root;
				}
                root = root->right;
            }
        }

        if (!root)
        {
            return nullptr;
        }

        if (root->left)
        {
			root = root->left;
			while (root->right)
			{
				root = root->right;
			}
            
			return root;
        }

        return result;

	}

    template <typename T>
    size_t BST<T>::size() const // returning nodes count in tree
    {
        return sizeImpl(m_root); // calling impl fucntion
    }

    template <typename T>
    size_t BST<T>::sizeImpl(Node* root) const // simple using of recursion
    {
        if (!root) // if it isn't valid, return 0
        {
            return 0;
        }

        return 1 + sizeImpl(root->left) + sizeImpl(root->right); // return the right side nodes count + left side nodes count + this node as 1
    }

    template <typename T>
    size_t BST<T>::height() const // returning max height of tree
    {
        return heightImpl(m_root); // calling impl method
    }

    template <typename T>
    size_t BST<T>::heightImpl(Node* root) const // height method implementation with simple using of recursion
    {
        if (!root) // if root isn't valid
        {
            return 0;
        }

        size_t h1 = heightImpl(root->left) + 1; // max height of left side
        size_t h2 = heightImpl(root->right) + 1; // max height of right side

        return (h1 > h2) ? h1 : h2; // returning max of h1 and h2
    }

    template <typename T>
    bool BST<T>::is_valid_bst() const // checking if we do all right with insert and remove
    {
        if (!m_root) // if it's empty tree, it's true
        {
            return true;
        }

        return is_valid_bstImpl(m_root); // calling impl funcion
    }

    template <typename T>
    bool BST<T>::is_valid_bstImpl(BST<T>::Node* root) const // is_valid_bst method implementation using of simple recursion
    {
        return !(root->left && root->val <= root->left->val && !is_valid_bstImpl(root->left)) &&  // for left side, checking for values condition and check same for left side,
                                                                                                  // if it's true, reverse the value for consistency of true
               !(root->right && root->val <= root->right->val && !is_valid_bstImpl(root->right)); // same for right side
    }

    template <typename T>
    std::vector<T> BST<T>::serialize() const // same logic as in level order, but we push nodes in vector and return it
    {
        std::queue<Node*> roots;
        std::vector<T> result;
        roots.push(m_root);

        while (!roots.isEmpty())
        {
            Node* root = roots.front();
            if (root->left)
            {
                roots.push(root->left);
            }

            if (root->right)
            {
                roots.push(root->right);
            }

            result.push_back(root->val);
            roots.pop();
        }
    
        return result;
    }

	template <typename T>
	std::vector<T> BST<T>::range_query(const T& start, const T& end) const // method for pushing node's values to result if it's values in range
	{
		std::vector<T> result; // creating vector for result

		range_queryImpl(m_root, start, end, result); // calling impl method

		return result; // return the result
	}

	template <typename T>
	void BST<T>::range_queryImpl(BST<T>::Node* root, const T& start, const T& end, std::vector<T>& vec) const // range_query method implementation
	{
		if (root) // if it isn't nullptr
		{
			if (root->val > end) // if it's big than the end of range
			{
				range_queryImpl(root->left, start, end, vec); // call for left side
			}
			
			else if (root->val < start) // if it is's small than the start of range
			{
				range_queryImpl(root->right, start, end, vec); // call for right side
			}	
			
			else // if it's in range
			{			
				if (root->val != start) // if it's meaningful to call for left node
				{
					range_queryImpl(root->left, start, end, vec); // call for left side
				}
			
				vec.push_back(root->val); // pushing in inorder logic
				
				if (root->val != end) // if it's meaningful to call for right node
				{
					range_queryImpl(root->right, start, end, vec); // call for right side
				}
			}
		}
	}

	template <typename T>
	T BST<T>::kth_smallest(int k) const // finding kth smallest value
	{
        if (m_root && (k > 0)) // checking m_root and k validity
        {	
            int index = 0; // index for finding kth smallest value
			return kth_smallestImpl(m_root, k, index); // calling impl method
        }

		return -1; // return -1 as error value
	}

	template <typename T>
	T BST<T>::kth_smallestImpl(Node* root, int k, int& index) const // kth_smallest method implementation
	{
        // using inOrder logic and counting with index
        if (root->left) // if root->left is valid
        {
            int tmp = kth_smallestImpl(root->left, k, index); // call for left side
            if (tmp != -1) // if tmp != -1, we find the value
            {
                return tmp; // return the result as tmp
            }
        }

        ++index; // increment the index
    
        if (index == k) // it's base case
        {
            return root->val; // return the result as root->val
        }

        if (root->right) // if root->right is valid
        {
            int tmp = kth_smallestImpl(root->right, k, index); // call for right side
            if (tmp != -1) // same as in top
            {
                return tmp; // return the result as tmp
            }
        }

        return -1; // otherwise, return -1 as incorrect value
    }

	template <typename T>
	T BST<T>::kth_largest(int k) const // findingt the kth largest value
	{
		if (m_root && (k > 0)) // checking m_root validity
        {	
            int index = 0; // index for finding the kth largest value
			return kth_largestImpl(m_root, k, index); // calling impl method
        }

        return -1; // return -1 as error value
	}

	template <typename T>
	T BST<T>::kth_largestImpl(Node* root, int k, int& index) const // kth_largest method implementation
	{
        // inOrder logic as in kth_smallest but opposite
		if (root->right)
        {
            int tmp = kth_largestImpl(root->right, k, index);
            if (tmp != -1)
            {
                return tmp;
            }
        }

        ++index;
    
        if (index == k)
        {
            return root->val;
        }

        if (root->left)
        {
            int tmp = kth_largestImpl(root->left, k, index);
            if (tmp != -1)
            {
                return tmp;
            }
        } 

        return -1;
	}

	template <typename T>
	void BST<T>::print_node_val(Node* root) const // simple method to get print node's value (private for test my functions)
	{
		if (root)
		{
			std::cout << root->val << std::endl;
		}

		else
		{
			std::cout << "nullptr\n";
		}
	}
#endif
