private static String plusOut(String str, String word) {
  final StringBuilder sb = new StringBuilder();
  
  for (int left = 0; left != str.length(); ) {
    final int found = str.indexOf(word, left);
    final int right = (found == -1 ? str.length() : found);
    
    for (; left != right; ++left) sb.append('+');
    
    if (found != -1) {
      sb.append(word);
      left += word.length();
    }
  }
  
  return sb.toString();
}


public static void main(final String[] args) {
  System.out.format("%s, %s, %s%n", plusOut("12xy34", "xy"),
                                    plusOut("12xy34", "1"),
                                    plusOut("12xy34xyabcxy", "xy"));
}