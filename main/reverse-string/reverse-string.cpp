class Solution {
public:
    static string reverseString(const string& s)
    {
        return string(crbegin(s), crend(s));
    }
};
