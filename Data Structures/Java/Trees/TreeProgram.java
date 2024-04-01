package Trees;
import java.util.*;

public class TreeProgram {
    public static void main(String[] args) {
        BinaryTree<Integer> tree = new BinaryTree<Integer>();
        Scanner keyboard = new Scanner(System.in);

        while (true) {
            try {
                menu(); // print the menu
                String choice = keyboard.nextLine();
                int menuChoice = Integer.parseInt(choice);
                int value, maxInput, i;

                if (menuChoice == 6) { // exit the loop
                    System.out.printf("Exiting program...\n");
                    break;
                }

                switch(menuChoice) {
                    case 1:
                        System.out.printf("How many nodes would you like to create: ");
                        maxInput = Integer.parseInt(keyboard.nextLine());

                        for (i = 0; i < maxInput; i++) {
                            System.out.printf("Enter data: ");
                            value = Integer.parseInt(keyboard.nextLine());
                            tree.setRoot(tree.insertNodeRec(tree.getRoot(), value));
                        }
                        break;
                    case 2:
                        System.out.printf("How many nodes would you like to delete: ");
                        maxInput = Integer.parseInt(keyboard.nextLine());

                        if (maxInput > tree.totalNodes(tree.getRoot())) {
                            System.err.printf("Error, there are not enough nodes to delete from the tree.\n");
                            break;
                        }

                        for (i = 0; i < maxInput; i++) {
                            System.out.printf("Enter data: ");
                            value = Integer.parseInt(keyboard.nextLine());
                            tree.setRoot(tree.deleteNode(tree.getRoot(), value));
                        }
                        break;
                    case 3:
                        System.out.printf("Enter node you would like to find the depth of: ");
                        value = Integer.parseInt(keyboard.nextLine());
                        System.out.printf("The depth of node [%d] is %d.\n", value, tree.depthOfNode(tree.getRoot(), value, 0));
                        break;
                    case 4:
                        System.out.printf("Enter node you would like to find the height of: ");
                        value = Integer.parseInt(keyboard.nextLine());
                        System.out.printf("The height of node [%d] is %d.\n", value, tree.heightOfNode(tree.getRoot(), value));
                        break;
                    case 5:
                        tree.printTree(tree.getRoot());
                        break;
                    default:
                        break;
                }
            } catch (NumberFormatException e) { // incorrect user input by entering a character that isn't an integer
                System.err.printf("Invalid input, please enter a valid number - ERROR {%s}\n", e);
            } catch (Exception e) {
                System.err.printf("Error detected - ERROR {%s}\n", e);
            }
        }

        keyboard.close();
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
        System.out.printf("| Enter option: ");
    }
}
