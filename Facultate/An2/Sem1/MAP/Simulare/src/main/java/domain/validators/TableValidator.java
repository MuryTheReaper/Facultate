package domain.validators;

import domain.Table;

public class TableValidator implements Validator<Table>{

    @Override
    public void validate(Table entity) throws ValidatorException {
        String errors = "";
        if(entity.getId() < 0)
            errors += "Id must be positive!\n";
        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }
}

