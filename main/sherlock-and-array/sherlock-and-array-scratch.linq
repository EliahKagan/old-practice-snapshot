<Query Kind="Program" />

bool ContainsEqualSumCut(this int[] a)
{
    var left = 0;
    var right = a.Sum();
    
    var prev = 0;
    foreach (var cur in a) {
        left += prev;
        right -= cur;
        if (left == right) return true;
        prev = cur;
    }
    
    return false;
}