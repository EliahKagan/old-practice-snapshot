import java.util.*;
import java.util.Scanner;

final class myCalculator {
    public int power(int n, int p) throws Exception
    {
        if (n < 0 || p < 0)
            throw new java.lang.Exception("n and p should be non-negative");

        int ans = 1;
        for (; p != 0; --p) ans *= n;
        return ans;
    }
}

class Solution{

    public static void main(String []argh)
    {
        Scanner in = new Scanner(System.in);

        while(in.hasNextInt())
        {
            int n = in.nextInt();
            int p = in.nextInt();
            myCalculator M = new myCalculator();
            try
            {
                System.out.println(M.power(n,p));
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
        }

    }
}
