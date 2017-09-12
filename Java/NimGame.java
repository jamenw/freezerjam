package nimgame;

import java.util.*;

/**
 *
 * @author Jamen Wood
 */
public class NimGame {
    
    public static void main(String[] args) {
    
    Scanner draw = new Scanner(System.in);    
    double stones = 0;
    double min = 0;
    double max = 0;
    double computerDraw = 0;
    double playerDraw = 0;
    double totalStones;
    boolean ok;
    double num1;
    double num2;
    String winner = "";
    
    
    // set randon number of stones from 15 to 30
    min = 15;
    max = 30;
    
    totalStones = min + (int) Math.random() * (max - min +1);    
    stones = totalStones;
    
    do {
      
    // user draws   
    ok = true;
    
    do { 
    draw.reset();    
    System.out.print("There are " + stones + ". How many would you like? ");
    playerDraw = draw.nextDouble();  
        
    ok = isValidEntry(stones, playerDraw);
    } while (ok == false);
    
    if ((stones - playerDraw) == 0) {
        winner = "Player";
    }
    
    stones = stones - playerDraw;
    
    // computer draws
    
    computerDraw = drawStones(stones);// generates a random number from 1 to 3
    System.out.println("There are " + stones + ". The computer takes " + computerDraw);            
    
    if ((stones - computerDraw) == 0) {
        winner = "Computer";
    }
    
    stones = stones - computerDraw;
    
    
    } while (stones > 0);
    
    
    System.out.print("The winner is: " + winner + "!");
            
    }// end main
    
    
    public static boolean isValidEntry(double num1, double num2) {
// user turn: 1 to 3 stones unless there are less than 3 stones left    
    boolean ok = true;
    
    if (num1 == 2 && num2 > 2) {
    ok = false;
    
    }
    if (num1 == 1 && num2 > 1) {
    ok = false;
    }
    
    if (num2 > 3 || num2 < 1) {
    ok = false;    
    }
    
    return ok;
    
    } // end isValidEntry   
    

    public static double drawStones(double num1)  {
    // computer turn: random number from 1 to 3 stones unless there are less than 3 stones left
    int min = 1, max = 3;
    double computerDraw;
    
    if (num1 == 2) {
    max = 2;
    } 

    if (num1 == 1)  {
    max = 1;
    }

    computerDraw = min + (int) Math.random() * (max - min +1);    
    return computerDraw;
    
    }// end drawStones
   
}// end class
