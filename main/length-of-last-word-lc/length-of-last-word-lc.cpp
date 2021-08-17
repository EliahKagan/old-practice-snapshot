class Solution {
public:
    static int lengthOfLastWord(const string& s) noexcept;
};

int Solution::lengthOfLastWord(const string& s) noexcept
{
    const auto j = s.find_last_not_of(' ');
    if (j == string::npos) return 0;
    
    const auto i = s.find_last_of(' ', j);
    return static_cast<int>(i == string::npos ? j + 1 : j - i);
}
