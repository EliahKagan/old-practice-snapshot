# Your task is to Complete this function
# functtion should return an integer
def maxDistance(a, n):
    indices = {}
    for i in xrange(0, n):
        indices.setdefault(a[i], []).append(i)
    
    return max(ind[-1] - ind[0] for ind in indices.values())
