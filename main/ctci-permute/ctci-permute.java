final class Permute {
    public static void main(final String[] args) {
        permute("abc");
    }

    private static void permute(final String str) {
        permute(str, "");
    }

    private static void permute(final String str, final String prefix) {
        if (str.isEmpty()) {
            System.out.println(prefix);
            return;
        }

        for (var i = 0; i != str.length(); ++i) {
            final var rem = str.substring(0, i) + str.substring(i + 1);
            permute(rem, prefix + str.charAt(i));
        }
    }

    private Permute() {
        throw new AssertionError();
    }
}
