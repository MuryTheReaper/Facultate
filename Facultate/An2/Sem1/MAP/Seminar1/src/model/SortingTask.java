package model;


public class SortingTask extends Task {

    private int[] numbers;

    public SortingTask(String taskId, String description, int[] numbers) {
        super(taskId, description);
        this.numbers = numbers;
    }

    public int[] getNumbers() {
        return numbers;
    }

    public void setNumbers(int[] numbers) {
        this.numbers = numbers;
    }

    @Override
    public void execute() {

        StrategySorter sorter;
        if (getDescription().equals("bubbleSort")) {
            sorter = new StrategySorter(new BubbleSort());
        } else {
            sorter = new StrategySorter(new QuickSort());
        }


        sorter.sort(numbers);
        System.out.print(getDescription() + ": ");
        for (Object number : numbers) {
            System.out.print(number + " ");
        }
        System.out.println();

    }
}
