#include <algorithm>
#include <cstdio>
#include <initializer_list>
using namespace std;

namespace {
    int max_of_four(int a, int b, int c, int d) {
        // this clunky notation is in case the MSVCRT is used [it has max() macro]
        return (std::max)(initializer_list<int>{a, b, c, d});
    }
}

// Keeping main() scaffolding provided by unit test, even though it has the bug
// of failing to print a terminal newline after the last (in this case, only)
// write to standard output. Anyone who uses this program for other purposes
// should probably fix that first. It might be a good idea to also check that
// the four variables were successfully read into, before writing their values
// to standard output (or if not, then initialize them first, for behavior that
// is defined and deterministic).
int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}
