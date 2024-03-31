package Trees;
import java.util.*;

public class TreeProgram {
    public static void main(String[] args) {
        BinaryTree tree = new BinaryTree();
        menu();

        tree.setRoot(tree.insertNodeRec(tree.getRoot(), 24));
        tree.setRoot(tree.insertNodeRec(tree.getRoot(), 65));
        tree.setRoot(tree.insertNodeRec(tree.getRoot(), 32));
        tree.setRoot(tree.insertNodeRec(tree.getRoot(), 13));
        tree.setRoot(tree.insertNodeRec(tree.getRoot(), 7));
        tree.setRoot(tree.insertNodeRec(tree.getRoot(), 11));

        tree.printInOrder(tree.getRoot());
        System.out.println();
        System.out.printf("Total amount of nodes in tree: %d\n", tree.totalNodes(tree.getRoot()));
        System.out.printf("Depth of root: %d\n", tree.depthOfNode(tree.getRoot(), 24, 0));
        System.out.printf("height of root: %d\n", tree.heightOfNode(tree.getRoot(), 24));
        tree.setRoot(tree.deleteNode(tree.getRoot(), 32));
        tree.printInOrder(tree.getRoot());
    }

    public static void menu() {
        System.out.printf("0===================================0\n");
        System.out.printf("| [1] Insert data into tree         |\n");
        System.out.printf("| [2] Delete data from tree         |\n");
        System.out.printf("| [3] Find depth of a node          |\n");
        System.out.printf("| [4] Find height of a node         |\n");
        System.out.printf("| [5] Print tree                    |\n");
        System.out.printf("| [6] Exit program                  |\n");
        System.out.printf("0===================================0\n");
    }
}
