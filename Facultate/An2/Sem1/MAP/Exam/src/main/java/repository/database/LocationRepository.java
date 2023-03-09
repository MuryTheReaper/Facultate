package repository.database;

import domain.Location;
import domain.validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LocationRepository extends AbstractDBRepository<Double, Location> {

    public LocationRepository(String url, String username, String password, Validator<Location> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Class<Location> getEntityClass() {
        return Location.class;
    }

    @Override
    public Location extractEntity(ResultSet rs) {
        try {
            Double id = rs.getDouble("id");
            String name = rs.getString("locationName");
            Location location = new Location(name);
            location.setId(id);
            return location;

        }catch (SQLException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void createEntity(PreparedStatement ps, Location entity) {

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
