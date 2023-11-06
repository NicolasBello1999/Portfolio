import java.io.*;
import java.util.*;

class handlingFiles {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        employeeRepo repo = new employeeRepo();
        BufferedReader file = null;
        int input = 0;
        
        System.out.print("Enter file name to either open or create: ");
        String filename = keyboard.nextLine();

        do {
            try {
                file = openFile(filename);
                menu();
                input = keyboard.nextInt();
                
                if (input == 1) {

                } else if (input == 2) {

                } else if (input == 3) {

                } else if (input == 4) {

                } else if (input == 5) {
                    System.out.println("Exiting program...");
                }
            } catch (IOException e) {
                System.err.printf("Error opening {%s} - No such file exists...\n", filename);
            } catch (InputMismatchException e) {
                System.err.printf("Invalid input detected - ERROR - {%s}\n", e);
            }
        } while (input != 5);
    }

    public static BufferedReader openFile(String filename) throws IOException {
        File file = new File(filename);

        if (!file.exists()) // if file doesn't exist, create new file
            file.createNewFile();

        BufferedReader openfile = new BufferedReader(new FileReader(file));
        return openfile;
    }

    public static void menu() {
        System.out.println("\nList of options:");
        System.out.println("1. Create an employee.");
        System.out.println("2. Delete an employee.");
        System.out.println("3. Display employees by department.");
        System.out.println("4. Display employee information.");
        System.out.println("5. Exit program.");
        System.out.print("Enter option: ");
    }

    public static void createEmployee() {
        employee obj = new employee();
        obj.getEmployeeID();
    }
}