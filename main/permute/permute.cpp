#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    std::string s {"abc"};
    do std::cout << s << '\n';
    while std::next_permutation(std::begin(s), std::end(s));
}
