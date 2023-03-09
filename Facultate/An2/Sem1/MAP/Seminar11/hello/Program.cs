using Seminar11.domain;

namespace Seminar11
{
    public class Run
    {
        static void Main(string[] args){
            
            domain.Task task1 = new MessageTask("1", "descriere", "mesaj", "from", "to", DateTime.Now);
            domain.Task task2 = new MessageTask("2", "descriere", "mesaj", "from", "to", DateTime.Now);
            domain.Task task3 = new MessageTask("3", "descriere", "mesaj", "from", "to", DateTime.Now);
            domain.Task task4 = new MessageTask("4", "descriere", "mesaj", "from", "to", DateTime.Now);
            domain.Task task5 = new MessageTask("5", "descriere", "mesaj", "from", "to", DateTime.Now);

            List<domain.Task> tasks = new List<domain.Task>{task1, task2, task3, task4, task5};

            foreach (domain.Task task in tasks)
            {
                task.execute();
            }
            

        }
    }

}