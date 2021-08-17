bool canJump(int *const a, int j) {
    --j;

    while (j != 0) {
        int i = j - 1;
        while (i != -1 && i + a[i] < j) --i;
        if (i == -1) return false;
        j = i;
    }

    return true;
}
