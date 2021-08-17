/*You are required to complete below methods*/

class GfG
{
    /*inserts an element x at 
    the back of the ArrayList A */
    void add_to_ArrayList(ArrayList<Integer> A, int x)
    {
        A.add(x);
    }	
	
    /*sort the ArrayList A in ascending order*/
    void sort_ArrayList_Asc(ArrayList<Integer> A)
    {
        A.sort(null);
    }
	
    /*reverses the ArrayList A*/
    void reverse_ArrayList(ArrayList<Integer> A)
    {
        Collections.reverse(A);
    }
	
    /*returns the size of the ArrayList A */
    int size_Of_ArrayList(ArrayList<Integer> A)
    {
        return A.size();
    }
	
    /*sorts the ArrayList A in descending order*/
    void sort_ArrayList_Desc(ArrayList<Integer> A)
    {
        //A.sort((i, j) -> j.compareTo(i));
        A.sort(null);
        Collections.reverse(A);
    }
	
    /*prints space separated 
    elements of ArrayList A*/
    void print_ArrayList(ArrayList<Integer> A)
    {
        for (final int x : A) System.out.format("%d ", x);
    }
}
