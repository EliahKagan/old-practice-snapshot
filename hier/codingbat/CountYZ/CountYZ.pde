private static final java.util.regex.Pattern PATTERN =
                      java.util.regex.Pattern.compile("(?Ui)[yz](?!\\p{Alpha})");

private static int countYZ(final String str) {
  int count = 0;
  
  final java.util.regex.Matcher matcher = PATTERN.matcher(str);
  while (matcher.find()) ++count;
  
  return count;
}

public static void main(final String[] args) {
  System.out.format("%s, %s, %s, %s, %s, %s%n",
      countYZ("fez day"), countYZ("day fez"), countYZ("day fyyyz"),
      countYZ("feZ day pax paz pay pal"), countYZ("ayé"), countYZ("adz LAY prax AYYZYZl"));
}