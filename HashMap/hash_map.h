#ifndef HASH_MAP_H
#define HASH_MAP_H
    
    #include <utility>
    #include <cmath>
    #include <vector>
    #include <list>

    template <typename T, typename U>
    class HashMap {
        private:
            size_t nextSize() const;

            std::vector<size_t> m_prime;
            std::vector<std::pair<size_t, std::list< std::pair<T, U> > > > m_vec; // first element is size of list

        private:
            size_t hash(T key, size_t size) const;

        public:
            HashMap();
            ~HashMap() = default;

            void insert(std::pair<T, U>);
            void erase(T key);

            void rehash();

            U& get(T key);

            void clear();

            size_t size() const;
            
            bool empty() const;
    
            bool containsKey(T key) const;
            bool containsValue(U val) const;

            std::vector<T> keys() const;
            std::vector<U> values() const;
            std::vector<std::pair<T, U> > pairs() const;
    };    

    template <typename U>
    class HashMap<std::string, U> {
        private:
            size_t nextSize() const;

            std::vector<size_t> m_prime;
            std::vector<std::pair<size_t, std::list< std::pair<std::string, U> > > > m_vec; // first element is size of list

        private:
            size_t hash(std::string key, size_t size) const;

        public:
            HashMap();
            ~HashMap() = default;

            void insert(std::pair<std::string, U>);
            void erase(std::string key);

            void rehash();

            U& get(std::string key);

            void clear();

            size_t size() const;
            
            bool empty() const;
    
            bool containsKey(std::string key) const;
            bool containsValue(U val) const;

            std::vector<std::string> keys() const;
            std::vector<U> values() const;
            std::vector<std::pair<std::string, U> > pairs() const;
    };   

    #include "hash_map.hpp"

#endif
