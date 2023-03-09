package model;

public class BubbleSort implements AbstractSorter {

    @Override
    public void sort(int[] vector) {
        int n = vector.length;
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (vector[j] > vector[j + 1]) {
                    AbstractSorter.swap(vector, j + 1, j);
                }
    }
}
