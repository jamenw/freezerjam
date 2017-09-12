import java.util.Scanner;
public class SumOfDiv
{
	  public static void main(String args[])
	  {
	    
		  Scanner sc = new Scanner(System.in);
		  long X = sc.nextInt();  
		  
		  long Y;
	      if(X >= 1)
	      {
	        Y = SumOfDivisors(X);
	        System.out.println("\n X = " + X + "     Y = " + Y);
	      }
	    
	    sc.close();
	    return;
	  } // end main

	  public static long SumOfDivisors(long x)
	  {
	    long y = 0;
	    
	    // ...put code here...
	    int i;
	    for (i=1; i<=x; i++)
	    {
	        if (x%i == 0) 
	        {
	            y = y + i;
	        }
	    }
	     
	    return y;
	  }
	} // end class