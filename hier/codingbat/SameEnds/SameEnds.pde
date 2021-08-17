private static final java.util.regex.Pattern PATTERN =
                      java.util.regex.Pattern.compile("\\A(.*)(?=.*?\\1\\z)");

private static String sameEnds(final String str) {
  final java.util.regex.Matcher matcher = PATTERN.matcher(str);
  matcher.find();
  return matcher.group();
}

public static void main(final String[] args) {
  System.out.format("\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\"%n",
      sameEnds("abXYab"), sameEnds("xx"), sameEnds("xxx"),
      sameEnds("abcde"), sameEnds(""), sameEnds("abcabcabcabcabc"));
}