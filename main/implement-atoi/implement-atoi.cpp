/*You are required to complete this method */
int atoi(string str)
{
    constexpr auto no_value = -1;
    
    const auto q = str.cend();
    auto p = str.cbegin();
    if (p == q) return no_value;
    
    auto sign = 1;
    
    switch (*p) {
        case '-':   sign = -1;  // fallthrough
        case '+':   ++p;
    }
    
    int acc = 0;
    for (; p != q; ++p) {
        const auto c = *p;
        if (c < '0' || c > '9') return no_value;
        acc = acc * 10 + (c - '0');
    }
    
    return acc * sign;
}
