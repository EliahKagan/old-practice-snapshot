class GfG
{
    /*you are required to complete this method*/
    int countZeros(final int a[][], final int n)
    {
        int count = 0, jstop = n;
        
        for (int i = 0; i != n; ++i) {
            for (int j = 0; j != jstop; ++j) {
                if (a[i][j] != 0) {
                    jstop = j;
                    break;
                }
                
                ++count;
            }
        }
        
        return count;
    }
}
