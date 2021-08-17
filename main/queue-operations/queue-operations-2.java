/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

//User function Template for Java
// Helper class Geeks to implement 
// insert() and findFrequency()
class Geeks{
    
    // Function to insert element into the queue
    static void insert(final Queue<Integer> q, final int k) {
        q.add(k);
    }
    
    // Function to find frequency of an element
    // rteturn the frequency of k
    static int findFrequency(final Queue<Integer> q, final int k) {
        return Collections.frequency(q, k);
    }
    
}
