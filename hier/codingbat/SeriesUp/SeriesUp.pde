import java.util.StringJoiner;

private static int[] seriesUp(final int n) {
  final int[] a = new int[n * (n + 1) / 2];
  int pos = 0;
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j)
      a[pos++] = j;
  }
  
  return a;
}

private static void test(final int n) {
  final StringJoiner sj = new StringJoiner(", ", "[", "]");
  for (final int x : seriesUp(n)) sj.add(String.valueOf(x));
  System.out.println(sj);
}

public static void main(final String[] args) {
  test(3);
  test(4);
  test(2);
  //test(25);
}