private static final java.util.regex.Pattern PATTERN =
                      java.util.regex.Pattern.compile("(?:^|.)\\*+(?:.|$)");

private static String starOut(String str) {
  return PATTERN.matcher(str).replaceAll("");
}

public static void main(final String[] args) {
  System.out.format("%s, %s, %s%n", starOut("ab*cd"),
                                    starOut("ab**cd"),
                                    starOut("sm*eilly"));
}