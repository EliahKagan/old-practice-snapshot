SEC_PER_MIN = 60
MIN_PER_HR = 60
SEC_PER_HR = SEC_PER_MIN * MIN_PER_HR

def input_time(): # gives time in seconds
    h, m, s = map(int, raw_input().split(':'))
    return h * SEC_PER_HR + m * SEC_PER_MIN + s

def print_time(s): # takes time in seconds
    h, s = divmod(s, SEC_PER_HR)
    m, s = divmod(s, SEC_PER_MIN)
    print '{0:02d}:{1:02d}:{2:02d}'.format(h, m, s)

for t in xrange(0, int(raw_input())):
    ti = input_time()
    tf = input_time()
    print_time(tf - ti)
