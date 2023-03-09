package model;

import java.util.Objects;

public class Student {

    private  String nume;
    private  float media;

    public Student(String nume, float media) {
        this.nume = nume;
        this.media = media;
    }

    public String getNume() {
        return nume;
    }

    public float getMedia() {
        return media;
    }

    public int getMediaRotunjita() {
        return Math.round(media);
    }

    @Override
    public String toString(){
        return nume + " " + media;
    }

    @Override
    public int hashCode(){
        return Objects.hash(nume, media);
    }

    @Override
    public boolean equals(Object o) {
        //verifica prin adresa obiectului
        if (this == o) return true;
        //instance of
        if (o == null || getClass() != o.getClass()) return false;
        //facem cast in caz ca e copil de student
        Student student = (Student) o;
        return Float.compare(student.media, media) == 0 && nume.equals(student.nume);
    }
}
