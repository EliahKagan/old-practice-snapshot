import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

class Solution {
    private static final boolean flag = true;
    private static final Scanner sc = new Scanner(System.in);
    private static final int B = check(sc.nextInt()), H = check(sc.nextInt());

    private static int check(int n)
    {
        if (n <= 0) {
            System.out.println(
                    "java.lang.Exception: Breadth and height must be positive");
            System.exit(1);
        }

        return n;
    }

    public static void main(String[] args){
		if(flag){
			int area=B*H;
			System.out.print(area);
		}

	}//end of main

}//end of class
