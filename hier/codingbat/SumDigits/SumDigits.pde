private static int sumDigits(final String str) {
  int sum = 0;
  
  for (int i = 0; i != str.length(); ++i) {
    final char c = str.charAt(i);
    if ('0' < c && c <= '9') sum += c - '0';
  }
  
  return sum;
}

public static void main(final String[] args) {
  System.out.println(sumDigits("1"));
}