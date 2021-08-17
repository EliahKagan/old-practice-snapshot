private static final java.util.regex.Pattern PATTERN =
                      java.util.regex.Pattern.compile("(?<!\\.)xyz");

private static boolean xyzThere(String str) {
  return PATTERN.matcher(str).find();
}

public static void main(final String[] args) {
  System.out.format("%b, %b, %b%n", xyzThere("abcxyz"),
                                    xyzThere("abc.xyz"),
                                    xyzThere("xyz.abc"));
}