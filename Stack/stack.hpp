#ifndef STACK_IMPL_H
#define STACK_IMPL_H

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& other)
{
	return other.operator<<(os);	
}

template <typename T>
void Stack<T>::realloc(size_t new_size)
{
	m_capacity = new_size;
	if (m_ptr == nullptr)
	{
		m_ptr = new T [m_capacity];
	}

	else
	{
		T* new_ptr = new T [m_capacity];
		for (int i = 0; i < m_size; ++i)
		{
			new_ptr[i] = m_ptr[i];
		}

		delete[] m_ptr;
		m_ptr = new_ptr;
		new_ptr = nullptr; 
	}
}

template <typename T>
Stack<T>::Stack()
{
	m_size = 0;
	m_capacity = 0;
	m_ptr = nullptr;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> list)
{
	m_size = list.size();
	m_capacity = m_size + 10;
	m_ptr = new T [m_capacity];
	
    int index = 0;
	for (auto& elem : list)
	{
		m_ptr[index] = elem;
		++index;
	}
}

template <typename T>
Stack<T>::Stack(const Stack<T>& obj) noexcept
{
	m_size = obj.m_size;
	m_capacity = obj.m_capacity;
	m_ptr = new T [m_capacity]{0};
	
    for (int i = 0; i < m_size; ++i)
	{
		m_ptr[i] = obj.m_ptr[i];
	}
}

template <typename T>
Stack<T>::Stack(Stack<T>&& obj) noexcept
{
	m_size = std::move(obj.m_size);
	m_capacity = std::move(obj.m_capacity);
	m_ptr = std::move(obj.m_ptr);

	obj.m_size = 0;
	obj.m_capacity = 0;
	obj.m_ptr = nullptr;
}

template <typename T>
Stack<T>::~Stack()
{
	m_size = 0;
	m_capacity = 0;
	delete[] m_ptr;
	m_ptr = nullptr;
}

template <typename T>
std::ostream& Stack<T>::operator<<(std::ostream& os) const
{
	for (int i = 0; i < m_size; ++i)
	{
		std::cout << m_ptr[i] << ' ';
	}

	return os;	
}

template <typename T>
Stack<T>& Stack<T>::operator=(std::initializer_list<T> list)
{
	m_size = list.size();

	if (m_size > m_capacity)
	{
		realloc(m_size);
	}

	int index = 0;
	for (auto& elem : list)
	{
		m_ptr[index] = elem;
		++index;
	}

	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) noexcept
{
	if (this == &other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		delete[] m_ptr;
		m_ptr = new T [m_capacity];

		for (int i = 0; i < m_size; ++i)
		{
			m_ptr[i] = other.m_ptr[i];
		}
	}

	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
	m_size = std::move(other.m_size);
	m_capacity = std::move(other.m_capacity);
	m_ptr = std::move(other.m_ptr);

	other.m_size = 0;
	other.m_capacity = 0;
	other.m_ptr = nullptr;

	return *this;
}

template <typename T>
void Stack<T>::push(T val)
{
	if (m_size == m_capacity)
	{
		realloc(m_capacity + 10);
	}

	m_ptr[m_size] = val;
	++m_size;
}

template <typename T>
void Stack<T>::pop()
{
	if (!m_size)
	{
		std::cerr << "Wrong size for pop:\n";
		exit(-1);
	}
	--m_size;
}

template <typename T>
T Stack<T>::top()
{
	return m_ptr[m_size - 1];
} 

template <typename T>
bool Stack<T>::empty()
{
	return !m_size;
} 

#endif // STACK_IMPL_H
