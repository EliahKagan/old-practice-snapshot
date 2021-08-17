private static final java.util.regex.Pattern PATTERN =
                      java.util.regex.Pattern.compile("b.b");

private static boolean bobThere(final String str) {
  return PATTERN.matcher(str).find();
}

public static void main(final String[] args) {
  System.out.format("%b, %b, %b%n", bobThere("abcbob"),
                                    bobThere("b9b"),
                                    bobThere("bac"));
}