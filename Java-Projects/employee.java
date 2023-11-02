public class employee {
    // employee information
    private String employeeName;
    private String employeeID;

    private float wage;
    private int hours;

    // getters and setters
    public void setEmployeeName(String name) { this.employeeName = name; }
    public void setEmployeeID(String id) { this.employeeID = id; }
    public void setWage(float wage) { this.wage = wage; }
    public void setHours(int hours) { this.hours = hours; }
    
    public String getEmployeeName() { return this.employeeName; }
    public String getEmployeeID() { return this.employeeID; }
    public float getWage() { return this.wage; }
    public int getHours() { return this.hours; }
}
