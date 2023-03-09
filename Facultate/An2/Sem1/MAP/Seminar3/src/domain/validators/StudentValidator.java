package domain.validators;

import domain.Student;

public class StudentValidator implements Validator<Student> {
    @Override
    public void validate(Student entity) throws ValidationException {
        String errors = "";
        /*if (entity.getID() == null || entity.getID().equals(""))
            errors += "Invalid ID! ";
        if (entity.getNume() == null || entity.getNume().equals(""))
            errors += "Invalid name! ";
        if (entity.getGrupa() == null || entity.getGrupa() < 110 || entity.getGrupa() > 938)
            errors += "Invalid group! ";
        if (entity.getEmail() == null || entity.getEmail().equals(""))
            errors += "Invalid email! ";
        if (entity.getCadruDidacticIndrumatorLab() == null || entity.getCadruDidacticIndrumatorLab().equals(""))
            errors += "Invalid teacher! ";
        if (errors.length() > 0)
            throw new ValidationException(errors);
    */}
}
