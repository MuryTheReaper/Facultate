package container;

import model.Task;

import static utils.Constants.INITIAL_STACK_SIZE;

public class StackContainer extends SuperContainer {

    public StackContainer() {
        super();
        tasks = new Task[INITIAL_STACK_SIZE];
    }

    @Override
    public Task remove() {
        if (!isEmpty()) {
            size--;
            return tasks[size];
        }
        return null;
    }
}
