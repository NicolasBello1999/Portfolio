public class employee {
    // employee information
    private department dep;
    private String employeeName;
    private String employeeID;

    private float salary;
    private float wage;
    private int hours;

    // getters and setters
    public void setEmployeeName(String name) { this.employeeName = name; }
    public void setEmployeeID(String id) { this.employeeID = id; }
    public void setSalary() { this.salary = this.wage * this.hours; }
    public void setWage(float wage) { this.wage = wage; }
    public void setHours(int hours) { this.hours = hours; }
    
    public String getEmployeeName() { return this.employeeName; }
    public String getEmployeeID() { return this.employeeID; }
    public float getSalary() { return this.salary; }
    public float getWage() { return this.wage; }
    public int getHours() { return this.hours; }

    public void displayInfo() {
        System.out.printf("*--------------------------------------------------*");
        System.out.printf("| Employee Name: %s |\n", this.employeeName);
        System.out.printf("| Employee ID: %s |\n", this.employeeID);
        System.out.printf("| Salary: $%.2f |\n", this.salary);
        System.out.printf("| Hours worked: %d |\n", this.hours);
        System.out.printf("| Hourly rate (wage): %d |\n", this.wage);
        System.out.printf("*--------------------------------------------------*");
    }
}
