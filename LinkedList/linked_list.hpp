#ifndef LINKED_LIST_HPP
	#define LINKED_LIST_HPP

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const LinkedList<T>& other)
    {
        return other.operator<<(os);
    }

    template <typename T>
    LinkedList<T>::LinkedList()
    {
    	head = nullptr;
    }
    
    template <typename T>
    LinkedList<T>::LinkedList(T val)
    {
    	head = new Node(val);
    }
    
    template <typename T>
    LinkedList<T>::LinkedList(std::initializer_list<T> list)
    {
    	head = nullptr;
        for (auto it = std::rbegin(list); it != std::rend(list); ++it)
    	{
    		push_front(*it);
    	}
    }
    
    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList& other) noexcept
    {
    	head = nullptr;
    	Node* node = other.head;
    	while (node)
    	{
    		push_back(node->m_val);
    		node = node->m_next;
    	}
    }
    
    template <typename T>
    LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    {
    	head = std::move(other.head);
    	other.head = nullptr;
    }
    
    template <typename T>
    LinkedList<T>::~LinkedList()
    {
        free();	
    }
    
    template <typename T>
    std::ostream& LinkedList<T>::operator<<(std::ostream& os) const
    {
        Node* tmp = head;
        while (tmp)
        {
            std::cout << tmp->m_val << ' ';
            tmp = tmp->m_next;
        }
    
        return os;
    }
    
    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(std::initializer_list<T> list)
    {
    	free();
    	for (auto it = std::rbegin(list); it != std::rend(list); ++it)
    	{
    		push_front(*it);
    	}
    
    	return *this;
    }
    
    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) noexcept
    {
    	if (this != &other)
    	{
    		free();
    		Node* node = other.head;
    		while (node)
    		{
    			push_back(node->m_val);
    			node = node->m_next;
    		}
    	}
    
    	return *this;
    }
    
    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept
    {
        if (this != &this)
        {
    	    free();			
    
    	    head = std::move(other.head);
    	    other.head = nullptr;
        }

    	return *this;
    }
    
    template <typename T>
    void LinkedList<T>::push_front(T val)
    {
        if (!head)
        {
            head = new Node(val);
        }
    
        else
        {
            Node* tmp = head;
            head = new Node(val);
            head->m_next = tmp;
        }
    }
    
    template <typename T>
    void LinkedList<T>::push_back(T val)
    {
    	if (!head)
    	{
    		head = new Node(val);
    	}
    
    	else
    	{
    		Node* tmp = head;
    		while (tmp->m_next)
    		{
    			tmp = tmp->m_next;
    		}
    		tmp->m_next = new Node(val);
    	}
    }
    
    template <typename T>
    void LinkedList<T>::pop_front()
    {
        if (!head)
        {
            std::cerr << "Empty list for pop_front:\n";
            exit(-1);
        }
    
        else
        {
            Node* tmp = head;
            head = head->m_next;
            delete tmp;
            tmp = nullptr;
        }
    }
    
    template <typename T>
    void LinkedList<T>::pop_back()
    {
        if (!head)
        {
            std::cerr << "Empty list fot pop_back:\n";
            exit(-1);
        }
    
        else if (!(head->m_next))
        {
            delete head;
            head = nullptr;
        }
    
        else
        {
            Node* tmp = head;
            while (tmp->m_next->m_next)
            {
                tmp = tmp->m_next;
            }
    
            delete tmp->m_next;
            tmp->m_next = nullptr;
        }
    }
    
    template <typename T>
    size_t LinkedList<T>::size() const
    {
        size_t size = 0;
        Node* tmp = head;
    
        while (tmp)
        {
            tmp = tmp->m_next;
            ++size;
        }
    
        return size;
    }
    
    template <typename T>
    bool LinkedList<T>::empty() const
    {
        return head;   
    }
    
    template <typename T>
    void LinkedList<T>::clear()
    {
        free();
    }
    
    template <typename T>
    void LinkedList<T>::resize(size_t new_size)
    {
        if (!head)
        {
            for (int i = 0; i < new_size; ++i)
            {
                push_back(0);
            }
            return;
        }
    
        if (new_size == 0)
        {
            free();
            return;
        }
    
        Node* curr = head;            
        
        size_t count = 1; 
        while (curr->m_next && count < new_size)
        {
            curr = curr->m_next;
            ++count;
        }
    
        if (!(curr->m_next))
        {
            while (count < new_size)
            {
                curr->m_next = new Node();
                curr = curr->m_next;
                ++count;
            }
        }
    
        else
        {
            Node* tmp = curr;
            curr = curr->m_next;
            tmp->m_next = nullptr;
            while (curr)
            {
                tmp = curr;
                curr = curr->m_next;
                delete tmp;
            }
        }
    }
    
    template <typename T>
    void LinkedList<T>::reverse()
    {
        if (head && head->m_next)
        {
            Node* prev = nullptr;
            Node* curr = head;
            Node* tmp = nullptr;
            while (curr)
            {
                tmp = curr->m_next;
                curr->m_next = prev;
                prev = curr;
                curr = tmp;
            }
    
            head = prev;
        }
    }
    
    template <typename T>
    void LinkedList<T>::swap(LinkedList<T>& other)
    {
        std::swap(head, other.head);
    }
    
    template <typename T>
    void LinkedList<T>::insert(size_t pos, T val)
    {
        if (pos == 0)
        {
            push_front(val);
            return; 
        }
    
        size_t count = 0;
        Node* prev = nullptr;
        Node* curr = head;
        while (count < pos)
        {
            prev = curr;
            curr = curr->m_next;
            ++count;
        }
    
        prev->m_next = new Node(val);
        prev->m_next->m_next = curr;
    }
    
    template <typename T>
    void LinkedList<T>::insert(Iterator it, T val)
    {
        if (it == begin())
        {
            push_front(val);
            return; 
        }
    
        Iterator tmp_it = begin();
        Node* prev = nullptr;
        Node* curr = head;
        while (tmp_it != it)
        {
            prev = curr;
            curr = curr->m_next;
            ++tmp_it;
        }
    
        prev->m_next = new Node(val);
        prev->m_next->m_next = curr;
    }
    
    template <typename T>
    void LinkedList<T>::erase(size_t pos)
    {
        if (pos == 0)
        {
            pop_front();
            return;
        }
    
        size_t count = 0;
        Node* prev = nullptr;
        Node* curr = head;
        while (count < pos)
        {
            prev = curr;
            curr = curr->m_next;
            ++count;
        } 
    
        Node* next = curr->m_next;
        delete curr;
        prev->m_next = next;
    }
    
    template <typename T>
    void LinkedList<T>::erase(Iterator it)
    {
        if (it == begin())
        {
            pop_front();
            return;
        }
    
        Iterator tmp_it = begin();
        Node* prev = nullptr;
        Node* curr = head;
        while (tmp_it != it)
        {
            prev = curr;
            curr = curr->m_next;
            ++tmp_it;
        } 
    
        Node* next = curr->m_next;
        delete curr;
        prev->m_next = next;
    }
    
    
    template <typename T>
    void LinkedList<T>::sort()
    {
    	if (head)
    	{	
    		Node* end = nullptr;
    		while (head != end)
    		{
    			Node* prev = nullptr;
    			Node* curr = head;
    			Node* next = curr->m_next;
    			while (next != end)
    			{
    				if (curr->m_val > next->m_val)
    				{
    					curr->m_next = next->m_next;
    					next->m_next = curr;
    
    					if (prev)
    					{
    						prev->m_next = next;
    					}
    
    					else
    					{
    						head = next;
    					}
    					
    					std::swap(curr, next);			
    				}
    
    				prev = curr;
    				curr = next;
    				next = next->m_next;
    			}
    			end = curr;
    		}
    	}
    }
    
    template <typename T>
    void LinkedList<T>::free()
    {
    	Node* tmp = head;
    	while (tmp)
    	{
    		Node* tmp_copy = tmp;
    		tmp = tmp->m_next;
            delete tmp_copy;
        }
    
        head = nullptr;
    }
    
    template <typename T>
    LinkedList<T>::Node::Node(T val)
    {
    	m_val = val;
    	m_next = nullptr;
    }
    
    template <typename T>
    LinkedList<T>::Iterator::Iterator() : ptr(nullptr){}
    
    template <typename T>
    LinkedList<T>::Iterator::Iterator(Node* ptr1) : ptr(ptr1){}
    
    template <typename T>
    typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator=(const LinkedList<T>::Iterator& other)
    {
        ptr = other.ptr;
        return *this;
    }
    
    template <typename T>
    typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++()
    {
        if (ptr == nullptr)
        {
            std::cerr << "Error with iterator ++";
        }
    
        ptr = ptr->m_next;
        return *this;
    }
    
    template <typename T>
    typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
    {
        Iterator tmp = *this;
        ptr = ptr->m_next;
        return tmp;
    }
    
    template <typename T>
    bool LinkedList<T>::Iterator::operator==(const LinkedList<T>::Iterator& other) const
    {
        return this->ptr == other.ptr;
    }
    
    template <typename T>
    bool LinkedList<T>::Iterator::operator!=(const LinkedList<T>::Iterator& other) const
    {
        return this->ptr != other.ptr;
    }
    
    template <typename T>
    typename LinkedList<T>::Iterator LinkedList<T>::begin() const
    {
        Iterator it(head);
        return it;
    }
    
    template <typename T>
    typename LinkedList<T>::Iterator LinkedList<T>::end() const
    {
        Iterator it(nullptr);
        return it;
    }
    
    template <typename T>
    T& LinkedList<T>::Iterator::operator*() const
    {
       return ptr->m_val;
    }
    
    template <typename T>
    typename LinkedList<T>::Node* LinkedList<T>::Iterator::operator->() const
    {
       return ptr;
    }
    
#endif
