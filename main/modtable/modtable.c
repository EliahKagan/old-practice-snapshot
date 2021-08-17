// modtable.c - prints simple 11-by-11 modulus (remainder) table

#include <wchar.h>

int main()
{
    enum { w = 3, min = 0, max = 10 };
    _Static_assert(min <= max, "table must be at least 1-by-1 (min <= max)");

    wprintf(L"%*d", w * 3, min);
    for (int j = min + 1; j <= max; ++j) wprintf(L"%*d", w, j);
    fputws(L"\n\n", stdout);

    for (int i = min; i <= max; ++i) {
        wprintf(L"%*d%*c", w, i, w * 2, L'-');
        for (int j = min + 1; j <= max; ++j) wprintf(L"%*d", w, i % j);
        putwchar(L'\n');
    }
}
