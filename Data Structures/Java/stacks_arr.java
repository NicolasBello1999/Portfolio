class stacks_arr {
    private int capacity, size;
    private String[] arr;
    private String top;

    /**
     * Class constructor specifying the max capacity of objects the stack can hold.
     * @param capacity Determines the MAX capacity of strings the STACK is able to hold before it throws an error
     */
    public stacks_arr(int capacity) {
        this.capacity = capacity;
        arr = new String[this.capacity];
        size = 0;
    }

    /**
     * Class constructor with a default capacity size of 100 string objects for the stack.
     */
    public stacks_arr() {
        this.capacity = 100;
        arr = new String[this.capacity];
        size = 0;
    }

    public boolean isEmpty() {
        if (size == 0) 
            return true;
        else
            return false;
    }

    public void push(String s) {
        if (size >= capacity) {
            throw new IllegalStateException(s + " cannot be pushed! Stack is full!");
        }

        arr[size++] = s;
        top = s;
    }

    /**
     * @return the element at the top of the stack without removing it from the stack. If the stack is empty, returns null.
     * @exception Throws EmptyStackException if the stack by 
     */
    public String pop() {
        if (isEmpty()) {
            throw new RuntimeException("Cannot pop from an empty stack.");
        }

        return arr[size--];
    }

    public String peek() {
        if (isEmpty()) {
            System.out.println("Stack is empty.");
            return null;
        }

        return top;
    }

    /**
     * @param s string argument to be searched in the stack.
     * @return returns the distance between the element and the top of the stack. Returns -1 if s is not found in the stack.
     */
    public int search(String s) {
        int i;

        for (i = size - 1; i >= 0; i--) {
            if (s.equals(arr[i])) {
                return (size - 1) - i; // distance between the element and the top of the stack
            }
        }

        return -1;
    }

    public int getCapacity() { return capacity; }
    public int getSize() { return size; }
    public String[] getStack() { return arr; }
}