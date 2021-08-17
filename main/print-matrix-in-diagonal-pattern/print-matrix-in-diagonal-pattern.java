import java.util.*;

class Matrix_In_Diagonal_Pattern
{
	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t>0)
		{
			int n= sc.nextInt();
			int a[][] = new int[1000][1000];
			for(int i=0; i<n; i++)
			{
				for(int j=0;j<n;j++)
				{
					a[i][j] = sc.nextInt();
				}
			}
			GfG g = new GfG();
			g.printMatrixDiagonal(a,n);
			System.out.println();
		t--;
		}
	}
}

class GfG {
    private enum Move {
        RIGHT       (0, 1),
        DOWN_LEFT   (1, -1),
        DOWN        (1, 0),
        UP_RIGHT    (-1, 1);

        public final int di, dj;

        Move(final int di, final int dj)
        {
            this.di = di;
            this.dj = dj;
        }
    }
    
    void printMatrixDiagonal(int a[][], final int n)
    {
        final int max = n - 1;
        
        Move move = Move.RIGHT;
        
        for (int i = 0, j = 0; i != n && j != n; ) {
            System.out.format("%d ", a[i][j]);
            
            i += move.di;
            j += move.dj;
            
            switch (move) {
            case RIGHT:
                move = (i == 0 ? Move.DOWN_LEFT : Move.UP_RIGHT);
                break;
            
            case DOWN_LEFT:
                if (i == max)       move = Move.RIGHT;
                else if (j == 0)    move = Move.DOWN;
                break;
            
            case DOWN:
                move = (j == 0 ? Move.UP_RIGHT : Move.DOWN_LEFT);
                break;
            
            case UP_RIGHT:
                if (j == max)       move = Move.DOWN;
                else if (i == 0)    move = Move.RIGHT;
                break;
            }
        }
    }
}
