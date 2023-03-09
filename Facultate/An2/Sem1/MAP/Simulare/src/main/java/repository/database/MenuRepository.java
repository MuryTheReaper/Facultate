package repository.database;

import domain.MenuItem;
import domain.Table;
import domain.validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MenuRepository extends AbstractDBRepository<Long, MenuItem> {

    public MenuRepository(String url, String username, String password, Validator<MenuItem> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Class<MenuItem> getEntityClass() {
        return MenuItem.class;
    }

    @Override
    public MenuItem extractEntity(ResultSet rs) {
        try {
            Long id = rs.getLong("id");
            String category = rs.getString("category");
            String item = rs.getString("item");
            float price = rs.getFloat("price");
            String currency = rs.getString("currency");
            boolean isDeleted = rs.getBoolean("isDeleted");
            MenuItem menuItem = new MenuItem(category, item, price, currency);
            menuItem.setId(id);
            menuItem.setDeleted(isDeleted);
            return menuItem;

        }catch (SQLException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void createEntity(PreparedStatement ps, MenuItem entity) {

    }

    @Override
    public String getUpdateQuery() {
        return null;
    }

    @Override
    public String getInsertQuery() {
        return null;
    }
}
