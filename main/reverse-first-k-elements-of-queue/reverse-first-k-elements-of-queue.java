/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for Java
class GfG {
    public Queue<Integer> modifyQueue(final Queue<Integer> q, int k)
    {
        final Deque<Integer> d = new ArrayDeque<>(q.size());
        while (k-- != 0) d.addFirst(q.remove());
        while (!q.isEmpty()) d.addLast(q.remove());
        return d;
    }
}
