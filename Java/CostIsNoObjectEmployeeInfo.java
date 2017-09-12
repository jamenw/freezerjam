/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package costisnoobjectemployeeinfo;
import java.util.*;
import java.util.Scanner;

/**
 *
 * @author Jamen Wood
 */
public class CostIsNoObjectEmployeeInfo {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
   
           
 //declarations
        Scanner response = new Scanner(System.in);
        Scanner name = new Scanner(System.in);
        // Scanner
        int employeeID =1;
        String firstName;
        firstName = "";
        String lastName;
        String address;
        int zip =0;
        int hoursPerWeek =0;
        double hourlyRate = 0; // $.$$
        int insurancePlan=0;// 1 or 2
        double netPay=0.0;
        double grossPay =0.0;
        double incomeTax=0.0;
        String incomeRate = "";
        int insurancePrem = 0;
        insurancePrem = 0;
        boolean errorFlag = false;
 
        
        do { // error loop
        errorFlag = false;//reset flag

        // capture responses
       
         //continue to loop as long as the response is not 0
        do {// quit loop
        
        try{
            
        do {
            response.reset();
            System.out.print("Enter Employee ID Number (100 and 999): ");
            employeeID = response.nextInt();
        }   while(employeeID < 100 || employeeID > 999);

        name.reset();
        System.out.print("Enter First Name: ");
        firstName = name.nextLine();
        
        
        
        System.out.print("Enter Last Name: ");
        lastName = name.nextLine();
        
        response = new Scanner (System.in);
        response.reset();
        
        System.out.print("Enter Street Address: ");
        address = response.nextLine();
        
        
         
        do {
            response.reset();
            System.out.print("Enter Zip Code (less than 99999): ");
            zip = response.nextInt();
        } while (zip > 99999);
        
    
        
      do {
          response.reset();
            System.out.print("Enter Hourly Rate ($6 and $25): ");
            hourlyRate = response.nextInt();        
        }  while (hourlyRate <6 || hourlyRate >25);
        
    
                
        do {
            response.reset();
            System.out.print("Enter Number of hours this week (0 and 70): ");
         hourlyRate = response.nextInt();        
        } while (hoursPerWeek <0 || hoursPerWeek >70);
        
        do { 
            response.reset();
            System.out.print("Enter Insurance Plan Code (1 or 2): ");
            insurancePlan = response.nextInt();        
        }  while (insurancePlan < 1 || insurancePlan > 2);

         if (insurancePlan == 1) {
            insurancePrem = 60;
        }
        
        if (insurancePlan == 2)  {   
            insurancePrem = 100;
        }
        // figure grossPay & netPay
        
        grossPay = hoursPerWeek * hourlyRate;
        
        if (grossPay <= 400){
         incomeTax = grossPay * .15;   
         incomeRate = "15%";        
        }else { incomeTax = grossPay * .20;
                incomeRate = "20%";
        }
        
         netPay = grossPay - incomeTax - insurancePrem;
          if (netPay < 0) {
            netPay = 0;
        }
         
        
        System.out.println("Gross Pay: " + grossPay);
        System.out.println("Income Tax Rate: " + incomeRate);
        System.out.println("Income Tax: " + incomeTax);
        System.out.println("Insurance Premium: " + insurancePrem);
        System.out.println("Net Pay: " + netPay);
                
      
        
        }  catch(InputMismatchException error) {
            System.err.println("Invalid input");  
            errorFlag = true;
            response = new Scanner (System.in);
            name = new Scanner (System.in);
            
            
        }// end catch
        
        } while (employeeID != 0);//end while
        
        } while (errorFlag == true );
    
        
    }//end main
    
}// end class


       