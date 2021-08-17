import java.util.regex.*;

final class Program {
    public static void main(final String[] args) {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final Matcher m = Pattern.compile("(\\w+)\\s+(\\w+)\\s+(\\w+)")
                                     .matcher(sc.nextLine());
            if (!m.find()) {
                System.out.println("No match.");
                return;
            }

            for (int i = 1; i <= 3; ++i)
                System.out.format("%d: %s%n", i, m.group(i));
        }
    }
    
    private Program() { } // the Program class should not be instantiated
}
