#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {
    basic_string<bool> make_sieve(const int bound) noexcept
    {
        basic_string<bool> known_composite (bound + 1, false);
        
        const auto imax = static_cast<int>(sqrt(bound));
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
}

int main()
{
    ios_base::sync_with_stdio(false);
    
    auto sep = "";
    for (const auto x : compute_primes(100'000)) {
        cout << sep << x;
        sep = " ";
    }

    cout << '\n';
}
