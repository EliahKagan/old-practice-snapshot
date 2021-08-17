private static final java.util.regex.Pattern PATTERN =
                      java.util.regex.Pattern.compile("(?<=z).(?=p)");

private static String zipZap(final String str) {
  return PATTERN.matcher(str).replaceAll("");
}

public static void main(final String[] args) {
  System.out.format("%s, %s, %s%n", zipZap("zipXzap"),
                                    zipZap("zopzop"),
                                    zipZap("zzzopzop"));
}