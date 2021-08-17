#include <ios>
#include <sstream>
#include <string>

/* The function returns 1 if 
IP string is valid else return 0 
You are required to complete this method */
int isValid(const char *const ip)
{
    constexpr auto sep = '.';

    std::stringstream ss {ip};
    ss.seekp(0, std::ios::end);
    ss << sep;
    ss.seekg(0, std::ios::beg);
    ss >> std::noskipws;

    for (auto i = 4; i != 0; --i) {
        int n {};
        char c {};
        if (!(ss >> n >> c && 0 <= n && n <= 255 && c == sep)) return false;
    }

    char d {};
    return (!(ss >> d));
}
