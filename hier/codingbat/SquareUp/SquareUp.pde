import java.util.StringJoiner;

private static int[] squareUp(final int n) {
  final int[] a = new int[n * n];
  
  for (int i = 0; i != n; ++i) {
    for (int j = n - 1 - i; j != n; ++j)
      a[i * n + j] = n - j;
  }
  
  return a;
}

private static void test(final int n) {
  final StringJoiner sj = new StringJoiner(", ", "[", "]");
  for (final int x : squareUp(n)) sj.add(String.valueOf(x));
  System.out.println(sj);
}

public static void main(final String[] args) {
  test(3);
  test(2);
  test(4);
  test(25);
}