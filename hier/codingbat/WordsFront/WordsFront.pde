import java.util.Arrays;

private static String[] wordsFront(final String[] words, final int n) {
  return Arrays.copyOfRange(words, 0, n);
}

public static void main(final String[] args) {
    final String[] a = wordsFront(new String[] { "a", "b", "c", "d" }, 3);
    System.out.println(String.join(" ", a));
}