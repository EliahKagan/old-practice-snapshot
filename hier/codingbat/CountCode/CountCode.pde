import java.util.regex.Matcher;
import java.util.regex.Pattern;

private static final Pattern PATTERN = Pattern.compile("co.e");

private static int countCode(final String str) {
  int count = 0;
  for (final Matcher matcher = PATTERN.matcher(str); matcher.find(); ) ++count;
  return count;
}

public static void main(final String[] args) {
  System.out.format("%d, %d, %d%n", countCode("aaacodebbb"),
                                    countCode("codexxcode"),
                                    countCode("cozexxcope"));
}