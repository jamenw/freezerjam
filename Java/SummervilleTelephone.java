/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package summervilletelephone;

import java.util.Scanner;

/**
 *
 * @author Jamen Wood
 */
public class SummervilleTelephone {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
         // scanner
     Scanner response = new Scanner(System.in);

        // declarations
        int customerAreaCode = 0;
        int customerPhoneNumb = 0;
        int calledAreaCode = 0;
        int calledPhoneNumb = 0;
        int minutes = 0;
        double pricePerMinute = 0.00;
        double price = 0.00;
        
        // capture responses of phone numbers and minutes
        // 10 cents per minute for all calls outside the area code that last over 20 minutes
        // all other calls are 13 cents per minute
        // discount at 10% for calls over $10


                System.out.print("Enter customer area code: ");    
                customerAreaCode = response.nextInt();
                
                System.out.print("Enter customer phone number: ");    
                customerPhoneNumb = response.nextInt();

                System.out.print("Enter called area code: ");    
                calledAreaCode = response.nextInt();

                System.out.print("Enter called phone number: ");    
                calledPhoneNumb = response.nextInt();
            
                System.out.print("Enter minutes: ");    
                minutes = response.nextInt();        
        
        // all other calls per minute
        pricePerMinute = 0.13;
        
        // 10 cents per minute
        if ((customerAreaCode != calledAreaCode) && (minutes > 20)) {
        pricePerMinute = 0.10;    
        }
         // total price
        price = pricePerMinute * minutes;
        
        // 10 % discount?
        
        if (price > 10) {
            price = price * .9;
            System.out.println("10% discount!");
        }
       
        // display output
        System.out.println("Calling number: (" + customerAreaCode + ")" + customerPhoneNumb);
        System.out.println("Called number:  (" + calledAreaCode + ")" + calledPhoneNumb);
        System.out.println("Price for the call: " + price);  
      
        
    }// end main
}// end class
