class Solution {
public:
    static int countPrimes(int n);
};

int Solution::countPrimes(const int n)
{
    vector<bool> sieve(max(n, 2), true);
    sieve[0] = sieve[1] = false;

    for (auto k = 4; k < n; k += 2) sieve[k] = false;

    for (auto i = 3; i * i < n; i += 2)
        for (auto j = i * i; j < n; j += i * 2) sieve[j] = false;

    return accumulate(cbegin(sieve), cend(sieve), 0);
}
