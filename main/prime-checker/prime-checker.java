import java.io.*;
import java.util.*;
//import java.text.*;
//import java.math.*;
//import java.util.regex.*;
import java.lang.reflect.*;

import java.util.stream.IntStream;
import static java.lang.System.in;

final class Prime {
    private static int sqrt(final int n) {
        return (int)Math.sqrt(n); // simple cast from double OK for 32-bit ints
    }
    
    private static IntStream rangeClosed(
            final int startInclusive, final int endInclusive, final int step) {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    private static IntStream sieve(final int n) { // streams primes up to n
        final boolean[] a = new boolean[n + 1];
        
        final int imax = sqrt(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return IntStream.concat(IntStream.of(2),
                                rangeClosed(3, n, 2).filter(k -> !a[k]));
    }
    
    private final int[] elems = sieve(sqrt(Integer.MAX_VALUE)).toArray();
    
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
        IntStream.of(values).filter(this::isPrime)
                            .forEachOrdered(p -> System.out.format("%d ", p));
        
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
