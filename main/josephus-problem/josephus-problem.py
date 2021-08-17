#Your task is to complete this function
#Your function should return an integer 
def josephus(n, k):
    'Solves the josephus problem using the naive algorithm.'
    assert n > 0 and k > 0
    k -= 1
    
    a = range(1, n + 1)
    i = 0
    
    while len(a) != 1:
        i = (i + k) % len(a)
        del a[i]
    
    return a[0]
