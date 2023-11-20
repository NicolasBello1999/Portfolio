public class singly_ll {
    public Node head;

    public static void main(String[] args) {
        singly_ll objHead = new singly_ll();

        objHead.head = objHead.createLL_insertByTail(objHead.head, 5);
        objHead.head = objHead.createLL_insertByTail(objHead.head, 5);
        objHead.head = objHead.createLL_insertByTail(objHead.head, 43);
        objHead.head = objHead.createLL_insertByTail(objHead.head, 97);
        objHead.head = objHead.createLL_insertByTail(objHead.head, 5);
        objHead.head = objHead.createLL_insertByTail(objHead.head, 2);

        objHead.printLL(objHead.head);

        objHead.head = objHead.insert_y_after_x(objHead.head, 2, 81);

        objHead.printLL(objHead.head);
    }

    Node createLL_insertByTail(Node head, int data) {
        Node temp = new Node(null, data); // create new node
        Node iter = head;

        if (head == null) return temp;

        while (iter.next != null)
            iter = iter.next;

        iter.next = temp;

        return head; // we are returning the very first node which is the head so we are retaining this position
    }

    Node createLL_insertByHead(Node head, int data) {
        Node temp = new Node(null, data); // create new node

        if (head == null) return temp;

        temp.next = head;

        return temp; // we are returning this as the new head
    }

    /* insert a new node with the value y after a node with x value; so if y = 100 and x = 8, 
    we insert a new node with value 100 after a node with value 8. */
    Node insert_y_after_x(Node head, int x, int y) {
        Node iter = head, hold;

        while (iter != null) {
            if (iter.data == x) {
                hold = iter;
                Node temp = new Node(hold.next, y);
                hold.next = temp;
            }
            iter = iter.next;
        }

        return head;
    }

    // insert data in ascending order meaning that the head will have the lowest value and the tail will have the greatest value
    Node insert_inOrder(Node head, int data) {
        Node temp = new Node(null, data);
        Node iter = head, hold;

        if (head == null) return temp;

        if (head.data > data) { // if the head is greater than our current value
            temp.next = iter;
            return temp;
        }

        // we want to hold the node that less than our new node but the node ahead is greater than our new node as well, also checking for NULLs 
        while (iter.next.data < data && iter.next != null)
            iter = iter.next;

        hold = iter.next;
        iter.next = temp;
        temp.next = hold;

        return head;
    }

    void printLL(Node head) {
        Node iter = head;
        System.out.print("The Linked List:\n");
        while (iter != null) {
            System.out.printf("%d%s", iter.data, iter.next != null ? " -> " : " -> NULL\n");
            iter = iter.next;
        }
    }
}

class Node {
    int data;
    Node next;

    public Node(int data) {
        this.data = data;
        this.next = null;
    }

    public Node(Node next, int data) {
        this.data = data;
        this.next = next;
    }
}