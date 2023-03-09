package run;

import container.Strategy;
import model.MessageTask;
import model.SortingTask;
import model.Task;
import runner.DelayTaskRunner;
import runner.PrinterTaskRunner;
import runner.StrategyTaskRunner;
import runner.TaskRunner;

import java.time.LocalDateTime;
import java.util.Objects;

public class TestRunner {
    private static MessageTask[] getMessages() {
        MessageTask taskLaborator = new MessageTask(
                "1", "Seminar", "tema laborator",
                "Florentin", "Razvan", LocalDateTime.now());
        MessageTask taskTema = new MessageTask(
                "2", "Laborator", "Solutie",
                "Razvan", "Florentin", LocalDateTime.now());
        MessageTask taskNota = new MessageTask(
                "3", "Nota Lab", "10",
                "Florentin", "Razvan", LocalDateTime.now());
        return new MessageTask[]{
                taskLaborator, taskTema, taskNota
        };
    }

    private static SortingTask[] getSortings() {
        SortingTask taskRandomBubble = new SortingTask("1", "bubbleSort", new int[]{-5, 5, -3, 2, 0});
        SortingTask taskRandomQuick = new SortingTask("2", "quickSort", new int[]{1, 5, -3, 2, 0});

        return new SortingTask[]{
                taskRandomBubble, taskRandomQuick
        };
    }

    private static void addTasksInRunner(Task[] tasks, TaskRunner runner) {
        for (Task task : tasks) {
            runner.addTask(task);
        }
    }

    public static void run(String[] args) {

        MessageTask[] messages = getMessages();
        Strategy strategy;
        if (Objects.equals(args[0], "FIFO")) {
            strategy = Strategy.FIFO;
        } else {
            strategy = Strategy.LIFO;
        }
        StrategyTaskRunner runner = new StrategyTaskRunner(strategy);
        addTasksInRunner(messages, runner);
        System.out.println("StrategyTaskRunner");
        runner.executeAll();

        PrinterTaskRunner printer = new PrinterTaskRunner(runner);
        addTasksInRunner(getSortings(), printer);
        //addTasksInRunner(messages, printer);
        System.out.println("PrinterTaskRunner");
        printer.executeAll();


        DelayTaskRunner delayed = new DelayTaskRunner(runner);
        addTasksInRunner(messages, delayed);
        System.out.println("DelayTaskRunner");
        delayed.executeAll();


    }
}
