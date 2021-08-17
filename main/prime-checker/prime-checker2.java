import java.io.*;
import java.util.*;
//import java.text.*;
//import java.math.*;
//import java.util.regex.*;
import java.lang.reflect.*;

import static java.lang.System.in;

final class Prime {
    private static int sqrt(final int n) {
        return (int)Math.sqrt(n); // simple cast from double OK for 32-bit ints
    }
    
    private static int rawSieve(final boolean[] a) // returns count of primes
    {
        final int n = a.length - 1;
        int count = n - n / 2; // evens, including 0 but not 2, aren't prime
        
        final int imax = sqrt(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) {
                    if (a[j]) continue;
                    a[j] = true;
                    --count;
                }
            }
        }
        
        return count;
    }
    
    static int[] sieve(final int n) // returns array of primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        final int count = rawSieve(a);
        
        final int[] primes = new int[count];
        primes[0] = 2;
        
        for (int p = 1, k = 1; k != count; ++k) {
            while (a[p += 2]) { }
            primes[k] = p;
        }
        
        return primes;
    }
    
    private final int[] elems = sieve(sqrt(Integer.MAX_VALUE));
    
    private boolean hasSmallFactor(final int n) {
        final int pmax = sqrt(n);
        
        for (final int p : elems) {
            if (p > pmax) break;
            if (n % p == 0) return true;
        }
        
        return false;
    }
    
    private boolean isPrime(final int n) {
        final int i = java.util.Arrays.binarySearch(elems, n);
        return i >= 0 || (~i == elems.length && !hasSmallFactor(n));
    }
    
    public void checkPrime(final int... values) {
        for (final int n : values)
            if (isPrime(n)) System.out.format("%d ", n);
        
        System.out.println();
    }
}

/*public*/ class Solution {

	public static void main(String[] args) {
		try{
		BufferedReader br=new BufferedReader(new InputStreamReader(in));
		int n1=Integer.parseInt(br.readLine());
		int n2=Integer.parseInt(br.readLine());
		int n3=Integer.parseInt(br.readLine());
		int n4=Integer.parseInt(br.readLine());
		int n5=Integer.parseInt(br.readLine());
		Prime ob=new Prime();
		ob.checkPrime(n1);
		ob.checkPrime(n1,n2);
		ob.checkPrime(n1,n2,n3);
		ob.checkPrime(n1,n2,n3,n4,n5);	
		Method[] methods=Prime.class.getDeclaredMethods();
		Set<String> set=new HashSet<>();
		boolean overload=false;
		for(int i=0;i<methods.length;i++)
		{
			if(set.contains(methods[i].getName()))
			{
				overload=true;
				break;
			}
			set.add(methods[i].getName());
			
		}
		if(overload)
		{
			throw new Exception("Overloading not allowed");
		}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
	
}
