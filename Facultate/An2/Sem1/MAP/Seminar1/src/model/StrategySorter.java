package model;

public class StrategySorter {

    private final AbstractSorter strategy;

    public StrategySorter(AbstractSorter strategy) {
        this.strategy = strategy;
    }

    public void sort(int[] vector) {
        strategy.sort(vector);
    }
}
