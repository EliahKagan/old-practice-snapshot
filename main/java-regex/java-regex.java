import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Scanner;

class Solution{

    public static void main(String []args)
    {
        Scanner in = new Scanner(System.in);
        while(in.hasNext())
        {
            String IP = in.next();
            System.out.println(IP.matches(new myRegex().pattern));
        }

    }
}

final class myRegex {
    private static final String octet
            = "(?:[01]\\d\\d|2[0-4]\\d|25[0-5]|\\d\\d?)";

    public static final String pattern
            = String.format("(?:%1$s\\.){3}%1$s", octet);
}
