/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
string printOrder(string dict[], int N, int k)
{
    constexpr auto alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    bool table[k][k] {}; // using nonstandard GNU VLA extension
    
    const auto istop = N - 1;
    for (auto i = 0; i != istop; ++i) {
        for (auto j = i + 1; j != N; ++j) {
            const auto hstop = min(dict[i].size(), dict[j].size());
            for (string::size_type h {}; h != hstop; ++h) {
                if (dict[i][h] != dict[j][h]) {
                    table[dict[i][h] - 'a'][dict[j][h] - 'a'] = true;
                    break;
                }
            }
        }
    }
    
    string ret (alphabet, k);
    
    sort(begin(ret), end(ret), [&table](const char x, const char y) {
        return table[x - 'a'][y - 'a'];
    });
    
    return ret;
}
