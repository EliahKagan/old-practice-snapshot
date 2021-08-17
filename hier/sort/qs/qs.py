#!/usr/bin/env python3

def swap_center_to_front(low, high):
    """Exchanges an element at the center of a range with its first element."""
    center = (low + high) // 2
    a[low], a[center] = a[center], a[low]

def quicksort_hoare(a):
    """Quicksorts a list, using Hoare partitioning."""
    def partition(low, high):
        swap_center_to_front(low, high)
        pivot = a[low]
        low -= 1
        high += 1

        while True:
            low += 1
            while a[low] < pivot:
                low += 1

            high -= 1
            while pivot < a[high]:
                high -= 1

            if low >= high:
                return high

            a[low], a[high] = a[high], a[low]

    def quicksort_subarray(low, high):
        if low < high:
            mid = partition(low, high)
            quicksort_subarray(low, mid)
            quicksort_subarray(mid + 1, high)

    quicksort_subarray(0, len(a) - 1)


def quicksort_lomuto(a):
    """Quicksorts a list, using Lomuto partitioning."""
    def partition(low, high):
        swap_center_to_front(low, high)
        pivot = a[low]
        left = low

        for right in range(low + 1, high + 1):
            if a[right] < pivot:
                left += 1
                a[left], a[right] = a[right], a[left]

        a[low], a[left] = a[left], a[low]
        return left

    def quicksort_subarray(low, high):
        if low < high:
            mid = partition(low, high)
            quicksort_subarray(low, mid - 1)
            quicksort_subarray(mid + 1, high)

    quicksort_subarray(0, len(a) - 1);
