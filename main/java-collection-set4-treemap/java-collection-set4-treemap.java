/*You are required to complete below methods */
class GfG
{
    /*Inserts an entry with key x and value y in map */
    void add_Value(TreeMap<Integer,Integer> hm, int x, int y)
    {
        hm.put(x, y);
    }
	
    /*Returns the value with key x from the map */
    int find_value(TreeMap<Integer, Integer> hm, int x)
    {
        return hm.getOrDefault(x, -1);
    }
	
    /*Returns the size of the map */
    int getSize(TreeMap<Integer, Integer> hm)
    {
        return hm.size();
    }
		
    /*Removes the entry with key x from the map */	
    void removeKey(TreeMap<Integer, Integer> hm, int x)
    {
        hm.remove(x);
    }

    /*print map sorted by key */	
    void sorted_By_Key(TreeMap<Integer, Integer> hm)
    {
        hm.keySet().stream().forEachOrdered(x -> System.out.format("%d ", x));
    }   
}
