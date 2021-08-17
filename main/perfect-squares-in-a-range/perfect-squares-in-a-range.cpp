#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <algorithm>
#include <cmath>
#include <iostream>

int main()
{
    using namespace std;

    auto t = 0;
    for (cin >> t; t > 0; --t) {
        auto a = 0., b = 0.;
        cin >> a >> b;
        cout << max(lround(floor(sqrt(b)) - ceil(sqrt(a))) + 1L, 0L) << '\n';
    }
}
