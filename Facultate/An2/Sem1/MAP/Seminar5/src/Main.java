import grades.Nota;
import grades.Raport;
import grades.Student;
import grades.Tema;

import javax.xml.transform.stream.StreamSource;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {

        Student s1 = new Student(1, "John");
        Student s2 = new Student(2, "Jane");
        Student s3 = new Student(3, "Jack");
        Student s4 = new Student(4, "Jill");


        Tema t1 = new Tema("Tema MAP", "1");
        Tema t2 = new Tema("Tema ASC", "2");
        Tema t3 = new Tema("Tema Algebra", "3");
        Tema t4 = new Tema("Tema OOP", "4");


        Nota n1 = new Nota("Antonin", s1, t1, 10);
        Nota n2 = new Nota("Antonin", s2, t1, 8);
        Nota n3 = new Nota("Antonin", s3, t1, 7);

        Nota n4 = new Nota("Antonin", s2, t2, 8);

        Nota n5 = new Nota("Nicu", s3, t3, 5);

        Nota n6 = new Nota("Alex", s1, t4, 9);
        Nota n7 = new Nota("Antonin", s4, t4, 7);



        List<Nota> notaList = Arrays.asList(n1, n2, n3, n4, n5, n6, n7);
        List<Student> studentList = Arrays.asList(s1, s2, s3, s4);
        List<Tema> temaList = Arrays.asList(t1, t2, t3, t4);

        Raport r = new Raport(studentList, temaList, notaList);

        System.out.println("Report MEDIE PT TEME :");
        temaList.forEach(x -> System.out.println(x + " " + r.medieTema(x)));

        System.out.println("\nReport MAX MEDIE:");
        System.out.println(r.maxMedieTema());

        System.out.println("\nReport MIN MEDIE:");
        System.out.println(r.minMedieTema());


    }
}