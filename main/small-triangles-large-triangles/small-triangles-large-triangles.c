#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

static int scaled_squared_area(const triangle *const tp)
{
    const int perim = tp->a + tp->b + tp->c;

    return perim * (perim - tp->a * 2)
                 * (perim - tp->b * 2)
                 * (perim - tp->c * 2);
}

static int compare(const void *const lhsp_param, const void *const rhsp_param)
{
    const triangle *const lhsp = (const triangle *)lhsp_param;
    const triangle *const rhsp = (const triangle *)rhsp_param;

    const int lhs_key = scaled_squared_area(lhsp);
    const int rhs_key = scaled_squared_area(rhsp);

    if (lhs_key < rhs_key) return -1;
    if (lhs_key > rhs_key) return +1;
    return 0;
}

// Sort an array, a, of n triangles.
void sort_by_area(triangle *const a, const int n)
{
    qsort(a, n, sizeof *a, compare);
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
