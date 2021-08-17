private static String wordEnds(final String str, final String word) {
  final StringBuilder sb = new StringBuilder();
  
  for (int i = 0; (i = str.indexOf(word, i)) != -1; ) {
    if (i != 0) sb.append(str.charAt(i - 1));
    i += word.length();
    if (i != str.length()) sb.append(str.charAt(i));
  }
  
  return sb.toString();
}

public static void main(final String[] args) {
  System.out.format("%s, %s, %s%n", wordEnds("abcXY123XYijk", "XY"),
                                    wordEnds("XY123XY", "XY"),
                                    wordEnds("XY1XY", "XY"));
}