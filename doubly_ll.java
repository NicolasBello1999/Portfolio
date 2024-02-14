/*
 * Very simple program displaying how doubly linked lists work. 
 */

import java.util.*;

public class doubly_ll {
    private Node head;
    private Node tail;

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        doubly_ll ll_obj = new doubly_ll();
        int menuOption = 0;
        boolean repetitionMode = false;

        do {
            try {
                menuOption = ll_obj.menu(keyboard);
                switch (menuOption) {
                    case 1:
                        ll_obj.handleInput(ll_obj, keyboard, repetitionMode, 1);
                        break;
                    case 2:
                        ll_obj.handleInput(ll_obj, keyboard, repetitionMode, 2);
                        break;
                    case 3:
                        ll_obj.printLLForwards();
                        break;
                    case 4:
                        ll_obj.printLLBackwards();
                        break;
                    case 5:
                        ll_obj.sortLL();
                        break;
                    case 6:
                        repetitionMode = !repetitionMode;
                        System.out.printf("Repition mode status - [%s]\n", repetitionMode);
                        break;
                    case 7:
                        System.out.println("Exiting program...");
                        break;
                }
            } catch (NumberFormatException e) {
                System.err.println(e);
            } catch (Exception e) {
                System.err.println(e);
            }
        } while (menuOption != 7);

        keyboard.close();
    }

    // inserts data into the LL in FIFO type of fashion (Queues)
    public void insertByTail(int data) {
        Node temp = new Node(data);
        Node iter = head;

        if (head == null) {
            head = temp;
            tail = temp;
            return;
        }

        while (iter.next != null)
            iter = iter.next;
        
        iter.next = temp;
        temp.prev = iter;
        tail = temp;
    }

    // inserts data into the LL in LIFO type of fashion (Stacks)
    public void insertByHead(int data) {
        Node temp = new Node(data);

        if (head == null) {
            head = temp;
            tail = temp;
            return;
        }

        temp.next = head;
        head.prev = temp;
        head = temp;
    }

    // handles user input and is our main method for entering information into our LL
    public void handleInput(doubly_ll ll_obj, Scanner keyboard, boolean repetitionMode, int method) throws NumberFormatException {
        String tempInput;
        int input = 0;

        do {
            System.out.print("Enter a number: ");
            tempInput = keyboard.nextLine();
            input = Integer.parseInt(tempInput);

            if (input != 999) {
                if (method == 1)
                    ll_obj.insertByTail(input);
                else
                    ll_obj.insertByHead(input);
            }
        } while (repetitionMode && input != 999);
    }

    // handles user input, used for our menu method, if user inputs anything other than a number we will throw an exception that'll be caught in main
    public int handleInput(Scanner keyboard) throws NumberFormatException {
        String tempInput;
        int input = 0;

        tempInput = keyboard.nextLine();
        input = Integer.parseInt(tempInput);

        return input;
    }

    // allows the user to choose what menu option they want and then return to main to call their respective methods based on user input
    public int menu(Scanner keyboard) throws OutOfBounds {
        int menuOption = 0;

        System.out.flush();
        System.out.println("================================");
        System.out.println("List of options:");
        System.out.println("1. Insert data by tail");
        System.out.println("2. Insert data by head");
        System.out.println("3. Print doubly LL forwards");
        System.out.println("4. Print doubly LL backwards");
        System.out.println("5. Sort doubly LL");
        System.out.println("6. Toggle repetition mode");
        System.out.println("7. Exit program");
        System.out.println("================================");
        System.out.print("Enter option: ");

        menuOption = handleInput(keyboard);

        if (menuOption < 1 || menuOption > 7)
            throw new OutOfBounds(menuOption);

        return menuOption;
    }

    // sort the LL in ascending order, uses a reworked version of bubble sort for the LL - O(n^2)
    public void sortLL() {
        Node iter = head, cur;
        boolean swapped;
        int temp;

        while (iter.next != null) {
            swapped = false;
            cur = iter;
            while (cur != null) {
                if (cur.data > iter.data) {
                    temp = cur.data;
                    cur.data = iter.data;
                    iter.data = temp;
                    swapped = true;
                }
                cur = cur.next;

                if (swapped) break;
            }
            iter = iter.next;
        }
    }

    public void printLLForwards() {
        if (head == null) {
            System.out.println("\nLinked list is empty!");
            return;
        }

        Node iter = head;

        System.out.printf("Printing doubly LL Forwards:\nHead -> ");
        while (iter != null) {
            System.out.printf("%d%s", iter.data, (iter.next != null) ? " -> " : " -> NULL\n");
            iter = iter.next;
        }
        System.out.println();
    }

    public void printLLBackwards() {
        if (tail == null) {
            System.out.println("\nLinked list is empty!");
            return;
        }

        Node iter = tail;

        System.out.printf("Printing doubly LL Backwards:\nTail -> ");
        while (iter != null) {
            System.out.printf("%d%s", iter.data, (iter.prev != null) ? " -> " : " -> NULL\n");
            iter = iter.prev;
        }
        System.out.println();
    }
    
    class Node {
        int data;
        Node next, prev;

        public Node(int data) {
            this.data = data;
            this.next = null;
            this.prev = null;
        }

        public Node(Node next, Node prev, int data) {
            this.data = data;
            this.next = next;
            this.prev = prev;
        }
    }

    class OutOfBounds extends Exception {
        public OutOfBounds(Object error) {
            System.err.println("ERROR! Input is not within menu option bounds...");
        }
    }
}