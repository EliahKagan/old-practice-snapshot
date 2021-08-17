<Query Kind="Statements" />

void PrintIndicesAndValues(int[] a)
	=> Enumerable.Range(0, a.Length)
		.Zip(a, (Index, Value) => new { Index, Value })
		.Dump();

int BinarySearch(int[] a, int low, int high, int key)
{
	if (low > high) return -1;
	
	var mid = (low + high) / 2;
	
	if (a[mid] < key) return BinarySearch(a, mid + 1, high, key);
	if (a[mid] > key) return BinarySearch(a, low, mid - 1, key);
	return mid;
}

int BSearch(int[] a, int key)
	=> BinarySearch(a, 0, a.Length, key);

int[] b = { 10, 20, 25, 30, 50, 95, 100, 117 };

//PrintIndicesAndValues(b);
BSearch(b, 32).Dump();
BSearch(b, 30).Dump();
