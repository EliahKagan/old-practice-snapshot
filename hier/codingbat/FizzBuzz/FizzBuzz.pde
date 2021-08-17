private static String[] fizzBuzz(final int start, final int end) {
  final String[] ret = new String[Math.max(0, end - start)];
  
  for (int i = 0; i != ret.length; ++i) {
    final int n = start + i;
    final boolean fizz = n % 3 == 0, buzz = n % 5 == 0;
    
    if (fizz && buzz) ret[i] = "FizzBuzz";
    else if (fizz)    ret[i] = "Fizz";
    else if (buzz)    ret[i] = "Buzz";
    else              ret[i] = String.valueOf(n);
  }
  
  return ret;
}

private static void test(final int start, final int end) {
  System.out.println(String.join(", ", fizzBuzz(start, end)));
}

public static void main(final String[] args) {
  test(1, 6);
  test(1, 8);
  test(1, 11);
  test(100, 200);
}