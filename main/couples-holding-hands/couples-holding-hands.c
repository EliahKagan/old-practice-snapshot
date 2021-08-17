static inline void makeSets(int *const a, const int n)
{
    // set every element to -1
    memset(a, 0xFF, n * sizeof *a);
}

static int findSet(int *const a, int i)
{
    // find the ancestor
    int j = i;
    while (a[j] >= 0) j = a[j];

    // compress the path
    while (i != j) {
        const int next = a[i];
        a[i] = j;
        i = next;
    }

    return j;
}

static int unite(int *const a, int i, int j)
{
    // find the ancestors and stop if they are the same
    i = findSet(a, i);
    j = findSet(a, j);
    if (i == j) return 0;

    // union by rank
    if (a[i] > a[j]) {
        // j has superior (more negative) rank, so make it the parent
        a[i] = j;
    } else {
        // if i and j both have the same rank, promote i
        if (a[i] == a[j]) --a[i];

        // i has superior (more negative) rank, so make it the parent
        a[j] = i;
    }

    return 1;
}

int minSwapsCouples(int *row, const int rowSize)
{
    const int n = rowSize / 2;
    int a[n];
    makeSets(a, n);

    int swaps = 0;
    for (int pos = 0; pos != rowSize; pos += 2)
        swaps += unite(a, row[pos] / 2, row[pos + 1] / 2);

    return swaps;
}
