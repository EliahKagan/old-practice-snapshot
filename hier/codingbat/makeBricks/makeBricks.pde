private static boolean makeBricks(final int small, final int big, final int goal) {
  final int big_size = 5;
  
  // With s = number of small bricks used, b = number of big bricks used, we
  // need (s + b * big_size == goal). So use as many big bricks as we can
  // without exceeding goal. Then we succeed iff we have enough small bricks to
  // make up the difference.
  final int b = Math.min(big, goal / big_size);
  final int s = goal - b * big_size;
  
  return s <= small;
}

public static void main(final String[] args) {
  System.out.format("%b, %b, %b%n", makeBricks(3, 1, 8),
                                    makeBricks(3, 1, 9),
                                    makeBricks(3, 2, 10));
}