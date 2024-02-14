import java.util.ArrayList;

public class employeeRepo {
    private ArrayList<employee> listsOfEmployees;

    // create new repo when creating an object of employeeRepo
    public employeeRepo() {
        listsOfEmployees = new ArrayList<employee>();
    }

    public void addToList(employee emp) { listsOfEmployees.add(emp); }

    public void sortListOfEmployees() {

    }

    /**
    * <p> This method will search through the list of employee's using binary search and then display the corresponding
    * information of the employee. <p>
    * @function    searchEmployee(String id, String name)
    * @param       id    ID of the employee that you want to display.
    * @param       name  Name of the employee that you want to display.
    *
    * @returns     Nothing. It just displays the information about the searched employee.
    */
    public employee searchEmployee(String id, String name) {
        int index = binarySearch(id, name);

        if (index != -1)
            return listsOfEmployees.get(index);
        
        return null;
    }

    public int binarySearch(String id, String name) {
        int l = 0, r = listsOfEmployees.size() - 1, 
            m = 0, resID = 0, resName = 0;

        while (l <= r) {
            // Calculating mid 
            m = l + (r - l) / 2; 
  
            resID = id.compareTo(listsOfEmployees.get(m).getEmployeeID());
            resName = name.compareToIgnoreCase(listsOfEmployees.get(m).getEmployeeName());
  
            // Check if x is present at mid 
            if (resID == 0 && resName == 0) 
                return m;
  
            // If x greater, ignore left half 
            if (resID > 0) 
                l = m + 1; 
  
            // If x is smaller, ignore right half 
            else
                r = m - 1;
        }

        return -1;
    }
}
