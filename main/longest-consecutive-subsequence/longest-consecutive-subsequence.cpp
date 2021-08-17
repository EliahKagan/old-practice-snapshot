int findLongestConseqSubseq(int *const a, const int n)
{
    assert(n > 0);
    
    sort(a, a + n);
    
    auto maxlen = 1, len = 1, prev = a[0];
    
    for_each(a, a + n, [&maxlen, &len, &prev](const int cur) {
        switch (cur - prev) {
        case 0:
            return;
        
        case 1:
            ++len;
            break;
        
        default:
            maxlen = max(maxlen, len);
            len = 1;
        }
        
        prev = cur;
    });
    
    return max(maxlen, len);
}
