private static boolean evenlySpaced(final int a, final int b, final int c) {
  // If any 2 pairs of evenly spaced numbers are equal, they must all be equal.
  if (a == b || b == c || c == a) return a == b && b == c && c == a;
  
  // Otherwise, they're evenly spaced iff 2 equal differences exist among them.
  final int ab = Math.abs(a - b), bc = Math.abs(b - c), ca = Math.abs(c - a);
  return ab == bc || bc == ca || ca == ab;
}

public static void main(final String[] args) {
  System.out.format("%b, %b, %b%n", evenlySpaced(2, 4, 6),
                                    evenlySpaced(4, 6, 2),
                                    evenlySpaced(4, 6, 3));
}