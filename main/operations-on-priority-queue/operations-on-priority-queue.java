/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

//User function Template for Java
// Helper class Geeks to implement 
// insert() and findFrequency()
class Geeks{
    // Function to insert element into the queue
    static void insert(final PriorityQueue<Integer> q, final int k) {
        q.add(k);
    }
    
    // Function to find an element k
    static boolean find(final PriorityQueue<Integer> q, final int k) {
        return q.contains(k);
    }
    
    // Function to delete the element from queue
    static int delete(final PriorityQueue<Integer> q) {
        return q.remove();
    }
}
