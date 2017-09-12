
// Program to calculate the sum of squared integers
// using 3 algorithms.
import java.util.Scanner;
public class P1PartA
{
  public static void main(String args[])
  {
	  
	  Scanner sc = new Scanner(System.in);
	  int x = sc.nextInt();
	  
	  int y1, y2, y3;
	  	  
	  //if(args.length >= 1){
      //x = Integer.parseInt(args[0]);
      System.out.println("\n Input value       x = " + x);
      if (x >= 1){
        // Sum-of squares algorithm
        y1 = f1(x);
        System.out.println(" Sum-of-squares   y1 = " + y1);
        // Divide-last algorithm
        y2 = f2(x);
        System.out.println(" Divide-last      y2 = " + y2);
        // Divide-early algorithm
        y3 = f3(x);
        System.out.println(" Divide-early     y3 = " + y3);
      //}
    }
	sc.close();
    return;
  } // end main

  private static int f1(int x)
  {
    // Sum-of-squares algorithm
    int y = 0;
    for (int k = 1; k <= x; k++){
      y = y + k*k;
    }
    return y;
  }

  private static int f2(int x)
  {
    // Divide-last algorithm
    int y = 0;
    y = x*(x + 1)*(2*x + 1)/6;
    return y;
  }

  private static int f3(int x)
  {
    // Divide-early algorithm
    int y = 0;
    int A = x*(x+1)/2;
    int B = 2*x + 1;
    if(A % 3 == 0)
      y = (A/3)*B;
    else
      y = A*(B/3);
    return y;
  }

} // end class