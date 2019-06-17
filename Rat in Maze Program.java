import java.util.Scanner;
class RatMaze
{
  static int r,c;
  public static void main(String ar[])
  {
    int i,j;
    
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter row");
     r = sc.nextInt();
    System.out.println("Enter column");
    c = sc.nextInt();
    int matrix[][] = new int[r][c];
    System.out.println("Enter elements");
    for( i=0; i<r; i++)
      for( j=0; j<c ;j++)
         matrix[i][j] = sc.nextInt();
    
    System.out.println("Enter Starting row and column");
    int r1 = sc.nextInt();
    int c1 = sc.nextInt();
    
    
    System.out.println("Enter ending row and column");
    int r2 = sc.nextInt();
    int c2 = sc.nextInt();
    
    int result[][] = new int[r][c];
    
    findPath(matrix, result, r1, c1,'N', 'N', r2, c2);
     
  }
  static void findPath(int matrix[][], int result[][], int curR,int curC, char previous,char direction, int destR,int destC)
  {
    int i,j;
    for( i=0; i<r; i++)
      for( j=0; j<c ;j++)
         System.out.println(matrix[i][j]);
    
  }
}
    