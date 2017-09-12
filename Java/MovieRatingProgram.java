
package movie.rating.program;

import java.util.*;


public class MovieRatingProgram {

    public static void main(String[] args) {
       
    //declarations
        Scanner response = new Scanner(System.in);
        Scanner name = new Scanner(System.in);
        // Scanner
        double movieRating = 0;
        double counter = 0;
        double total = 0;
        double average = 0;
        String movie;
        boolean errorFlag = false;
        boolean quit = false;
        int inputCounter = 0;
        
         // capture responses
        System.out.print("Enter the movie of the week: ");
        movie = name.nextLine();
       
        while (quit == false) {
       
        do {    
        errorFlag = false;//reset flag
        movieRating = 0;//reset
      
        
            try{
            
            System.out.print("Enter your movie rating 0 to 4 (minus number to quit): ");    
            movieRating = response.nextDouble();
            
            if (movieRating < 0) {
                quit = true;
            }

            if (movieRating > 4){
            inputCounter = inputCounter + 1; 
            while (inputCounter == 3) {
                System.out.println("**************************");
                System.out.println("Enter the next rating: ");
                System.out.println();
                inputCounter = 0;
            }
            System.err.println("Invalid input");  
            System.out.println("Movie rating must be between 0 to 4: ");      
           
            }
            
            if (movieRating >= 0 && movieRating <= 4) {
            counter = counter + 1;
            total = total + movieRating;
            } 
            
            }// end try
           
            catch(InputMismatchException error) {
            System.err.println("Invalid input");   
            errorFlag =true;
            inputCounter = inputCounter + 1;
              while (inputCounter == 3) {
                System.out.println("**************************");
                System.out.println("Enter the next rating: ");
                System.out.println();
                inputCounter = 0;
            }
            response = new Scanner (System.in);// reset input buffer

            System.out.println("Movie rating must be between 0 to 4");      
            }// end catch
            
         
            
        } while (errorFlag == true ) ;
     
       
    }// end while
        
        average = total / counter;
        System.out.println("The movie of the week is: " + movie);
        System.out.println("Number of ratings: " + counter);
        System.out.println("Ratings total: " + total);
        System.out.println("Average rating of: " + average);
  
    }//end main
    
}// end class