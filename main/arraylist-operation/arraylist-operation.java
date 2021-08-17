/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

//User function Template for Java
// Geeks clas with functions insert and freq
// insert : to insert element into ArrayList
// freq : function to count frequency of element
class Geeks
{
    // Function to insert element
    public static void insert(final ArrayList<Character> clist, final char c) {
        clist.add(c);
    }
    
    // Function to count frequency of element
    public static void freq(final ArrayList<Character> clist, final char c) {
        final int f = Collections.frequency(clist, c);
        
        if (f > 0)
            System.out.println(f);
        else
            System.out.println("Not Present");
    }
}
