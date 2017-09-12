import java.util.Scanner;

public class P4Test
{
  public static void main(String[] args)
  {
    // Boolean matrix definitions

    int A[][] = new int[][]
                {{1, 1, 0, 0, 1},
                 {1, 0, 1, 0, 0},
                 {0, 0, 0, 0, 0},
                 {1, 0, 0, 0, 0},
                 {0, 0, 1, 0, 1}};

    int B[][] = new int[][]
                {{0, 1, 0, 0, 1},
                 {0, 1, 1, 0, 0},
                 {1, 0, 1, 0, 0},
                 {1, 0, 0, 0, 0},
                 {0, 1, 0, 0, 1}};

    int C[][] = new int[][]
                {{0, 1, 0, 0, 0},
                 {0, 0, 1, 0, 0},
                 {0, 0, 0, 1, 0},
                 {1, 0, 0, 0, 1},
                 {0, 1, 0, 0, 0}};

    int D[][] = new int[][]
                {{1, 1, 0, 0, 0, 0},
                 {1, 1, 1, 0, 0, 0},
                 {0, 1, 1, 1, 0, 0},
                 {0, 0, 1, 1, 0, 0},
                 {0, 0, 0, 0, 0, 1},
                 {0, 0, 0, 0, 1, 1}};

    int E[][] = new int[][]
                {{0, 1, 1, 0, 0, 1},
                 {0, 1, 1, 0, 0, 1},
                 {0, 0, 1, 0, 0, 1},
                 {0, 0, 0, 0, 1, 1},
                 {0, 0, 0, 1, 1, 1},
                 {0, 0, 0, 0, 0, 0}};

    int F[][] = new int[][]
    {{0, 0, 0, 0, 1, 0, 1, 0, 0},
     {1, 0, 0, 1, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 1, 0, 0, 0, 0, 1, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int G[][] = new int[][]
    {{0, 0, 0, 1, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {1, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 1, 0, 0, 1, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 1, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    /*int TEST[][] = new int[][] // test for warshall's algorithm
    		 {{0,1,0,0,0},
    		  {0,0,0,0,0},
    		  {0,1,0,1,0},
    		  {0,0,1,1,1},
    		  {1,0,0,0,0}};
    */
    
    // Put code here...   
            
    System.out.println("a. W = (C' AND (A OR B)) AND B' ");
    BMat BMA = new BMat(A);
    BMat BMB = new BMat(B);
    BMat BMC = new BMat(C);
    BMat BMBC = BMB.complement();
    BMat BMCC = BMC.complement();
    BMat BMAB = BMA.join(BMB); 		// A or B
    BMat CCAB = BMCC.meet(BMAB); 	// C' and (A or B)
    BMat CCBB = CCAB.meet(BMBC);	// (C' and (A or B)) and B'
    BMat W = CCBB;
    W.show();
    
    System.out.println("b. W = (B^T * B) AND (C OR C^T)");
  
    BMat BT = BMB.transpose();
    BMat CT = BMC.transpose();
    BMat BTB = BT.product(BMB);
    BMat CCT = BMC.product(CT);
    BMat BTBCCT = BTB.meet(CCT);
    W = BTBCCT;
    W.show();
            
    System.out.println("c. W = C^18");
    BMat C18 = BMC.power(18);		// C to power of 18
    W = C18;
    W.show();
    
    System.out.println("d. W = (D OR E)^T AND (D^T OR E^T)");
    //System.out.print("enter power for T: ");   
    //Scanner sc2 = new Scanner(System.in); 
    //int T2 = sc2.nextInt();
    
    BMat BMD = new BMat(D);
    BMat BME = new BMat(E);
    
    BMat DE = BMD.join(BME); // d or e
    BMat DET = DE.transpose(); // (d or e) to the power of T
    BMat DT = BMD.transpose(); // d to the power of T
    BMat ET = BME.transpose(); // e to the power of T
    BMat DTET = DT.join(ET); //d to the power of T OR e to the power of T
    
    BMat DEDE = DET.meet(DTET); // d or e to the power of T AND....
    W = DEDE;
    W.show();
        
    System.out.println("e. W = D^1 OR D^2 OR D^3 OR D^4");
    //BMat BMD = new BMat(D);
    BMat D1 = BMD.power(1);
    BMat D2 = BMD.power(2);
    BMat D3 = BMD.power(3);
    BMat D4 = BMD.power(4);
    
    BMat D1D2 = D1.join(D2);	// D1 or D2
    BMat D3D4 = D3.join(D4);	// D3 or D4
    
    BMat DD = D1D2.join(D3D4);	//(D1 or D2) or (D3 or D4)
    W = DD;
    W.show();
        
    // max out-degree of all nodes
    int node,max=0;
   
    for (int x=0;x<BMD.SIZE; x++){   //find largest node
    	node = BMD.outdegree(x);
    	if (node > max){
    		max = node;
    	}
    }
    int X = max;
    System.out.println("f. X = maximum out-degree of all nodes in D: " + X);
    BMD.show();
        
    // g. symmetric closure
    BMat DS = BMD.sclosure();
    boolean s1 = BMD.isEqual(DS);
    System.out.println("g. W = symmetric closure of D. Is D symmetric? " + s1);
    W = DS;
    W.show();
    
    // is E transitive?
    BMat BMEP = BME.product(BME);
    BMat BMEJ = BMEP.join(BME);
    boolean s2 = BME.isEqual(BMEJ);
    System.out.println("h. W = transitive closure of E. Is E transitive? " + s2);
    //Warshall's algorithm 
    //show transitive closure
    BMat ETC = BME.tclosure();
    W = ETC; 
    W.show();
    
    // test
    //BMat test1 = new BMat(TEST); 
    //BMat testw = test1.tclosure();
    //testw.show();
    
    //i. 
    BMat BMF = new BMat(F); 
    System.out.println("i. Show that matrix F represents a tree (has a candidate root node and has no cycles): ");
    System.out.println("  1. A tree has 0 cycles................#cycles: " + BMF.trace()); 
    System.out.println("  2. A tree has 1 root...................#roots: " + BMF.rootnode());
    
    boolean bmfr = false;
    if (BMF.rootnode() == 1) {
    	bmfr = true;
    } else bmfr = false;
    
    System.out.println("  3. A root has in-degree 0.  All other nodes have in-degree 1... " + bmfr);
    BMF.show();
    
    //j. 
    BMat BMG = new BMat(G);
    System.out.println("j. Show that matrix G does not represent a tree. ");
    System.out.println("  1. A tree has 0 cycles................#cycles: " + BMG.trace()); 
    System.out.println("  2. A tree has 1 root...................#roots: " + BMG.rootnode());
    
    boolean bmfrr = false;
    if (BMG.rootnode() == 1) {
    	bmfrr = true;
    } else bmfrr = false;
    
    System.out.println("  3. A root has in-degree 0.  All other nodes have in-degree 1... " + bmfrr);
    BMG.show();
  } // end main 
  
} // end class
