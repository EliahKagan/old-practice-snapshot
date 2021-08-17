class Solution {
public:
    static int largestComponentSize(const vector<int>& a) noexcept;
};

namespace {
    inline int square_root(const int n) noexcept
    {
        return static_cast<int>(sqrt(n));
    }
    
    basic_string<bool> make_sieve(const int bound) noexcept
    {
        basic_string<bool> known_composite (bound + 1, false);
        
        const auto imax = square_root(bound);
        for (auto i = 3; i <= imax; i += 2) {
            if (known_composite[i]) continue;
            
            const auto jstep = i * 2;
            for (auto j = i * i; j <= bound; j += jstep)
                known_composite[j] = true;
        }
        
        return known_composite;
    }
    
    vector<int> compute_primes(const int bound) noexcept
    {
        const auto known_composite = make_sieve(bound);
        
        vector<int> primes;
        primes.push_back(2);
        
        for (auto i = 3; i <= bound; i += 2)
            if (!known_composite[i]) primes.push_back(i);
        
        return primes;
    }
    
    vector<int> inverse(const vector<int>& values, const int bound) noexcept;
    {
        static constexpr auto npos = -1; // to make debugging less horrible
        
        vector<int> ret (bound + 1, npos);
        for (auto i = 0; i != values.size(); ++i) ret[values[i]] = i;
        return ret;
    }
    
    constexpr auto element_bound = 100'000;
    const auto prime_bound = square_root(element_bound);
    const auto primes = compute_primes(prime_bound);
    const auto indices = inverse(primes, prime_bound);
    
    class DisjointSets {
    public:
        // Performs makeset operations for elements 0, ..., element_count - 1.
        explicit DisjointSets(int element_count) noexcept;
        
        // Performs union by size with full path compression.
        void unite(int i, int j) noexcept;
        
        // Finds the size of the largest component.
        
    private:
        // Finds the representative of the set that contains an element.
        int find_set(int i) noexcept;
        
        vector<int> elems_;
    };
    
    DisjointSets::DisjointSets(const int element_count) noexcept
        : elems_(element_count, -1) // representatives hold negative size
    {
    }
}

int largestComponentSize(const vector<int>& a) noexcept
{
    
}
