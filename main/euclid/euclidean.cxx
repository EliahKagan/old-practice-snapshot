#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <type_traits>

// Seq - class template for sequences that can be added and scalar-multiplied
template<typename Index, typename Value, Index start, Index end>
class Seq {
public:
    inline const Value& operator[](Index i) const;
    inline Value& operator[](Index i);

private:
    static const ptrdiff_t s_start = static_cast<ptrdiff_t>(start);
    static const ptrdiff_t s_size = static_cast<ptrdiff_t>(end) - s_start + 1;
    
    static std::string getBoundsError();
    static inline void checkBounds(Index i);
    
    Value m_data[s_size];
};

// Seq - public instance methods:

template<typename Index, typename Value, Index start, Index end>
inline const Value& Seq<Index, Value, start, end>::operator[](Index i) const
{
    checkBounds(i);
    return m_data[static_cast<ptrdiff_t>(i) - s_start];
}

template<typename Index, typename Value, Index start, Index end>
inline Value& Seq<Index, Value, start, end>::operator[](Index i)
{
    return const_cast<Value&>(
        static_cast<const Seq<Index, Value, start, end>&>(*this)[i]);
}

// Seq - private static methods:

template<typename Index, typename Value, Index start, Index end>
std::string Seq<Index, Value, start, end>::getBoundsError()
{
    std::ostringstream what ("Index must be in range ");
    what << start << ".." << end << '.';
    return what.str();
}

template<typename Index, typename Value, Index start, Index end>
inline void Seq<Index, Value, start, end>::checkBounds(Index i)
{
    if (i < start || i > end) throw std::out_of_range(getBoundsError());
}

// Vec3 - class template for Euclidean 3-vectors
template<typename T>
class Vec3 : public Seq<int, T, 1, 3> {
};

// Test harness:

int main()
{
    // Seq test:
    Seq<int, double, 1, 3> v;
    v[1] = 10.1, v[2] = 20.2, v[3] = 30.3;
    for (int i = 1; i <= 3; ++i) std::cout << v[i] << '\n';
    
    std::cout << std::endl;

    // Vec3 test:

    return EXIT_SUCCESS;
}
