class GfG
{
    private static final int BASE = 10, FROM_DIGIT = 0, TO_DIGIT = 5;
    
    int convertfive(int num)
    {
        int ret = 0;
        for (int place = 1; num != 0; num /= BASE, place *= BASE) {
            final int digit = num % BASE;
            ret += (digit == FROM_DIGIT ? TO_DIGIT : digit) * place;
        }
        
        return ret;
    }
}
