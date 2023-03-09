package repository.database;

import domain.Table;
import domain.validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TableRepository extends AbstractDBRepository<Long, Table> {


    public TableRepository(String url, String username, String password, Validator<Table> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Class<Table> getEntityClass() {
        return Table.class;
    }

    @Override
    public Table extractEntity(ResultSet rs) {
        try {
            Long id = rs.getLong("id");
            boolean isDeleted = rs.getBoolean("isDeleted");
            Table table = new Table();
            table.setId(id);
            table.setDeleted(isDeleted);
            return table;

        }catch (SQLException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void createEntity(PreparedStatement ps, Table entity) {

        try {
            ps.setLong(1, entity.getId());

        } catch (SQLException e) {
            e.printStackTrace();
        }
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
