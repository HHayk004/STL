#ifndef PAIR_H
    #define PAIR_H

    #include <utility>

    template <typename T, typename U>
    struct Pair
    {
        T first;
        U second;

        Pair();
        Pair(T val1, U val2);
        Pair(const Pair& other) noexcept;
        Pair(Pair&& other) noexcept;

        Pair& operator=(const Pair& other) noexcept;
        Pair& operator=(Pair&& other) noexcept;

        ~Pair() = default;
    };

    #include "pair.hpp"

#endif
