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


}
