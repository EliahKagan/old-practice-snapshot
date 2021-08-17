/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
string printOrder(string dict[], int N, int k)
{
    constexpr auto alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    bool table[26][26] {};
    
    const auto istop = N - 1;
    for (auto i = 0; i != istop; ++i) {
        for (auto j = i + 1; j != N; ++j) {
            const auto hstop = min(dict[i].size(), dict[j].size());
            for (string::size_type h {}; h != hstop; ++h) {
                if (dict[i][h] != dict[j][h]) {
                    std::cout << dict[i][h] << " < " << dict[j][h] << '\n';
                    table[dict[i][h] - 'a'][dict[j][h] - 'a'] = true;
                    break;
                }
            }
        }
    }
    
    for (auto i = 0; i != k; ++i) {
        for (auto j = 0; j != k; ++j) std::cout << ' ' << table[i][j];
        std::cout << '\n';
    }
    
    string ret (alphabet, k);
    
    sort(begin(ret), end(ret), [&table](const char x, const char y) {
        return table[x - 'a'][y - 'a'];
    });
    
    cout << ret << '\n';
    return ret;
}
