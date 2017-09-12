
package finalproject1400;

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 *
 * @author Jamen Wood
 */
public class FinalProject1400 {

    public static void main(String[] args) {
     
      //declarations
       
        int rentalAgreementNumber;
        boolean errorFlag;
        int x = 0;
        double subTotal, total, tax;
        
        int [] carID = {1,2,3,4,5,6,7,8,9,10};
        String [] make = {"Honda","Ford","Suzuki","Chevy","Datsun","VW","Pontiac","Buick","Mercury","Geo"};
        String [] model = {"Civic","Pinto","Sprint","Vega","B210","Bus","Wagon","Regal","Capri","Metro"};
        int [] year = {1980,1977,1989,1981,1985,1982,1975,1991,1985,1995};
        double [] dailyFee = {20.00,5.00,12.00,13.50,11.50,9.99,5.00,15.00,13.50,10.50};
        String carInfo = null;
        
        String phoneNumber = null, emailAddress = null, paymentType = null;
        String cardNumber = null;
        String custInfo;
        
        int idNumber = 0;
        String firstName = null, lastName = null;
        String streetAddress = null, city = null, state = null, zip = null;
        String personInfo;
        
        String hireDate;
        double hourlyPayRate = 0;
        String agentName = null;
        int insuranceInput = 0;
        String insuranceMark = null;
        
        int month = 0, day = 0, yr = 0;
        int rentalDays = 0;
        
        Scanner response = new Scanner(System.in);
        Scanner response1 = new Scanner(System.in);
        Scanner response2 = new Scanner(System.in);
        Scanner response3 = new Scanner(System.in);
        Scanner response4 = new Scanner(System.in);
        Scanner response5 = new Scanner(System.in);
        Scanner response6 = new Scanner(System.in);
        Scanner response7 = new Scanner(System.in);
        Scanner response8 = new Scanner(System.in);
        Scanner response9 = new Scanner(System.in);
        Scanner response10 = new Scanner(System.in);
        Scanner response11 = new Scanner(System.in);
        Scanner response12 = new Scanner(System.in);
        
       // print menu
         
            System.out.println("WELCOME TO CHEAP BEATER CAR RENTAL... ");
            System.out.println("where we can't be beat!!!!");
            System.out.println("ID#  Make     Model    Year    Rate/Day");
            System.out.println("---------------------------------------");
            System.out.println("1    Honda    Civic    1980    $20.00");
            System.out.println("2    Ford     Pinto    1977     $5.00");
            System.out.println("3    Chevy    Sprint   1989    $12.00");
            System.out.println("4    Chevy    Vega     1981    $13.50");
            System.out.println("5    Datsus   B210     1985    $11.50");
            System.out.println("6    VW       Bus      1982     $9.99");
            System.out.println("7    Pontiac  Wagon    1975     $5.00");
            System.out.println("8    Buick    Regal    1991    $15.00");
            System.out.println("9    Mercury  Capri    1985    $13.50");
            System.out.println("10   Geo      Metro    1995    $10.50");
            System.out.println("---------------------------------------");
           
        do { // error loop
        errorFlag = false;//reset flag
        try{ 
            
            do { 
            System.out.print("Enter Car Code (1 - 10): ");
            response.reset();
            x = response.nextInt();
            }  while(x <1 || x > 10);
            x=x -1;
            carInfo = "       ID#: " + carID[x] + "\n";
            carInfo += "      Make: " + make[x]  + "\n";
            carInfo += "     Model: " + model[x] + "\n";
            carInfo += "      Year: " + year[x]  + "\n";
            carInfo += "Daily Rate: " + dailyFee[x];
            
            System.out.println(carInfo);
            
            System.out.print("Enter # of days for rental: ");
            rentalDays = response.nextInt();
            
            do  {
            System.out.print("Insurance? 1-yes  2-no: ");
            response.reset();
            insuranceInput = response.nextInt();
            } while (insuranceInput < 1 || insuranceInput > 2);
                    
            do  {
            System.out.print("Enter date-- (1-12) Month: ");
            month = response.nextInt();
            }  while (month < 1 || month > 12);
                        
            if (month == 1 ||  month == 3 ||
                month == 5 ||  month == 7 ||
                month == 8 ||  month == 10 ||
                month == 12) {
            
            do{
            System.out.print("Enter date-- (1-31) Day: ");
            day = response.nextInt();
            } while (day < 1 || day > 31);
            }// end if
            
            if (month == 2) {
            do {
            System.out.print("Enter date--(1-28) Day: ");
            day = response.nextInt();
            } while (day < 1 || day > 28);
            }// end if
            
            if (month == 4 || month == 6 ||
                month == 7 || month == 9 ||
                month == 11) {
              do{
            System.out.print("Enter date-- (1-30) Day: ");
            day = response.nextInt();
            } while (day < 1 || day > 30);  
            }// end if
            
            System.out.print("Enter date-- Year: ");
            yr = response.nextInt();
            
            do {
            System.out.print("Enter Customer's I.D. Number (1 to 999): ");
            idNumber = response.nextInt();    
            } while (idNumber < 1 || idNumber > 999);

            System.out.print("Enter First Name: ");
            firstName = response1.nextLine();

            System.out.print("Enter Last Name: ");
            lastName = response2.nextLine();

            System.out.print("Enter Street Address: ");
            streetAddress = response3.nextLine();

            System.out.print("Enter City: ");
            city = response4.nextLine();

            System.out.print("Enter State: ");
            state = response5.nextLine();

            do {
            System.out.print("Enter Zip (5 digits): ");
            zip = response6.nextLine();
            } while (zip.length() != 5);
           
            do {     
            System.out.print("Enter Phone Number (xxx-xxx-xxxx): ");
            phoneNumber = response7.nextLine();    
            } while (phoneNumber.length() != 12);

            do  {
            System.out.print("Enter Email Address: ");
            emailAddress = response8.nextLine();
            } while (emailAddress.contains(".") == false || emailAddress.contains("@") == false);

            System.out.print("Enter Payment Type: ");
            paymentType = response9.nextLine();

            do  {
            System.out.print("Enter Card Number (16 digit or 19 digit with 3 spaces: ");
            cardNumber = response10.nextLine();
            } while (cardNumber.length() != 16 || 
            (cardNumber.length() != 19 && cardNumber.contains(" ")));
           
            
            //System.out.print("Enter Employee Hire Date: ");
            //hireDate = response.nextLine();

            System.out.print("Enter Employee Agent Name: ");
            agentName = response11.nextLine();

            System.out.print("Enter Hourly Pay Rate: ");
            hourlyPayRate = response12.nextDouble();
            
       }  catch(InputMismatchException error) {
       System.err.println("Invalid input");  
       errorFlag = true;
       response = new Scanner (System.in);
       response1 = new Scanner(System.in);
       response2 = new Scanner(System.in);
       response3 = new Scanner(System.in);
       response4 = new Scanner(System.in);
       response5 = new Scanner(System.in);
       response6 = new Scanner(System.in);
       response7 = new Scanner(System.in);
       response8 = new Scanner(System.in);
       response9 = new Scanner(System.in);
       response10 = new Scanner(System.in);
       response11 = new Scanner(System.in);
       response12 = new Scanner(System.in);
       
       
       }// end catch
        
       } while (errorFlag == true );
        
        // random rental agreement number from 999 to 9999
        int min = 999;// random generator min
        int max = 9999;// random generator max
        rentalAgreementNumber = min + (int) Math.random() * (max - min +1);  
                
        custInfo  = " Phone Number: " + phoneNumber + "\n";
        custInfo += "Email Address: " + emailAddress + "\n";
        custInfo += " Payment Type: " + paymentType;

        personInfo  = "     ID Number: " + idNumber + "\n";
        personInfo += "          Name: " + firstName + " " + lastName + "\n";
        personInfo += "       Address: " + streetAddress + "\n";
        personInfo += "City,State,Zip: " + city + ", " + state + "  " + zip;
        
        if (insuranceInput == 1) {
            insuranceMark = "YES";
        } else insuranceMark = "NO";
        
        
        // print out invoice
        System.out.println("*********************************************************");
        System.out.println("*   ------  R E N T A L   A G R E E M E N T   --------  *");
        System.out.println("*********************************************************");
        System.out.println();
        System.out.println("Rental Agreement No. " + rentalAgreementNumber);
        System.out.println();
        System.out.println("Car Rental:                              Date: " + month + "/" + day + "/" + yr);
        System.out.println(carInfo);
        System.out.println();
        System.out.println("Customer:                      Employee Agent: " + agentName);
        System.out.println(personInfo);
        System.out.println("                                    Insurance: " + insuranceMark);
        System.out.println(custInfo);
        System.out.println();
        System.out.println("DESCRIPTION                              AMOUNT");
        System.out.println("---------------------------------------------------------");
        System.out.println("Daily Rate of $" + dailyFee[x] + " @ " + rentalDays + " days =");
        System.out.println("                                         $ " + dailyFee[x] * rentalDays);
        System.out.println("Sir Charge                               $ " + hourlyPayRate);
        subTotal = (dailyFee[x] * rentalDays) + hourlyPayRate;
        System.out.println();
        System.out.println("SUB-TOTAL                                $ " + subTotal);
        tax = .06 * subTotal;
        System.out.println("SALES TAX 6%                             $ " + tax);
        System.out.println();
        total = subTotal + tax;
        System.out.println("TOTAL                                    $ " + total);
        System.out.println("---------------------------------------------------------");
    }
}
