import java.util.Scanner;


public class Fibonacci {

	public static void main(String[] args) {
		 
	int counter, firstNumber = 0, secondNumber = 1, next;
		  
	System.out.print("Number of Fibonacci numbers: ");
		   
	Scanner sc = new Scanner(System.in);
	int number = sc.nextInt(); 
		 
	System.out.print("\nFirst " + number + " numbers are: ");
		 
		for ( counter = 0 ; counter < number ; counter++ )
		{
			if ( counter <= 1 ) {
			next = counter;
			} else
			    {
				next = firstNumber + secondNumber;
			    firstNumber = secondNumber;
			    secondNumber = next;
			    }
			    
		System.out.print(next + " ");
		
		}
		sc.close();
		return;
	}// end of main
}// end of class