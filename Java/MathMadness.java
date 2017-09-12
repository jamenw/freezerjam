/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mathmadness;

import java.util.*;
/**
 *
 * @author Jamen Wood
 */
public class MathMadness {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

    //scanners
        
    Scanner number1 = new Scanner(System.in);
    Scanner number2 = new Scanner(System.in);
        
    // declarations
    
    int numb1 = 0;
    int numb2 = 0;
    int number = 0;
    
    
    
    
    System.out.print("Enter first number: ");    
    numb1 = number1.nextInt();
    
    System.out.print("Enter second number: ");    
    numb2 = number2.nextInt();
    
    number = added(numb1, numb2);
    System.out.println("Added: " + number);
    number = subtracted(numb1, numb2);
    System.out.println("Subtracted: " + number);
    number = multiplied(numb1, numb2);
    System.out.println("Multiplied: " + number);
    number = divided(numb1, numb2);
    System.out.println("Divided: " + number);
    
    }// end main
    
public static int added(int numb1, int numb2)  {
return numb1 + numb2;
}// ended method     
    
public static int subtracted(int numb1, int numb2)  {
return numb1 - numb2;
}// end method

public static int multiplied(int numb1, int numb2)  {
return numb1 * numb2;    
}// end method
    
public static int divided(int numb1, int numb2)  {
return numb1 / numb2;
}// ended method


    
}// end class
