#ifndef PAIR_HPP
    #define PAIR_HPP

    template <typename T, typename U>
    Pair<T, U>::Pair() : first(T()), second(U()) {}

    template <typename T, typename U>
    Pair<T, U>::Pair(T val1, U val2) : first(val1) , second(val2) {}
    
    template <typename T, typename U>
    Pair<T, U>::Pair(const Pair<T, U>& other) noexcept : first(other.first), second(other.second) {}
    
    template <typename T, typename U>
    Pair<T, U>::Pair(Pair<T, U>&& other) noexcept : first(std::move(other.first)) , second(std::move(other.second)) {}
   
    template <typename T, typename U>
    Pair<T, U>& Pair<T, U>::operator=(const Pair<T, U>& other) noexcept
    {
        first = other.first;
        second = other.second;

        return *this;
    }
    
    template <typename T, typename U>
    Pair<T, U>& Pair<T, U>::operator=(Pair<T, U>&& other) noexcept
    {
        first = std::move(other.first);
        second = std::move(other.second);
    
        return *this;
    }
#endif
