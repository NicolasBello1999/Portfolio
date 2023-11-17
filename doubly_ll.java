class doubly_ll {
    public Node head;
    public Node tail;

    public static void main(String[] args) {
        doubly_ll ll_head = new doubly_ll();

        ll_head.head = ll_head.createLL_insertByTail(ll_head, 10);
        ll_head.head = ll_head.createLL_insertByTail(ll_head, 15);
        ll_head.head = ll_head.createLL_insertByTail(ll_head, 23);

        printLLForwards(ll_head.head);
        ll_head.printLLBackwards(ll_head.tail);
    }

    Node createLL_insertByTail(doubly_ll ll_head, int data) {
        Node temp = new Node(data);
        Node iter = ll_head.head;

        if (ll_head.head == null) {
            ll_head.head = temp;
            ll_head.tail = temp;
            return ll_head.head;
        }

        while (iter.next != null)
            iter = iter.next;
        
        iter.next = temp;
        temp.prev = iter;
        ll_head.tail = temp;

        return ll_head.head;
    }

    public static void printLLForwards(Node head) {
        Node iter = head;

        while (iter != null) {
            System.out.printf("%d%s", head.data, (head.next != null) ? "->" : "\n");
            iter = iter.next;
        }
    }

    public void printLLBackwards(Node tail) {
        Node iter = tail;

        System.out.printf("Printing doubly LL backwards:\nTail->");
        while (iter != null) {
            System.out.printf("%d%s", head.data, (head.next != null) ? "->" : "\n");
            iter = iter.prev;
        }
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
}