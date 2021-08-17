''' Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above. '''

def normalize_to_permutation(values):
    return sorted(range(len(values)), key=lambda i: values[i])

def count_inversions(permutation):
    ret = 0

    for i in range(len(permutation)):
        if permutation[i] is None:
            continue

        j = permutation[i]
        permutation[i] = None

        while permutation[j] is not None:
            ret += 1
            permutation[j], j = None, permutation[j]

    return ret

# Your task is to complete this function
# function should return an integer denoting the minimum number of swap's
def minSwaps(a, n):
    return count_inversions(normalize_to_permutation(a[:n]))
