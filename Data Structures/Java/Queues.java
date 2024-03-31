import java.util.*;

public class Queues {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);

        try {
            System.out.print("Enter the max size for the queue: ");
            int maxSize = keyboard.nextInt();

            Queues myQueue = new Queues(maxSize);
            for (int i = 0; i < maxSize; i++) {
                System.out.print("Enter a string: ");
                String input = keyboard.next();

                myQueue.enqueue(input); // Adds item to end of queue
            }
            myQueue.printQueue(myQueue);
        } catch (Exception e) {
            System.err.println(e);
        }
    }

    public class Node {
        private Node next;
        private Node prev;
        private String data;

        public Node(String str) {
            next = prev = null;
            this.data = str;
        }
    }

    private Node head, tail;
    private int size, maxQueue;

    public Queues() {
        head = tail = null;
        this.maxQueue = 100;
        this.size = 0;
    }

    public Queues(int maxQueue) {
        head = tail = null;
        this.maxQueue = maxQueue;
        this.size = 0;
    }

    public void enqueue(String str) {
        Node temp = new Node(str);

        if (size >= maxQueue) {
            throw new IllegalStateException("Queue is full");
        } else if (isEmpty()) {
            head = tail = temp;
        } else {
            tail.next = temp;
            temp.prev = tail;
            tail = temp;
        }

        size++;
    }

    public String dequeue() {
        if (isEmpty()) throw new IllegalStateException("Nothing to dequeue from the queue");

        String headData = head.data;
        head = head.next;
        head.prev = null;
        size--;

        return headData;
    }

    public int inlineQueue(String str) {
        Node iter = head;
        int fromHead = 0, notFound = -1;

        if (isEmpty()) throw new RuntimeException("Queue is empty");

        while (iter != null) {
            if (iter.data.equals(str))
                return fromHead;
            iter = iter.next;
            fromHead++;
        }

        return notFound;
    }

    public String peek() {
        if (isEmpty()) throw new RuntimeException("Queue is empty");

        return head.data;
    }

    public boolean isEmpty() {
        return (size == 0) ? true : false;
    }

    public void printQueue(Queues myQueue) {
        Node iter = myQueue.head;
        int i;

        System.out.printf("\n       ");
        while (iter != null) {
            System.out.printf("0");
            for (i = 0; i < iter.data.length(); i++) {
                System.out.printf("=");
            }
            System.out.printf("0   ");
            iter = iter.next;
        }

        System.out.println();
        iter = myQueue.head;
        System.out.printf("Head<->");
        while (iter != null) {
            System.out.printf("|%s|<->", iter.data);
            iter = iter.next;
        }
        System.out.printf("Tail\n       ");

        iter = myQueue.head;
        while (iter != null) {
            System.out.printf("0");
            for (i = 0; i < iter.data.length(); i++) {
                System.out.printf("=");
            }
            System.out.printf("0   ");
            iter = iter.next;
        }
    }
}
