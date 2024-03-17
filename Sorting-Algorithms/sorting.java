import java.util.*;

public class sorting {
    public static void main(String[] args) {
        int[][] arr;
        boolean m_flag = false;
        Random rand = new Random();
        int count = 0, max = 0, i = 0, j = 0;
        String m;

        for (count = 0; count < args.length; count++) {
            if (!args[count].startsWith("-")) {
                System.out.println("Invalid argument : " + args[count]);
                return;
            }

            if(args[count].equals("-m")) m = args[++count];
        }

        if (!m_flag)
            max = 1000;

        arr = new int[4][max];
        for (i = 0; i < 4; i++) {
            for (j = 0; j < max; j++) {
                arr[i][j] = rand.nextInt(100) + 1;
                System.out.printf("%d,", arr[i][j]);
            }
            System.out.printf("\n\n");
        }

        selectionSort(arr[0]);
        for (j = 0; j < max; j++) {
            System.out.printf("%d,", arr[0][j]);
        }
    }

    public static void swap(int x, int y) {
        int temp = x;
        x = y;
        y = temp;
    }

    public static void bubbleSort(int arr[]) {
        int i, j, temp;
    
        for (i = 0; i < arr.length - 1; i++) {
            for (j = 0; j < arr.length - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    public static void insertionSort(int[] arr) {
        int i, j, key;
    
        for (i = 0; i < arr.length; i++) {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    public static void selectionSort(int[] arr) {
        int i, j, min_idx, temp;
    
        for (i = 0; i < arr.length - 1; i++) {
            min_idx = i;
    
            for (j = i + 1; j < arr.length; j++) {
                if (arr[j] <  arr[min_idx])
                    min_idx = j;
                temp = arr[i];
                arr[i] = arr[min_idx];
                arr[min_idx] = temp;
            }
        }
    }
}