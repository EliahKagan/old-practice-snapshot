private static int countMatches(final String text, final String pattern) {
  int count = 0;
  
  for (int i = 0; i != text.length(); ++i)
    if (text.regionMatches(i, pattern, 0, pattern.length())) ++count;
  
  return count;
}

private static boolean catDog(String str) {
  return countMatches(str, "cat") == countMatches(str, "dog");
}

public static void main(final String[] args) {
  System.out.format("%b, %b, %b%n", catDog("catdog"),
                                    catDog("catcat"),
                                    catDog("1cat1cadodog"));
}