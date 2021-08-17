private static boolean endOther(String a, String b) {
  a = a.toLowerCase();
  b = b.toLowerCase();
  return a.endsWith(b) || b.endsWith(a);
}

public static void main(final String[] args) {
  System.out.format("%b, %b, %b, %b, %b, %b%n",
      endOther("Hiabc", "abc"), endOther("AbC", "HiaBc"), endOther("abc", "abXabc"),
      endOther("xyz", "xyz"), endOther("xyz", "xy"), endOther("ab", "cd"));
}