/* The function should return position where the target string 
   matches the string str
Your are required to complete this method */
int strstr(string text, string pattern)
{
    constexpr auto not_found = -1;
    
    const auto text_len = text.size(), pattern_len = pattern.size();
    
    if (text_len < pattern_len) return not_found;
    const auto imax = text_len - pattern_len;
    
    for (string::size_type i {0u}; i <= imax; ++i) {
        string::size_type j {0u};
        while (j != pattern_len && text[i + j] == pattern[j]) ++j;
        if (j == pattern_len) return i;
    }
    
    return not_found;
}
