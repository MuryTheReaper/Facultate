package domain.validators;

import domain.Order;

public class OrderValidator implements Validator<Order> {
    @Override
    public void validate(Order entity) throws ValidatorException {
        String errors = "";
        if(entity.getId() < 0)
            errors += "Id must be positive!\n";
        if(entity.getTableId() < 0)
            errors += "Table id must be positive!\n";
        if(entity.getMenuItemIds().size() == 0)
            errors += "Order must have at least one menu item!\n";
        if (!errors.equals(""))
            throw new ValidatorException(errors);
    }
}
