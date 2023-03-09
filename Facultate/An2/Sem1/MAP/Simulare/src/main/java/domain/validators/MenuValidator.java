package domain.validators;

import domain.MenuItem;

public class MenuValidator implements Validator<MenuItem>{
    @Override
    public void validate(MenuItem entity) throws ValidatorException {
        String errors = "";
        if (entity.getItem().equals(""))
            errors += "Name can't be empty!\n";
        if (entity.getPrice() < 0)
            errors += "Price can't be negative!\n";

        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }
}
