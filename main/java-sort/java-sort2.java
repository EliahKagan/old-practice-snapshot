import java.util.*;

final class Student implements Comparable<Student> {
    public final String name;
    public final double gpa;
    
    public Student(final Scanner sc)
    {
        sc.nextInt(); // discard unneded ID
        name = sc.next();
        gpa = sc.nextDouble();
    }
    
    @Override public int compareTo(final Student other)
    {
        final int by_gpa = Double.compare(other.gpa, gpa);
        return by_gpa != 0 ? by_gpa : name.compareTo(other.name);
    }
}

final class Solution {
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final Student[] a = new Student[sc.nextInt()];
            for (int i = 0; i != a.length; ++i) a[i] = new Student(sc);
            Arrays.sort(a);
            for (final Student s : a) System.out.println(s.name);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
