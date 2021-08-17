/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for Java
/*Complete the function below*/
class GfG{
    public Queue<Integer> rev(final Queue<Integer> q) {
        final Deque<Integer> s = new ArrayDeque<>(q.size());
        while (!q.isEmpty()) s.push(q.remove());
        while (!s.isEmpty()) q.add(s.pop());
        return q;
    }
}
