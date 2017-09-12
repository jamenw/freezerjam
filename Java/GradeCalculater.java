/*
 * Calculate weighted scores.
 * 
 */
package gradecalculater;

import java.util.Scanner;

/**
 *
 * @author Jamen Wood
 */
public class GradeCalculater {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
      Scanner response = new Scanner(System.in);  
      Scanner response1 = new Scanner(System.in);
      Scanner response2 = new Scanner(System.in);
      Scanner response3 = new Scanner(System.in);
      Scanner response4 = new Scanner(System.in);
      Scanner response5 = new Scanner(System.in);
      
        // declarations
        String lastName;
        String firstName;
        int studentID;
        double assignmentScore;
        double quizScore;
        double midTermScore;
        double finalScore;
        
        double totalScore;
        char grade = 0;
        String loop;
       
        loop = "n";

        
        do {
        
       
        
        System.out.print("Student ID No.: ");
        studentID = response1.nextInt();
        
       
        System.out.print("First Name: ");
        firstName = response2.nextLine();
        
            
        System.out.print("Last Name: ");
        lastName = response3.nextLine();
        
        
        System.out.print("Assignment Score: ");
        assignmentScore = response4.nextDouble();
        
       
        System.out.print("Quiz Score: ");
        quizScore = response.nextDouble();
        
      
        System.out.print("Midterm Score: ");
        midTermScore = response.nextDouble();
        
        System.out.print("Final Score: ");
        finalScore = response.nextDouble();
        
        System.out.println("******************************");
        System.out.println(lastName + "," + firstName);
        System.out.println("Student ID: " + studentID);
        System.out.println("Homework: " + assignmentScore);
        System.out.println("Quizzes: " + quizScore);
        System.out.println("Midterm: " + midTermScore);
        System.out.println("Final: " + finalScore);
                
        assignmentScore = (assignmentScore * .01) * 50;
        quizScore = (quizScore * .01) * 20;
        midTermScore = (midTermScore * .01) * 10;
        finalScore = (finalScore * .01) * 20;
        
        totalScore = assignmentScore + quizScore + midTermScore + finalScore;
        if (totalScore >= 90 && totalScore <= 100) { 
        grade = 'A';
        }  
     
        if (totalScore >= 80 && totalScore < 90)  {
        grade = 'B';
        }  
        
        if (totalScore >= 70 && totalScore < 80)  {
        grade = 'C';
        }  
        
        if (totalScore >= 60 && totalScore < 70)   {
        grade = 'D';
        }  
        
        if (totalScore < 60)  {
        grade = 'E';
        }
        System.out.println("*******************************************");
        System.out.println("Total Score: " + totalScore + "   Grade: " + grade);
        System.out.println("*******************************************");
        System.out.print("Would you like to enter another student (y)es or (n)o? ");
     
        loop = response5.nextLine();
        
        
    }while (loop.equals("y")); // end while
    
        System.out.println("******************************");
        System.out.println("Thank you for being a teacher!");
}
}
