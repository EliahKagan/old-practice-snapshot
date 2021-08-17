private static final java.util.regex.Pattern PATTERN =
                       java.util.regex.Pattern.compile("co.e");

private static int countCode(final String str) {
  int count = 0;
  
  final java.util.regex.Matcher matcher = PATTERN.matcher(str);
  while (matcher.find()) ++count;
  
  return count;
}

public static void main(final String[] args) {
  System.out.format("%d, %d, %d%n", countCode("aaacodebbb"),
                                    countCode("codexxcode"),
                                    countCode("cozexxcope"));
}