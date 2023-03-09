package model;

public class QuickSort implements AbstractSorter {

    private int partition(int[] vector, int low, int high) {

        int pivot = vector[high];

        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (vector[j] > pivot) {
                i++;
                AbstractSorter.swap(vector, i, j);
            }
        }
        AbstractSorter.swap(vector, i + 1, high);
        return (i + 1);
    }

    private void quickSort(int[] vector, int low, int high) {
        if (low < high) {

            int pi = partition(vector, low, high);

            quickSort(vector, low, pi - 1);
            quickSort(vector, pi + 1, high);
        }
    }

    @Override
    public void sort(int[] vector) {
        quickSort(vector, 0, vector.length - 1);
    }
}
