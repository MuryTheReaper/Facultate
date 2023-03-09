package domain.validators;

import domain.Location;

public class LocationValidator implements Validator<Location> {

    @Override
    public void validate(Location entity) throws ValidatorException {
        String errors = "";
        if (entity.getLocationName().equals(""))
            errors += "Name can't be empty!\n";
        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }
}
