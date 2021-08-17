class GfG
{
    static final int NOT_FOUND = -1;
    
	int bin_search(final int a[], final int left, final int right, final int k)
	{
		final int mid = left + (right - left) / 2;
		if (right < left) return NOT_FOUND;
		if (k < a[mid]) return bin_search(a, left, mid - 1, k);
		if (k > a[mid]) return bin_search(a, left + 1, right, k);
		return mid;
	}
}
