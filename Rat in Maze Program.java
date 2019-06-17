import java.util.Scanner;
class RatMaze
{
  static int r,c;                               //class (or) global scope 
  public static void main(String ar[])
  {
    int i,j;
    
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter number of rows");
     r = sc.nextInt();
    System.out.println("Enter number of columns");
    c = sc.nextInt();
    int matrix[][] = new int[r][c];
    System.out.println("Enter matrix elements..\n 0->path not blocked \n 1->path blocked");
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
    
    int status = findPath(matrix, result, r1, c1,'N', 'N', r2, c2);
    if( status< 0)
      System.out.println("Rat cannot find cheese in the maze status: "+ status);
    else 
      System.out.println("Successful status: "+ status);
     
  }
  static int findPath(int matrix[][], int result[][], int curR,int curC, char previous,char direction, int destR,int destC)
  {
    int status = -1;                                            //Used to check whether destination reached or not
     
    if(curR<r && curC<c)
    {
      int i,j;
      
      if(matrix[curR][curC] == 1)
           return -1;                                           // Path Blocked
      if(matrix[curR][curC] == 0)
      {
        if(curR == destR && curC == destC)
        {
          result[curR][curC] = 1;
          for( i=0; i<r; i++)
            for( j=0; j<c ;j++)
          {
            if(result[i][j] == 1)
              System.out.println("("+i +" , " +j +" )");
          }
          return 1;                                              //return status 'success'
       
        }
        /*If status is -1(destination not reached yet) and it is not deadlock condition,
         * then Recursive calls are made to find the path*/ 
        
        if(previous != 'L' && status != 1)                      //previous direction not Left
        {
          result[curR][curC] = 1;                               //updating the path of result matrix
          System.out.println("Turning Right");
          status = findPath(matrix, result, curR, curC+1, direction, 'R', destR, destC);
        }
        if(previous != 'U' && status != 1)                      //previous direction not Up
        {
          result[curR][curC] = 1;
          System.out.println("Turning Bottom");
          status = findPath(matrix, result, curR+1,curC ,direction,'B', destR, destC);
        }
        if(previous != 'R' && status != 1)                       //previous direction not Right
        {
          result[curR][curC] = 1;
          System.out.println("Turning Left");
          status = findPath(matrix, result, curR,curC-1 ,direction,'L', destR, destC);
        }
        if(previous != 'B' && status != 1)                        //previous direction not Bottom
        {
          result[curR][curC] = 1;
          System.out.println("Turning Top");
          status = findPath(matrix, result, curR-1,curC ,direction,'T', destR, destC);
        }
        
      }
    }
    return status;
  }
}
    