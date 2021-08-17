// vec.cxx - class and test harness for limited std::vector-like functionality

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>

class Bad_Vec_new_length : public std::bad_array_new_length {
    using std::bad_array_new_length::bad_array_new_length;
};          // FIXME: make what() correct, by changing base class

template<typename T>
class Vec {
public:
    Vec(std::size_t count = 0, const T& value = T());
    Vec(std::initializer_list<T> init);

    Vec(const Vec&) = delete;
    Vec(Vec&&) = delete;
    Vec& operator=(const Vec&) = delete;
    Vec& operator=(Vec&&) = delete;

    const T& operator[](std::ptrdiff_t i) const { return m_data[i]; }
    T& operator[](std::ptrdiff_t i)
        { return const_cast<T&>(const_cast<const Vec<T>&>(*this)[i]); }
    const T& at(std::ptrdiff_t i) const;
    T& at(std::ptrdiff_t i)
        { return const_cast<T&>(const_cast<const Vec<T>*>(this)->at(i)); }
    const T& front() const { return (*this)[0]; }
    T& front()
        { return const_cast<T&>(const_cast<const Vec<T>*>(this)->front()); }
    const T& back() const { return (*this)[m_size - 1]; }
    T& back()
        { return const_cast<T&>(const_cast<const Vec<T>*>(this)->back()); }

    const T* cbegin() const { return m_data.get(); }
    const T* begin() const { return cbegin(); }
    T* begin() { return const_cast<T*>(cbegin()); }
    const T* cend() const { return m_data.get() + m_size; }
    const T* end() const { return cend(); }
    T* end() { return const_cast<T*>(cend()); }

private:
    static inline std::size_t check_count(const std::size_t n);

    std::size_t m_size;
    std::unique_ptr<T[]> m_data;

    std::string at_range_error_msg(std::ptrdiff_t i) const;
};

template<typename T> // public constructor; count = 0, value = T()
Vec<T>::Vec(std::size_t count, const T& value)
    : m_size{check_count(count)}, m_data{new T[count]}
{
    std::fill(begin(), end(), value);
}

template<typename T> // public constructor
Vec<T>::Vec(std::initializer_list<T> init)
    : m_size{init.size()}, m_data{new T[m_size]}
{
    std::move(init.begin(), init.end(), begin());
}

template<typename T> // public method
const T& Vec<T>::at(std::ptrdiff_t i) const
{
    if (static_cast<std::size_t>(i) >= m_size || i < 0)
        throw std::out_of_range{at_range_error_msg(i)};

    return (*this)[i];
}

template<typename T>  // private static method
inline std::size_t Vec<T>::check_count(const std::size_t n)
{
    if (n > static_cast<std::size_t>(
                std::numeric_limits<std::ptrdiff_t>::max()))
        throw Bad_Vec_new_length{};
    
    return n;
}

template<typename T> // private method
std::string Vec<T>::at_range_error_msg(std::ptrdiff_t i) const
{
    assert(static_cast<std::size_t>(i) >= m_size || i < 0);

    std::ostringstream what {"Vec<T>::at: Index ", std::ios_base::ate};
    what << i << " not in range " << 0 << ".." << m_size - 1 << '.';
    return what.str();
}

// Test harness:

class Foo {
public:
    Foo();
    Foo(const Foo&) : Foo{} { } // a Foo has no "content"
    Foo(Foo&&) = delete;
    ~Foo();

    Foo& operator=(const Foo&) { return *this; } // a Foo has no "content"
    Foo& operator=(Foo&&) = delete;

private:
    static thread_local unsigned long count;

    const unsigned long id = count++;
};

Foo::Foo() { std::cout << "Foo " << id << " created.\n"; }
Foo::~Foo() { std::cout << "Foo " << id << " destroyed.\n"; }
thread_local unsigned long Foo::count = 0L;

namespace {
    void test_Vec()
    {
        for (auto k : Vec<int>(10, 2)) std::cout << ' ' << k;
        std::cout << '\t';
        for (auto x : Vec<float>{10.1f, 20.2f, 30.3f}) std::cout << ' ' << x;
        std::cout << "\n\n";

        Vec<Foo> a (5);
    }
}

int main(int, char *argv[])
{
    try { test_Vec(); }
    catch (const std::exception& e) {
        std::cerr << argv[0] << ": error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
