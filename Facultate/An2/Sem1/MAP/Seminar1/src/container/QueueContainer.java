package container;

import model.Task;

import static utils.Constants.INITIAL_QUEUE_SIZE;

public class QueueContainer extends SuperContainer {
    private int front;

    public QueueContainer() {
        super();
        tasks = new Task[INITIAL_QUEUE_SIZE];
        front = 0;
    }

    @Override
    public Task remove() {
        if (!isEmpty()) {
            size--;
            Task x = tasks[front];
            if (size != 0) {
                front = front + 1;
            } else {
                front = 0;
            }
            return x;
        }
        return null;
    }
}
