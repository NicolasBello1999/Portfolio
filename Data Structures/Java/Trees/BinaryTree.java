package Trees;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class BinaryTree<T> {
    private TreeNode<T> root;

    public BinaryTree() {
        this.root = null;
    }

    public TreeNode<T> insertNodeRec(TreeNode<T> node, T data) {
        if (node == null) {
            return new TreeNode(data);
        }

        if (data.compareTo(node.data) ) {
            node.right = insertNodeRec(node.right, data);
        } else {
            node.left = insertNodeRec(node.left, data);
        }

        return node;
    }

    public void insertNodeIter(TreeNode<T> node, int data) {

    }

    public TreeNode<T> deleteNode(TreeNode<T> node, int data) {
        if (node == null) return null;

        if (data > node.data) { // if the target is in right subtree
            node.right = deleteNode(node.right, data);
        } else if (data < node.data) { // if the target is in left subtree
            node.left = deleteNode(node.left, data);
        } else { // we found the key value for the node
            if (node.left == null && node.right == null) { // no children - case 1
                node = null;
            } else if (node.left == null) { // only has a single child node - case 2
                return node.right;
            } else if (node.right == null) {
                return node.left;
            } else { // has two existing child nodes - case 3
                // find the minimum element of the right sub tree and replace it with the parent node's data
                node.data = findMinNode(node.right).data;
                node.right = deleteNode(node.right, node.data);
            }
        }

        return node;
    }

    public TreeNode<T> findMinNode(TreeNode<T> node) {
        if (node.left != null)
            node = findMinNode(node.left);
        return node;
    }

    public TreeNode<T> findNode(TreeNode<T> node, int key) {
        if (node == null) return null;

        if (node.data == key) return node;

        // Recursively search in the left and right subtrees
        TreeNode<T> leftNode = findNode(node.left, key);
        TreeNode<T> rightNode = findNode(node.right, key);

        // Return the node if found, otherwise return null
        return (leftNode != null) ? leftNode : rightNode;
    }

    // returns the number of edges (connections between nodes) from the node to the tree's root node (the root node will have a depth of 0)
    public int depthOfNode(TreeNode<T> node, int data, int depth) {
        if (node == null) return -1;

        if (node.data == data) {
            return depth;
        }

        int left = depthOfNode(node.left, data, depth + 1);
        int right = depthOfNode(node.right, data, depth + 1);

        return Math.max(left, right);
    }

    // returns the number of edges from the longest path from the node to a leaf (a leaf node will have a height of 0)
    public int heightOfNode(TreeNode<T> node, int x) {
        TreeNode<T> target = findNode(node, x);

        if (target == null) return -1;

        return calculateHeight(target);
    }

    public int calculateHeight(TreeNode<T> node) {
        if (node == null) return -1;

        int left = calculateHeight(node.left);
        int right = calculateHeight(node.right);

        return Math.max(left, right);
    }

    public int totalNodes(TreeNode<T> node) {
        if (node == null) return 0;

        return totalNodes(node.left) + totalNodes(node.right) + 1;
    }

    /*public void printTree() {
        if (this.root == null) 
            throw new IllegalStateException("The tree is empty.");
        
        List<Integer> treeArr = treeToArray(this.root);
        int maxHeight = heightOfNode(this.root);

        for (int i = 0; i < treeArr.size(); i++) {
            if (i == 0) {
                for (int j = 0; j < maxHeight * 4; j++)
                    System.out.printf(" ");
                System.out.println(treeArr.get(i));
            } else {
                for (int j = 0; j < maxHeight * 4; j++)
                    System.out.printf(" ");
                System.out.print(treeArr.get(2 * i + 1));

                for (int j = 0; j < maxHeight * 4; j++)
                    System.out.printf(" ");
                System.out.println(treeArr.get(2 * i + 2));
            }
            maxHeight--;
        }
    }*/

    private List<Integer> treeToArray(TreeNode<T> root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode<T>> queue = new LinkedList<>();
        queue.add(root);
        
        while (!queue.isEmpty()) {
            TreeNode<T> node = queue.poll();
            if (node == null) {
                result.add(-1); // Placeholder for missing node
                continue;
            }
            result.add(node.data);
            
            queue.add(node.left);
            queue.add(node.right);
        }
        
        return result;
    }

    public void printInOrder(TreeNode<T> node) {
        if (node == null) return;

        printInOrder(node.left);
        System.out.printf("%d%s,", node.data, (node == this.root) ? "-root" : "");
        printInOrder(node.right);
    }
    
    public TreeNode<T> getRoot() { return this.root; }
    public void setRoot(TreeNode<T> root) { this.root = root; }
}
