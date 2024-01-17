#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

template <typename T, typename U>
HashMap<T, U>::HashMap()
{
    m_prime = {2, 3};
    m_vec.resize(m_prime.back());
}

template <typename T, typename U>
void HashMap<T, U>::insert(std::pair<T, U> elem)
{
    size_t index = hash(elem.first, m_vec.size());

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == elem.first)
        {
            if (it->second != elem.second)
            {
                it->second = elem.second;
            }

            return;
        }
    }
    
    m_vec[index].second.push_front(elem);
    ++m_vec[index].first;

    if (m_vec[index].first > m_vec.size())
    {
        rehash();
    }
}

template <typename T, typename U>
void HashMap<T, U>::erase(T key)
{
    size_t index = hash(key, m_vec.size());

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == key)
        {
            m_vec[index].second.erase(it);
            break;
        }
    }
}

template <typename T, typename U>
void HashMap<T, U>::rehash()
{
    std::vector<std::pair<size_t, std::list<std::pair<T, U> > > > tmp;
    tmp.resize(nextSize());

    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            size_t index = hash(it->first, tmp.size());

            tmp[index].second.push_front(*it);
            ++tmp[index].first;
        }
    }

    m_vec = std::move(tmp);
}

template <typename T, typename U>
U& HashMap<T, U>::get(T key)
{
    const size_t index = hash(key, m_vec.size());

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == key)
        {
            return it->second;
        }
    }

    std::cerr << "The element doesn't exist!\n";
    exit(1);
}

template <typename T, typename U>
void HashMap<T, U>::clear()
{
    m_vec.clear();
}

template <typename T, typename U>
size_t HashMap<T, U>::nextSize() const
{
    size_t num = m_prime.back() + 2;

    while (true)
    {
        size_t val = std::sqrt(num);

        bool check = true;
        for (int i = 0; i < m_prime.size() && m_prime[i] <= val; ++i)
        {
            if (num % m_prime[i] == 0)
            {
                check = false;
                break;
            }
        }

        if (check)
        {
            break;
        }

        num += 2;
    }

    return num;
}

template <typename T, typename U>
size_t HashMap<T, U>::hash(T key, size_t size) const
{
    return static_cast<size_t>(key) % size; 
}

template <typename T, typename U>
size_t HashMap<T, U>::size() const
{
    size_t result = 0;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        result += m_vec[i].first;
    }

    return result;
}

template <typename T, typename U>
bool HashMap<T, U>::empty() const
{
    for (int i = 0; i < m_vec.size(); ++i)
    {
        if (m_vec[i].first)
        {
            return false;
        }
    }
 
    return true;
}

template <typename T, typename U>
bool HashMap<T, U>::containsKey(T key) const
{
    size_t index = hash(key);

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == key)
        {
            return true;
        }
    }

    return false;
}

template <typename T, typename U>
bool HashMap<T, U>::containsValue(U val) const
{
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            if (it->second == val)
            {
                return true;
            }
        }
    }

    return false;
}

template <typename T, typename U>
std::vector<T> HashMap<T, U>::keys() const
{
    std::vector<T> result;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            result.push_back(it->first);
        }
    }

    return result;
}

template <typename T, typename U>
std::vector<U> HashMap<T, U>::values() const
{
    std::vector<U> result;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            result.push_back(it->second);
        }
    }

    return result;
}

template <typename T, typename U>
std::vector<std::pair<T, U> > HashMap<T, U>::pairs() const
{
    std::vector<std::pair<T, U> > result;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            result.push_back(*it);
        }
    }

    return result;
}

template <typename U>
HashMap<std::string, U>::HashMap()
{
    m_prime = {2, 3};
    m_vec.resize(m_prime.back());
}

template <typename U>
void HashMap<std::string, U>::insert(std::pair<std::string, U> elem)
{
    size_t index = hash(elem.first, m_vec.size());

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == elem.first)
        {
            if (it->second != elem.second)
            {
                it->second = elem.second;
            }

            return;
        }
    }
    
    m_vec[index].second.push_front(elem);
    ++m_vec[index].first;

    if (m_vec[index].first > m_vec.size())
    {
        rehash();
    }
}

template <typename U>
void HashMap<std::string, U>::erase(std::string key)
{
    size_t index = hash(key, m_vec.size());

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == key)
        {
            m_vec[index].second.erase(it);
            break;
        }
    }
}

template <typename U>
void HashMap<std::string, U>::rehash()
{
    std::vector<std::pair<size_t, std::list<std::pair<std::string, U> > > > tmp;
    tmp.resize(nextSize());

    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            size_t index = hash(it->first, tmp.size());

            tmp[index].second.push_front(*it);
            ++tmp[index].first;
        }
    }

    m_vec = std::move(tmp);
}

template <typename U>
U& HashMap<std::string, U>::get(std::string key)
{
    const size_t index = hash(key, m_vec.size());

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == key)
        {
            return it->second;
        }
    }

    std::cerr << "std::stringhe element doesn't exist!\n";
    exit(1);
}

template <typename U>
void HashMap<std::string, U>::clear()
{
    m_vec.clear();
}

template <typename U>
size_t HashMap<std::string, U>::nextSize() const
{
    size_t num = m_prime.back() + 2;

    while (true)
    {
        size_t val = std::sqrt(num);

        bool check = true;
        for (int i = 0; i < m_prime.size() && m_prime[i] <= val; ++i)
        {
            if (num % m_prime[i] == 0)
            {
                check = false;
                break;
            }
        }

        if (check)
        {
            break;
        }

        num += 2;
    }

    return num;
}

template <typename U>
size_t HashMap<std::string, U>::hash(std::string key, size_t size) const
{
    const size_t prime_const = 31; // can be any number

    size_t result = 0;
    for (int i = 0; i < key.size(); ++i)
    {
        result += key[i] * pow(prime_const, i);
    }

    return result % size;
}

template <typename U>
size_t HashMap<std::string, U>::size() const
{
    size_t result = 0;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        result += m_vec[i].first;
    }

    return result;
}

template <typename U>
bool HashMap<std::string, U>::empty() const
{
    for (int i = 0; i < m_vec.size(); ++i)
    {
        if (m_vec[i].first)
        {
            return false;
        }
    }
 
    return true;
}

template <typename U>
bool HashMap<std::string, U>::containsKey(std::string key) const
{
    size_t index = hash(key);

    for (auto it = m_vec[index].second.begin(); it != m_vec[index].second.end(); ++it)
    {
        if (it->first == key)
        {
            return true;
        }
    }

    return false;
}

template <typename U>
bool HashMap<std::string, U>::containsValue(U val) const
{
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            if (it->second == val)
            {
                return true;
            }
        }
    }

    return false;
}

template <typename U>
std::vector<std::string> HashMap<std::string, U>::keys() const
{
    std::vector<std::string> result;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            result.push_back(it->first);
        }
    }

    return result;
}

template <typename U>
std::vector<U> HashMap<std::string, U>::values() const
{
    std::vector<U> result;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            result.push_back(it->second);
        }
    }

    return result;
}

template <typename U>
std::vector<std::pair<std::string, U> > HashMap<std::string, U>::pairs() const
{
    std::vector<std::pair<std::string, U> > result;
    for (int i = 0; i < m_vec.size(); ++i)
    {
        for (auto it = m_vec[i].second.begin(); it != m_vec[i].second.end(); ++it)
        {
            result.push_back(*it);
        }
    }

    return result;
}



#endif
