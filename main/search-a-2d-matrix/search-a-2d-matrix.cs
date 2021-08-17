public class Solution {
    public bool SearchMatrix(int[,] matrix, int target)
        => matrix.AsFlatView().BSearch(target) != -1;
}

internal sealed class FlatView<T> : IList<T> {
    public FlatView(T[,] matrix) {
        _matrix = matrix;
        _width = matrix.GetLength(1);
    }

    public T this[int index] {
        get => _matrix[index / _width, index % _width];
        set => throw new NotSupportedException("View is read-only.");
    }

    public int Count => _matrix.Length;

    public bool IsReadOnly => true;

    public IEnumerator<T> GetEnumerator() {
        foreach (var item in _matrix) yield return item;
    }

    int IList<T>.IndexOf(T item)
        => throw new NotSupportedException("View doesn't support searching.");

    void IList<T>.Insert(int index, T item)
        => throw new NotSupportedException("Collection was of a fixed size.");

    void IList<T>.RemoveAt(int index)
        => throw new NotSupportedException("Collection was of a fixed size.");

    void ICollection<T>.Add(T item)
        => throw new NotSupportedException("Collection was of a fixed size.");

    void ICollection<T>.Clear()
        => throw new NotSupportedException("Collection was of a fixed size.");

    bool ICollection<T>.Contains(T item)
        => throw new NotSupportedException("View doesn't support searching.");

    void ICollection<T>.CopyTo(T[] array, int index)
        => throw new NotSupportedException("View doesn't support copying.");

    bool ICollection<T>.Remove(T item)
        => throw new NotSupportedException("Collection was of a fixed size.");

    IEnumerator IEnumerable.GetEnumerator() => _matrix.GetEnumerator();

    private T[,] _matrix;

    private int _width;
}

internal static class Extensions {
    internal static FlatView<T> AsFlatView<T>(this T[,] self)
        => new FlatView<T>(self);

    internal static int BSearch<T>(this IList<T> self, T item)
            where T : IComparable<T> {
        var left = 0;
        var right = self.Count - 1;

        while (left <= right) {
            var mid = left + (right - left) / 2;
            var comp = self[mid].CompareTo(item);

            if (comp < 0) left = mid + 1;
            else if (comp == 0) return mid;
            else right = mid - 1;
        }

        return -1;
    }
}
