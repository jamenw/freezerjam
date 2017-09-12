// Test Finite State Machine Class
public class TestFSM
{
  public static void main(String[] args)
  {
     
    String A1 = "ab";
    int[][] ST1 =  {{1,5},
    				{2,3},
    				{1,5},
    				{4,6},
    				{3,6},
    				{7,6},
    				{6,6},
    				{5,6}};
    int[]AS1 = {0,0,0,1,0,0,0,1};
    
    String A2 = "01";
    int[][] ST2 =  {{1,5},
    				{2,6},
    				{3,7},
    				{4,8},
    				{4,4},
    				{6,9},
    				{7,9},
    				{8,8},
    				{8,8},
    				{9,9}};
    int[]AS2 = {0,1,1,1,0,0,0,1,0,0};
    
    String A3 = "xyz";
    int[][] ST3 =  {{1,0,4},
    				{1,2,4},
    				{3,1,4},
    				{3,3,4},
    				{1,5,4},
    				{1,4,6},
    				{1,6,6}};
    int[]AS3 = {0,0,0,1,0,0,1};	
    
    String A4 = "pqr";
    int[][] ST4 =  {{4,0,1},
					{4,2,1},
					{4,0,3},
					{3,3,3},
					{5,0,1},
					{5,0,1}};
    int[] AS4 = {0,0,0,1,0,1};
    
    String inString1a, inString1b, inString1c, inString1d, inString1e;
    String inString2a, inString2b, inString2c, inString2d, inString2e;
    String inString3a, inString3b, inString3c, inString3d, inString3e;
    String inString4a, inString4b, inString4c, inString4d, inString4e;
    
    boolean accept1a = false;
    boolean accept1b = false;
    boolean accept1c = false;
    boolean accept1d = false;
    boolean accept1e = false;
    
    boolean accept2a = false;
    boolean accept2b = false;
    boolean accept2c = false;
    boolean accept2d = false;
    boolean accept2e = false;
    
    boolean accept3a = false;
    boolean accept3b = false;
    boolean accept3c = false;
    boolean accept3d = false;
    boolean accept3e = false;
         
    boolean accept4a = false;
    boolean accept4b = false;
    boolean accept4c = false;
    boolean accept4d = false;
    boolean accept4e = false;
        
    FSM L1 = new FSM(A1, ST1, AS1);	
    FSM L2 = new FSM(A2, ST2, AS2);	
    FSM L3 = new FSM(A3, ST3, AS3);	
    FSM L4 = new FSM(A4, ST4, AS4);	
   
      inString1a = "aabaaaa";
      inString1b = "aaabaaaa";
      inString1c = "aabaaaab";
      inString1d = "baaaaaa";
      inString1e = "aaaaabaa";
      
      inString2a = "10";
      inString2b = "00";
      inString2c = "010";
      inString2d = "101";
      inString2e = "0100";
      
      inString3a = "xyzyzyzy";
      inString3b = "xzzxzxyy";
      inString3c = "yzxyzyyz";
      inString3d = "zzyzxyxx";
      inString3e = "yxzxxyzy";
      
      inString4a = "qqpprqrr";
      inString4b = "pqrprppq";
      inString4c = "rpqrrqpp";
      inString4d = "pqpprpqq";
      inString4e = "qrpprqrp";
      
      accept1a = L1.validString(inString1a);
      accept1b = L1.validString(inString1b);
      accept1c = L1.validString(inString1c);
      accept1d = L1.validString(inString1d);
      accept1e = L1.validString(inString1e);
      
      accept2a = L2.validString(inString2a);
      accept2b = L2.validString(inString2b);
      accept2c = L2.validString(inString2c);
      accept2d = L2.validString(inString2d);
      accept2e = L2.validString(inString2e);
      
      accept3a = L3.validString(inString3a);
      accept3b = L3.validString(inString3b);
      accept3c = L3.validString(inString3c);
      accept3d = L3.validString(inString3d);
      accept3e = L3.validString(inString3e);
           
      accept4a = L4.validString(inString4a);
      accept4b = L4.validString(inString4b);
      accept4c = L4.validString(inString4c);
      accept4d = L4.validString(inString4d);
      accept4e = L4.validString(inString4e);
      
      System.out.println("String: " + inString1a + "   Accept?  " + accept1a);
      System.out.println("String: " + inString1b + "   Accept?  " + accept1b);
      System.out.println("String: " + inString1c + "   Accept?  " + accept1c);
      System.out.println("String: " + inString1d + "   Accept?  " + accept1d);
      System.out.println("String: " + inString1e + "   Accept?  " + accept1e);
      System.out.println();
      System.out.println("String: " + inString2a + "   Accept?  " + accept2a);	
      System.out.println("String: " + inString2b + "   Accept?  " + accept2b);
      System.out.println("String: " + inString2c + "   Accept?  " + accept2c);
      System.out.println("String: " + inString2d + "   Accept?  " + accept2d);
      System.out.println("String: " + inString2e + "   Accept?  " + accept2e);
      System.out.println();
      System.out.println("String: " + inString3a + "   Accept?  " + accept3a);
      System.out.println("String: " + inString3b + "   Accept?  " + accept3b);
      System.out.println("String: " + inString3c + "   Accept?  " + accept3c);
      System.out.println("String: " + inString3d + "   Accept?  " + accept3d);
      System.out.println("String: " + inString3e + "   Accept?  " + accept3e);
      System.out.println();
      System.out.println("String: " + inString4a + "   Accept?  " + accept4a);
      System.out.println("String: " + inString4b + "   Accept?  " + accept4b);
      System.out.println("String: " + inString4c + "   Accept?  " + accept4c);
      System.out.println("String: " + inString4d + "   Accept?  " + accept4d);
      System.out.println("String: " + inString4e + "   Accept?  " + accept4e);
     
  } // end main

} // end class
