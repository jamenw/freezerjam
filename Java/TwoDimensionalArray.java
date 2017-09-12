package twodimensionalarray;

public class TwoDimensionalArray {

    public static void main(String[] args) {
        // TODO code application logic here

        // declarations 
        char[][] TTTBoard = new char[3][3];   // tic tac toe board
        
        // fill the board
        
        // length returns the number of rows
        for(int row = 0; row < TTTBoard.length; row++){
                    
            // length now returns the number of columns in row zero
            for(int col = 0; col < TTTBoard[0].length; col++) {
                TTTBoard[row][col] = ' ';
            } // end inner for
        
        } // end outer for
        
        // display the board
        displayBoard(TTTBoard);
        
        // set some values
        TTTBoard[0][0] = 'X';
        TTTBoard[1][1] = 'O';
        TTTBoard[0][2] = 'X';
        TTTBoard[0][1] = 'O';
        
        
        // display the board again
        displayBoard(TTTBoard);
    
    
    } // end main 
    
    public static void displayBoard(char[][] board){
        
                // length returns the number of rows
        for(int row = 0; row < board.length; row++){
                    
            // length now returns the number of columns in row zero
            for(int col = 0; col < board[0].length; col++) {
                System.out.print("[" + board[row][col] + "]");
            } // end inner for
            
            System.out.println();
        
        } // end outer for

            System.out.println("\n");
        
    } // end method
    
    
} // end class
