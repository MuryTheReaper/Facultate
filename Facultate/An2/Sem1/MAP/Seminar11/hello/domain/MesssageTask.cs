

//Derivați  clasa MessageTaskdin  clasa Task,  
//avand  atributele mesaj(String), from(String), to(String)  si date(LocalDateTime)
//și afișeazăpe ecran, via metoda execute, textul mesajului (valoarea atributului mesaj)si data la care a fost creat;(Vezi si DateTimeFormatter)
namespace Seminar11.domain
{

    public class MessageTask : Task{

        private String mesaj { get; set; }
        private String from { get; set; }
        private String to { get; set; }
        private DateTime date { get; set; }

        public MessageTask(String taskID, String descriere, String mesaj, String from, String to, DateTime date) : base(taskID, descriere)
        {
            this.mesaj = mesaj;
            this.from = from;
            this.to = to;
            this.date = date;
        }

        public override void execute()
        {
            Console.WriteLine("MessageTask{" +
                              "id = '" + this.TaskID + '\''+
                              ", descriere='" + this.Descriere + '\'' +
                              ", mesaj='" + mesaj + '\'' +
                              ", from='" + from + '\'' +
                              ", to='" + to + '\'' +
                              ", date=" + date +
                              '}');
        }

    }
}