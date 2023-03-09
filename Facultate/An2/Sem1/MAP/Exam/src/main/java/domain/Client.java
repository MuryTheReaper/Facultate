package domain;

import utils.Constants;

public class Client extends Entity<Long>{

    private String name;

    private int fidelityGrade;

    private int varsta;

    private Constants.Hobbies hobbies;

    public Client(String name, int fidelityGrade, int varsta, Constants.Hobbies hobbies) {
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.varsta = varsta;
        this.hobbies = hobbies;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getFidelityGrade() {
        return fidelityGrade;
    }

    public void setFidelityGrade(int fidelityGrade) {
        this.fidelityGrade = fidelityGrade;
    }

    public int getVarsta() {
        return varsta;
    }

    public void setVarsta(int varsta) {
        this.varsta = varsta;
    }

    public Constants.Hobbies getHobbies() {
        return hobbies;
    }

    public void setHobbies(Constants.Hobbies hobbies) {
        this.hobbies = hobbies;
    }
}
