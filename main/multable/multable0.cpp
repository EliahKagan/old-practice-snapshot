#include <iomanip>
#include <iostream>

int main()
{
	constexpr auto size = 12;

	for (auto i = 1; i <= size; ++i) {
		for (auto j = 1; j <= size; ++j)
			std::cout << ' ' << std::setw(3) << i * j;

		std::cout << '\n';
	}
}
