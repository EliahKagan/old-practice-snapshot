private static int countHi(final String str) {
  final String pattern = "hi";
  
  int count = 0;
  
  for (int i = 0; i != str.length(); ++i)
    if (str.regionMatches(i, pattern, 0, pattern.length())) ++count;
  
  return count;
}

public static void main(final String[] args) {
  System.out.format("%d, %d, %d%n", countHi("abc hi ho"),
                                    countHi("ABChi hi"),
                                    countHi("hihi"));
}