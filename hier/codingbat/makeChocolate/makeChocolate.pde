private static int makeChocolate(final int small, final int big, final int goal) {
  final int big_mass = 5;
  
  // With s = number of small bars used, b = number of big bars used, we need
  // (s + b * big_mass == goal), and must use the greedy approach of using as
  // many big bars as possible before using any small bars, which is the
  // optimal strategy anyway. After using as many big bars as possible without
  // exceeding goal, we succeed iff we have enough small bricks to make up the
  // difference. This is exactly the same problem as makeBricks, except (a) the
  // greedy approach is required, and (b) we report how many small bars to use.
  final int b = Math.min(big, goal / big_mass);
  final int s = goal - b * big_mass;
  
  return s > small ? -1 : s;
}

public static void main(final String[] args) {
  System.out.format("%d, %d, %d%n", makeChocolate(4, 1, 9),
                                    makeChocolate(4, 1, 10),
                                    makeChocolate(4, 1, 7));
}