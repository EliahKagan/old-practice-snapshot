/* The below function should return 
the transformed string */
string rearrangeString(string str)
{
    array<int, 26u> frequencies {};
    
    const auto freq = [&frequencies](const char c) -> int& {
        return frequencies[static_cast<size_t>(c - 'a')];
    };
    
    for (const auto c : str) ++freq(c);
    
    assert(!str.empty());
    string ret;
    ret.reserve(str.size());
    
    ret += str.at(0u);
    --freq(str[0u]);
    
    for (string::size_type i {1u}; i != str.size(); ++i) {
        if (ret.back() != str[i] && freq(str[i]) != 0) {
            ret += str[i];
            --freq(str[i]);
            continue;
        }
        
        for (auto c = 'a'; c <= 'z'; ++c) {
            if (ret.back() != c && freq(c) != 0) {
                ret += c;
                --freq(c);
                break;
            }
        }
    }
    
    return ret;
}
