import java.util.*;

public class input {

    public static void main(String args[]){

        String theString;
        int theInteger;
        float theFloat;

        Scanner console = new Scanner(System.in);

        try{

            System.out.println("Introduce string");
            theString = console.nextLine();
            System.out.println("Ai introdus: " + theString);

            System.out.println("Introduce intreg");
            theInteger = console.nextInt();
            System.out.println("Ai introdus: " + theInteger);

            System.out.println("Introduce float");
            theFloat = console.nextFloat();
            System.out.println("Ai introdus: " + theFloat);
        }catch (InputMismatchException exp){

            System.out.println("Erroare");
        }

    }

}