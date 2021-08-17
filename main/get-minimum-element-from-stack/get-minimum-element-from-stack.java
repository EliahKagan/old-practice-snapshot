class GfG
{
    static final int NO_ELEMENT = -1;
    
    private int minElement = NO_ELEMENT;
    private final Stack<Integer> stack = new Stack<>();

    /*returns min element from stack*/
    int getMin()
    {
        return stack.empty() ? NO_ELEMENT : minElement;
    }
    
    /*returns poped element from stack*/
    int pop()
    {
        if (stack.empty()) return NO_ELEMENT;
        
        final int top = stack.pop();
        
        if (top < minElement) {
            final int ret = minElement;
            minElement = minElement * 2 - top;
            return ret;
        }
        
        return top;
    }

    /*push element x into the stack*/
    void push(final int x)
    {
        if (stack.empty()) stack.push(minElement = x);
        else if (x < minElement) {
            stack.push(x * 2 - minElement);
            minElement = x;
        }
        else stack.push(x);
    }	
}
