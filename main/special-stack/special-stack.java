/*Complete the function(s) below*/
class GfG{
	public void push(final int a, final Stack<Integer> s)
	{
	    s.push(a);
	}
	
	public int pop(final Stack<Integer> s)
	{
	    return s.pop();
	}
	
	public int min(final Stack<Integer> s)
    {
        return s.stream().mapToInt(x -> x).min().getAsInt();
	}
	
	public boolean isFull(final Stack<Integer> s, final int n)
    {
        return s.size() == n;
	}
	
	public boolean isEmpty(final Stack<Integer> s)
    {
        return s.isEmpty();
	}
}
