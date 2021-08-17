
final class Calculator {
    private void fail() {
        throw new NumberFormatException("All the values must be positive");
    }
    
    public double get_volume(final int a) {
        if (a <= 0) fail();
        return a * a * a;
    }
    
    public double get_volume(final int l, final int b, final int h) {
        if (l <= 0 || b <= 0 || h <= 0) fail();
        return l * b * h;
    }
    
    public double get_volume(final double r) {
        if (r <= 0.0) fail();
        return 2 * Math.PI * r * r * r / 3;
    }
    
    public double get_volume(final double r, final double h) {
        if (r <= 0.0 || h <= 0.0) fail();
        return Math.PI * r * r * h;
    }
}

final class Output {
    public void display(final int volume) {
        System.out.println(volume);
    }
    
    public void display(final double volume) {
        System.out.format("%.3f%n", volume);
    }
}

final class Calculate implements AutoCloseable {
    public static Calculator do_calc() {
        return new Calculator();
    }
    
    private final Scanner scanner = new Scanner(System.in);
    
    public final Output output = new Output();
    
    public int get_int_val() throws IOException {
        try {
            return scanner.nextInt();
        }
        catch (final NoSuchElementException e) {
            throw new IOException(e);
        }
    }
    
    public double get_double_val() throws IOException {
        try {
            return scanner.nextDouble();
        }
        catch (final NoSuchElementException e) {
            throw new IOException(e);
        }
    }
    
    @Override
    public void close() {
        scanner.close();
    }
}
