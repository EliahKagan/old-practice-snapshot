import java.util.Scanner;
import java.util.*;



class LRU_Cache
{
	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t>0)
		{
			Set<Integer> s = new HashSet<Integer>() ;
				int n = sc.nextInt();
				LRUCache g = new LRUCache(n);
			int q = sc.nextInt();
			
			while(q>0)
			{
			
				String c = sc.next();
			//	System.out.println(c);
				if(c.equals("GET"))
				{
					int x = sc.nextInt();
					System.out.print(g.get(x)+" ");
				}
				if(c.equals("SET"))
				{
					int x = sc.nextInt();
					int y  = sc.nextInt();
					g.set(x,y);
				}
			
			q--;
			//System.out.println();
			}
		t--;
		System.out.println();
		}
	}
}

class LRUCache {
    public static final int ABSENT = -1;
    
    public LRUCache(final int capacity)
    {
        if (capacity < 1) 
            throw new IllegalArgumentException("capacity must be positive");
        
        this.capacity = capacity;
        this.lookup = new HashMap<>(capacity);
    }
    
    public int get(final int key)
    {
        final Node cur = lookup.get(key);
        if (cur == null) return ABSENT;
        
        bump(cur);
        return cur.value;
    }
    
    public void set(final int key, final int value)
    {
        final Node result = lookup.get(key);
        
        if (result == null) insert(key, value);
        else {
            bump(result);
            result.value = value;
        }
    }
    
    private static final class Node { // node for a circular linked list
        int key, value;
        
        Node() { this(ABSENT, ABSENT); } // make sentinel node
        
        // adds a new (key, value) node, just after this, and returns it
        Node splice(final int key, final int value)
        {
            final Node other = new Node(key, value);
            attach(other);
            return other;
        }
        
        void splice(final Node other) // moves other to come just after this
        {
            if (next != other) { // this check is an optimization
                other.detach();
                attach(other);
            }
        }
        
        private Node(final int key, final int value)
        {
            this.key = key;
            this.value = value;
            this.prev = this.next = this;
        }
        
        private void detach()
        {
            this.prev.next = this.next;
            this.next.prev = this.prev;
        }
        
        private void attach(final Node other)
        {
            other.prev = this;
            other.next = next;
            other.next.prev = next = other;
        }
        
        private Node prev, next;
    };
    
    private final int capacity;
    private int size = 0;
    
    private Map<Integer, Node> lookup;
    
    // list.next is front (priority); list.prev is back (LRU)
    private Node list = new Node();
    
    private Node back() { return list.prev; }
    private void bump(final Node cur) { list.splice(cur); } // move to front
    
    private void insert(final int key, final int value) // assumes key is new
    {
        final Node front;
        
        if (size == capacity) {
            front = back(); // reuse the least recently used node
            lookup.remove(front.key);
            bump(front);
            
            front.key = key;
            front.value = value;
        } else {
            front = list.splice(key, value);
            ++size;
        }
        
        lookup.put(key, front);
    }
}
