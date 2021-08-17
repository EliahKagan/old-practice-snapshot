// heaps-algorithm.cxx - Heap's algorithm for generating permutations

#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace {
    template<typename T>
    using Index = typename std::vector<T>::size_type;

    // Generates permutations by Heap's algorithm.
    template<typename TElement, class TEmitter>
    void generate_permutations(std::vector<TElement>& elements,
                               const Index<TElement> size,
                               const TEmitter& emitter)
    {
        if (size == 1u) {
            emitter(elements);
            return;
        }

        const auto back_index = size - 1u;

        for (Index<TElement> i {0u}; i < back_index; ++i) {
            generate_permutations(elements, back_index, emitter);
            std::swap(elements[size % 2u == 0u ? i : 0u], elements[back_index]);
        }

        generate_permutations(elements, back_index, emitter);
    }

    template<typename T>
    void print_elements(const std::vector<T>& v)
    {
        auto sep = "";

        for (const auto x : v) {
            std::cout << sep << x;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main() // unit test for generate_permutations()
{
    std::vector<int> a (3u);
    std::iota(std::begin(a), std::end(a), 0);
    generate_permutations(a, a.size(), print_elements<int>);
    
    std::cout << '\n';

    std::vector<char> chars {'A', 'B', 'C'};
    generate_permutations(chars, chars.size(), print_elements<char>);

    std::cout << '\n';

    std::vector<char> degen_chars {'A', 'B', 'B'};
    generate_permutations(degen_chars, degen_chars.size(), print_elements<char>);
}
