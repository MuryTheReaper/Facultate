package domain.validators;

import domain.Client;
import domain.Hotel;

public class ClientValidator implements Validator<Client> {

    @Override
    public void validate(Client entity) throws ValidatorException {
        String errors = "";
        if (entity.getName().equals(""))
            errors += "Name can't be empty!\n";
        if (entity.getFidelityGrade() < 0)
            errors += "Grade can't be negative!\n";
        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }

}
