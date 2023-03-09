package factory;

import container.Container;
import container.QueueContainer;
import container.StackContainer;
import container.Strategy;

public class TaskContainerFactory implements Factory {

    private static TaskContainerFactory singleton = null;

    private TaskContainerFactory() {
    }

    public synchronized static TaskContainerFactory getInstance() {
        if (singleton == null) {
            singleton = new TaskContainerFactory();
        }
        return singleton;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        if (strategy == Strategy.LIFO) {
            return new StackContainer();
        }
        if (strategy == Strategy.FIFO) {
            return new QueueContainer();
        }
        // ...
        return null;
    }
}
