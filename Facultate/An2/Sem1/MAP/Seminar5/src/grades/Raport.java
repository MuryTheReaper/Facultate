package grades;

import java.util.Comparator;
import java.util.List;

public class Raport {

    private List<Student> students;

    private List<Tema> teme;

    private List<Nota> note;

    public Raport(List<Student> students, List<Tema> teme, List<Nota> note) {
        this.students = students;
        this.teme = teme;
        this.note = note;
    }


    public float medieTema(Tema tema) {
        return (float) note.stream()
                .filter(nota -> nota.getTema().equals(tema))
                .mapToDouble(Nota::getValue)
                .average()
                .orElse(0);
    }

    private Tema ceaMai(Comparator<Tema> comparator) {
        return teme.stream()
                .max(comparator)
                .orElse(null);
    }


    public Tema maxMedieTema() {

        return ceaMai(Comparator.comparing(this::medieTema));
    }

    public Tema minMedieTema() {
        return ceaMai(Comparator.comparing(this::medieTema).reversed());
    }
}
