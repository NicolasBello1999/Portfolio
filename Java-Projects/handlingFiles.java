import java.io.*;
import java.util.*;

class handlingFiles {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        BufferedReader readFile = null;
        
        System.out.print("Enter file name to either open or create: ");
        String filename = keyboard.nextLine();

        try {
            readFile = openFile(filename);
        } catch (IOException e) {
            System.err.printf("Error opening {%s} - No such file exists...", filename);
        }
    }

    public static BufferedReader openFile(String filename) throws IOException {
        File file = new File(filename);

        if (!file.exists()) { // if file doesn't exist, we throw an error
            throw new IOException();
        }

        BufferedReader openfile = new BufferedReader(new FileReader(file));
        return openfile;
    }
}