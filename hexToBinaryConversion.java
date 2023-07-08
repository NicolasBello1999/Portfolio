/* Very simple program that converts hexadecimal values (read from a file) into binary and then into decimal */

import java.util.*;
import java.io.*;

class hexToBinaryConversion {
    public static void main(String[] args) {
        try {
            File fileObj = new File("something.txt");
            Scanner keyboard = new Scanner(fileObj);

            while (keyboard.hasNextLine())
                hexConvertToBinary(keyboard.nextLine());
            
            keyboard.close();
        } catch (Exception error) {
            System.out.printf("System error occurred : %s\n", error);
        }
    }
    
    public static String convertToBinary(int num) {
        int temp;
        String binaryForm = "";
        
        while (num > 0) {
            temp = num % 2;
            num /= 2;
            binaryForm = binaryForm.concat(Integer.toString(temp));
        }

        return binaryForm;
    }

    public static void hexConvertToBinary(String hex) {
        String binary = "";

        for (char c : hex.toCharArray()) {
            if (c == '0')
                binary += "0000";
            else if (c == '1')
                binary += "0001";
            else if (c == '2')
                binary += "0010";
            else if (c == '3')
                binary += "0011";
            else if (c == '4')
                binary += "0100";
            else if (c == '5')
                binary += "0101";
            else if (c == '6')
                binary += "0110";
            else if (c == '7')
                binary += "0111";
            else if (c == '8')
                binary += "1000";
            else if (c == '9')
                binary += "1001";
            else if (c == 'A')
                binary += "1010";
            else if (c == 'B')
                binary += "1011";
            else if (c == 'C')
                binary += "1100";
            else if (c == 'D')
                binary += "1101";
            else if (c == 'E')
                binary += "1110";
            else if (c == 'F')
                binary += "1111";
        }

        System.out.printf("Hex value : %s\n", hex);
        System.out.printf("Binary value : %s\n", binary);
        binaryConvertToDecimal(binary);
    }

    public static void binaryConvertToDecimal(String binary) {
        long decimal = 0, mult = 1;
        char[] arrBin = binary.toCharArray();
        int i;

        for (i = arrBin.length - 1; i >= 0; i--) {
            if (arrBin[i] == '1')
                decimal += mult;
            mult *= 2;
        }

        // can also use this expression
        /*
        for (i = arrBin.length - 1; i >= 0; i--) {
            decimal += (arrBin[i] - '0') * Math.pow(2, arrBin.length - 1 - i);
        }
        */

        System.out.printf("Decimal value : %d\n\n", decimal);
    }
}