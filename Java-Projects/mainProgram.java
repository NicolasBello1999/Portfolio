import java.io.*;
import java.util.*;

class mainProgram {
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
                
                if (input == 1) { // create employee
                    createEmployee(keyboard, repo);
                } else if (input == 2) { // delete employee

                } else if (input == 3) { // display employees by department

                } else if (input == 4) { // display employee information

                } else if (input == 5) { // close program
                    System.out.println("Exiting program...");
                    file.close();
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

    public static void createEmployee(Scanner keyboard, employeeRepo repo) {
        employee new_emp = new employee();

        try {
            System.out.print("Enter employee's name: ");
            new_emp.setEmployeeName(keyboard.nextLine());

            System.out.print("Enter employee's ID: ");
            new_emp.setEmployeeID(keyboard.nextLine());

            System.out.print("Enter employee's hours: ");
            String hours = keyboard.nextLine();
            new_emp.setHours(Integer.parseInt(hours));

            System.out.print("Enter employee's current wage: ");
            String wage = keyboard.nextLine();
            new_emp.setWage(Integer.parseInt(wage));

            new_emp.setSalary();

            repo.addToList(new_emp);
        } catch (Exception e) {
            System.err.printf("Invalid input detected - ERROR - {%s}\n", e);
            createEmployee(keyboard, repo);
        }
    }

    public static void displayEmployee(Scanner keyboard, employeeRepo repo) {
        try {
            System.out.printf("Enter employee's name: ");
            String name = keyboard.nextLine();

            System.out.printf("Enter employee's id: ");
            String id = keyboard.nextLine();

            employee curEmp = repo.searchEmployee(id, name);

            if (curEmp == null)
                System.out.printf("\nThere is no employee with the given ID or Name.\n");
            else
                curEmp.displayInfo();
        } catch (Exception e) {

        }
    }
}