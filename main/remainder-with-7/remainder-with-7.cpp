static int parseMod(const string value, const int mod)
{
    constexpr auto base = 10;
    
    int acc = 0, place = 1;
    for (auto p = value.crbegin(); p != value.crend(); ++p) {
        acc = (acc + (*p - '0') * place) % mod;
        place = (place * base) % mod;
    }
    
    return acc;
}

/*You are required to complete this method */
int remainderWith7(string n)
{
    return parseMod(n, 7);
}

