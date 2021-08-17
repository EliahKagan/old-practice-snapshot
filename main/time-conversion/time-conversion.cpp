#include <ctime>
#include <iomanip>
#include <iostream>

int main()
{
    std::tm t {};
    std::cin >> std::get_time(&t, "%I:%M:%S%t%p");
    std::cout << std::put_time(&t, "%T") << '\n';
}
