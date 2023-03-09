package domain.validators;

import domain.Hotel;

public class HotelValidator implements Validator<Hotel> {

    @Override
    public void validate(Hotel entity) throws ValidatorException {
        String errors = "";
        if (entity.getHotelName().equals(""))
            errors += "Name can't be empty!\n";
        if (entity.getPricePerNight() < 0)
            errors += "Price can't be negative!\n";

        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }
}
