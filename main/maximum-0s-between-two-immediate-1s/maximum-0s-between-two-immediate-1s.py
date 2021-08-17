def get():
    return int(raw_input())

def max_internal_zero_run_length(n):
    bits = '{0:b}'.format(n).strip('0')
    
    if len(bits) < 2:
        return -1
    
    runs = bits.split('1')
    lengths = map(len, runs)
    return max(lengths)

for t in xrange(get()):
    print max_internal_zero_run_length(get())
