final class Program {
    private static final int SIZE = 12;

    public static void main(final String[] args) {
        for (var i = 1; i <= SIZE; ++i) {
            for (var j = 1; j <= SIZE; ++j) System.out.format(" %3d", i * j);
            System.out.println();
        }
    }

    private Program() { throw new AssertionError();  }
}
