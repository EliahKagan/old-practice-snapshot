import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

class Student{
   private int token;
   private String fname;
   private double cgpa;
   public Student(int id, String fname, double cgpa) {
      super();
      this.token = id;
      this.fname = fname;
      this.cgpa = cgpa;
   }
   public int getToken() {
      return token;
   }
   public String getFname() {
      return fname;
   }
   public double getCgpa() {
      return cgpa;
   }
}

public class Solution {
    private static Comparator<Student> getStudentComparator() {
        return Comparator.comparing(Student::getCgpa).reversed()
                         .thenComparing(Student::getFname)
                         .thenComparing(Student::getToken);
    }
    
    private static Queue<Student> createStudentPriorityQueue() {
        return new PriorityQueue<>(getStudentComparator());
    }
    
    private static void processEvents(final Queue<Student> students,
                                      final Scanner sc) {
        for (int n = sc.nextInt(); n > 0; --n) {
            switch (sc.next()) {
            case "ENTER":
                final String fname = sc.next();
                final double cgpa = sc.nextDouble();
                final int id = sc.nextInt();

                students.add(new Student(id, fname, cgpa));
                continue;

            case "SERVED":
                students.poll();
                continue;

            default:
                throw new IllegalStateException();
            }
        }
    }
    
    private static void dumpRemaining(final Queue<Student> students) {
        if (students.isEmpty()) {
            System.out.println("EMPTY");
            return;
        }
        
        for (Student cur; (cur = students.poll()) != null; )
            System.out.println(cur.getFname());
    }
    
    public static void main(String[] args) {
        final Queue<Student> students = createStudentPriorityQueue();
        
        try (final Scanner sc = new Scanner(System.in)) {
            processEvents(students, sc);
        }
        
        dumpRemaining(students);
    }
}
