namespace {
    int transitionPoint(const int *const arr, const int low, const int high)
    {
        const auto mid = (high + low) / 2;
        
        if (arr[mid]) {
            return arr[mid - 1] ? transitionPoint(arr, low, mid - 1)
                                : mid;
        } else {
            return arr[mid + 1] ? mid + 1
                                : transitionPoint(arr, mid + 1, high);
        }
    }
}

int transitionPoint(int *const arr, const int size)
{
    return transitionPoint(arr, 0, size - 1);
}
