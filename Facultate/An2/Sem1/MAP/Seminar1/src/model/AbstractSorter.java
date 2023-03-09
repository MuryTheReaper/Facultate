package model;

public interface AbstractSorter {

    void sort(int[] vector);

    static void swap(int[] vector, int i, int j) {
        int temp = vector[i];
        vector[i] = vector[j];
        vector[j] = temp;
    }
}
