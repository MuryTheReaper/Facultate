package repository.database;

import domain.Hotel;
import domain.validators.Validator;
import utils.Constants;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class HotelRepository extends AbstractDBRepository<Double, Hotel> {

    public HotelRepository(String url, String username, String password, Validator<Hotel> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Class<Hotel> getEntityClass() {
        return Hotel.class;
    }

    @Override
    public Hotel extractEntity(ResultSet rs) {
        try {
            Double id = rs.getDouble("id");
            String name = rs.getString("hotelName");
            Double locationId = rs.getDouble("locationId");
            int rooms = rs.getInt("noRooms");
            Double price = rs.getDouble("pricePerNight");
            String type = rs.getString("type");
            Constants.Type t = null;
            if(type.equals("FAMILY"))
                t = Constants.Type.FAMILY;
            if(type.equals("TEENAGERS"))
                t = Constants.Type.TEENAGERS;
            if(type.equals("OLDPEOPLE"))
                t = Constants.Type.OLDPEOPLE;

            Hotel hotel = new Hotel(locationId,name,rooms, price, t);
            hotel.setId(id);

            return hotel;

        }catch (SQLException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void createEntity(PreparedStatement ps, Hotel entity) {

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
