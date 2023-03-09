package domain.validators;

import domain.Location;
import domain.SpecialOffer;

public class SpecialOfferValidator implements Validator<SpecialOffer> {

    @Override
    public void validate(SpecialOffer entity) throws ValidatorException {
        String errors = "";
        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }
}
