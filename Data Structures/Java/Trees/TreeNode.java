package Trees;

public class TreeNode<T extends Comparable<T>> {
    public TreeNode<T> left, right;
    public T data;

    public TreeNode(T data) {
        this.left = this.right = null;
        this.data = data;
    }

    public int compareTo(Object obj) {

    }
}
