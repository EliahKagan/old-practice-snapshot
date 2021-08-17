private static final java.util.regex.Pattern PATTERN =
    java.util.regex.Pattern.compile("(?U)(?<!\\p{Alpha})is(?!\\p{Alpha})");

private static String notReplace(final String str) {
  return PATTERN.matcher(str).replaceAll("is not");
}

public static void main(final String[] args) {
  System.out.format("\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\"%n",
      notReplace("is test"), notReplace("is-is"), notReplace("This is right"),
      notReplace("Chris is the isthumus king"), notReplace("12is34"), notReplace("")); 
}