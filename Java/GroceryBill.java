
package grocerybill;

import java.util.*;

/**
 *
 * @author Jamen Wood
 */
public class GroceryBill {

    public static void main(String[] args) {

        // declarations
        double foodBill = 150.0;
        double nonFoodBill = 50.0;
        double foodSalesTax = .03;
        double nonFoodSalesTax = .0675;
        double totalTax;
        
        totalTax =  (foodBill * foodSalesTax) + 
                    (nonFoodBill + nonFoodSalesTax);
       
        System.out.println("Total Bill is: $" + (foodBill + nonFoodBill));
        System.out.println("Total Tax for your bill is: $" + totalTax);
                
             
    }
}
