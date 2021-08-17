private static int strDistWrapper(final String str, final String sub) {
  System.out.format("Calling strDist(\"%s\", \"%s\").%n", str, sub);
  final int ret = strDist(str, sub);
  System.out.format("strDist(\"%s\", \"%s\") returned %d.%n", str, sub, ret);
  return ret;
}

private static int strDist(final String str, final String sub) {
  final boolean starts = str.startsWith(sub), ends = str.endsWith(sub);
  if (starts && ends) return str.length();
  
  final int last = str.length() - 1;
  
  if (last >= sub.length()) {
    if (starts) return strDistWrapper(str.substring(0, last), sub);
    if (ends) return strDistWrapper(str.substring(1), sub);
    if (last != sub.length()) return strDistWrapper(str.substring(1, last), sub);
  }
  
  return 0;
}

public static void main(final String[] args) {
  strDistWrapper("catcowcat", "cow");
}