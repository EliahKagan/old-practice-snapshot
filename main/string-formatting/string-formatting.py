def print_formatted(n):
    w = n.bit_length()
    
    for i in xrange(1, n + 1):
        print '%*d %*o %*X %*s' % (w, i, w, i, w, i, w, '{0:b}'.format(i))

if __name__ == '__main__':
    print_formatted(int(raw_input()))
