/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

//User function Template for Java
class Geeks
{
    public static long commonSum(int[] arr1, int[] arr2)
    {
        if (arr2.length < arr1.length) {
            final int[] tmp = arr1;
            arr1 = arr2;
            arr2 = tmp;
        }

        final Set<Integer> s = new HashSet<>();
        for (final int x : arr1) s.add(x);

        long sum = 0L;
        for (final int x : arr2)
            if (s.contains(x)) sum += x;

        return sum;
    }
}
