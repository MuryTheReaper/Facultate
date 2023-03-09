using System;

//Definițiclasa abstractă Task 
//avand  atributele:taskID(String), descriere(String) si  
//metodele:un  constructor  cu parametri,  set/get, execute()(metoda  abstracta), toString()si  metodele  equals -hashCode;De  ce  trebuie  sa  fie clasa Task abstracta?

namespace Seminar11.domain
{
    public abstract class Task
    {
        private String taskID;
        private String descriere;

        public String TaskID
        {
            get => taskID;
            set => taskID = value;
        }

        public String Descriere
        {
            get => descriere;
            set => descriere = value;
        }

        public Task(String taskID, String descriere)
        {
            this.taskID = taskID;
            this.descriere = descriere;
        }

        public abstract void execute();

        public override string ToString()
        {
            return "Task{" +
                   "taskID='" + taskID + '\'' +
                   ", descriere='" + descriere + '\'' +
                   '}';
        }

        public override bool Equals(object? obj)
        {
            if (this == obj) return true;

            if (obj == null || GetType() != obj.GetType()) return false;

            Task task = (Task) obj;

            return taskID == task.taskID && descriere == task.descriere;
        }

        public override int GetHashCode()
        {
           return HashCode.Combine(taskID, descriere);
        }


    }
}