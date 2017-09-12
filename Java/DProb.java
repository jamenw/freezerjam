import java.util.Scanner; 
import java.math.*;

  
//Discrete Probability Library  
public class DProb  
{  
        
    public static void main(String[] args) {  
            
        System.out.print("N total number: ");    
        Scanner sc1 = new Scanner(System.in);  
        long n = sc1.nextLong();   
                 
        System.out.print("\nX objects number: ");  
        Scanner sc2 = new Scanner(System.in);  
        long x = sc2.nextLong();   
          
        System.out.print("\nP number (binomial): ");  
        Scanner sc3 = new Scanner(System.in);  
        double p = sc3.nextDouble();  
          
        System.out.print("\nNp population: ");  
        Scanner sc4 = new Scanner(System.in);  
        long Np = sc4.nextLong();  
          
        System.out.print("\nXp population: ");  
        Scanner sc5 = new Scanner(System.in);  
        long Xp = sc5.nextLong();  
          
        System.out.print("\nN sample: ");  
        Scanner sc6 = new Scanner(System.in);  
        long N = sc6.nextLong();  
          
        System.out.print("\nX sample: ");  
        Scanner sc7 = new Scanner(System.in);  
        long X = sc7.nextLong(); 
      
        
        System.out.print("\nXmean number: ");  
        Scanner sc8 = new Scanner(System.in);  
        double xm = sc8.nextDouble();      
          
        System.out.print("\nto the power: ");  
        Scanner sc9 = new Scanner(System.in);  
        long po = sc9.nextLong();  
                  
        System.out.println("Test: N to the Power = " + Power(n,po)); 
        System.out.println("Output is: ");       
        System.out.println("Permutations = " + Permutations(n,x));  
        System.out.println("Combinations = " + Combinations(n,x));  
        System.out.println("HyperGeometric = " + HyperGeometric(Np, Xp, N, X));  
        System.out.println("Binomial = " + Binomial(p,n,x)); 
        System.out.println("Poisson = " + Poisson(xm,x));  
            
        sc1.close();  
        sc2.close();  
        sc3.close(); 
        sc4.close(); 
        sc5.close(); 
        sc6.close(); 
        sc7.close(); 
        sc8.close(); 
        sc9.close();        
          
        return;  
    }// end of main  
  
 // number to the power method 
public static double Power(double num, long pow) 
{ 
    double power = 1; 
    for(long c = 0; c < pow; c++){ 
    power *= num; 
    } 
    return power; 
      
} 
      
      
public static double Permutations(long N, long X)  
{  
//number of ways X objects can be drawn from N objects in a particular order     
 double perm = 1.0;  
     
 for(long i = 0; i < X ; i++) {  
     perm = perm * (double)(N-i);     
 }  
     
 return perm;  
}  
    
public static double Combinations(long N, long X)  
{  
//number of ways X objects can be drawn from N objects in any order    
// N = total number 
// X = objects  
if (X == 0 || X == N) {  
    return 1.0;  
}  
    
double comb = 1.0;  
    
if ( (N - X) < X) {  
    X = N - X;  
}  
        for (long i = 0; i < X; i++){  
        comb = comb * (double)(N - i) / (i+1);  
        }     
        
return comb;  
}  
    
public static double HyperGeometric(long Np, long Xp, long N, long X)  
{  
 double  hg = 0;  
 
 hg = (double) ((Combinations(Xp,X) * Combinations(Np-Xp,N-X)) / Combinations(Np,N));   
 return hg;  
}  
  
  
  
public static double Binomial(double P, long N, long X)  
{  
 double b = 0.0;  
 
// nCx * P^x * (1-P)^n-x   
b = (double) Combinations(N,X) * Power(P,X) * Power((1-P),(N-X)); 
 
 return b;  
}  
    
public static double Poisson(double R, long X)  
{  
 double p = 0.0;  
 double e = 2.71828183; 
 // p = e^-R * R^X/X!
 double fX = 1;
 
 for (long f = 1; f <= X; f++ ) {
	 fX = f * fX;
	 System.out.println(fX);
 }
  
 p = Math.exp(-R) * Power(R,X)/fX;
 System.out.println("fX = " + fX); 
 
 return p;  
}  
    
} // end class