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
        
        Node() // make sentinel node
        {
            this.prev = this.next = this;
            this.key = this.value = ABSENT;
        }
        
        Node(final Node prev, final int key, final int value) // make data node
        {
            insert(prev);
            
            this.key = key;
            this.value = value;
        }
        
        void splice(final Node prev) // moves this to come just after prev
        {
            if (this.prev != prev) { // this check is just an optimization
                remove();
                insert(prev);
            }
        }
        
        private void remove() // can make this non-private if callers need it
        {
            this.prev.next = this.next;
            this.next.prev = this.prev;
        }
        
        // helper for cons, splice(); disregards current this.prev, this.next
        private void insert(final Node prev)
        {
            this.prev = prev;
            this.next = prev.next;
            this.next.prev = prev.next = this;
        }
        
        private Node prev, next;
    };
    
    private final int capacity;
    private int size = 0;
    
    private Map<Integer, Node> lookup;
    
    // list.next is front (priority); list.prev is back (LRU)
    private Node list = new Node();
    
    private Node back() { return list.prev; }
    private void bump(final Node cur) { cur.splice(list); } // move to front
    
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
            front = new Node(list, key, value);
            ++size;
        }
        
        lookup.put(key, front);
    }
}
