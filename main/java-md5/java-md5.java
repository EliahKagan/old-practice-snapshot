import java.security.MessageDigest;
import javax.xml.bind.DatatypeConverter;

final class Solution {
    private static byte[] getMessageText()
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            return sc.next().getBytes(java.nio.charset.StandardCharsets.UTF_8);
        }
    }
    
    public static void main(final String[] args)
    {
        try {
            final MessageDigest md = MessageDigest.getInstance("MD5");
            final byte[] md5sum = md.digest(getMessageText());
            final String md5sum_hex = DatatypeConverter.printHexBinary(md5sum);
            System.out.println(md5sum_hex.toLowerCase());
        }
        catch (final java.security.NoSuchAlgorithmException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
