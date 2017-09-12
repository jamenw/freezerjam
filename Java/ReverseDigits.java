import java.util.Scanner;
public class ReverseDigits {
	
		  public static void main(String args[])
		  {
		    
			  Scanner sc = new Scanner(System.in);
			  long X = sc.nextInt();   
			  long Y;
		      if(X >= 1)
		      {
		        Y = ReverseDigits(X);
		        System.out.println("\n X = " + X + "     Y = " + Y);
		      }
		    
		    sc.close();
		    return;
		  } // end main

		  public static long ReverseDigits(long x)
		  {
		   long y = 0;
		   // ...put code here...
		   while (x != 0)
		    {
		        y = y*10 + x%10;
		        x /= 10;
		    }
		    return y;
		  }
		} // end class
