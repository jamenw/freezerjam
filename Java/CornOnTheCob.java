

package cornonthecob;

import java.util.Scanner;

public class CornOnTheCob {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

    //declarations
        Scanner response = new Scanner(System.in);
        int rows, ears;
        
        //prompt for the number of rows planted
        System.out.println("How many rows of corn did you plant?");
        rows= response.nextInt();
        
        // // calculate the number of ears expected
        ears = CalculateCorn(rows);
        
        
        // print the results
        
        System.out.println("You have " + ears + " ears of corn");
    
    
    }//end main method
    
    // calculate the number of ears expected
    
    public static int CalculateCorn(int row) {
    int earsOfCorn;
    
    earsOfCorn = row * 3 * 18;
    
    
    return earsOfCorn;
    
    }// end method
    
    
}// end class
