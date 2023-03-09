package repository.database;

import domain.Location;
import domain.SpecialOffer;
import domain.validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;

public class SpecialOfferRepository extends AbstractDBRepository<Double, SpecialOffer> {

    public SpecialOfferRepository(String url, String username, String password, Validator<SpecialOffer> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Class<SpecialOffer> getEntityClass() {
        return SpecialOffer.class;
    }

    @Override
    public SpecialOffer extractEntity(ResultSet rs) {
        try {
            Double id = rs.getDouble("id");
            Double hotelId = rs.getDouble("hotelId");
            Date startDate = rs.getDate("startDate");
            Date endDate = rs.getDate("endDate");
            int p = rs.getInt("percents");
            SpecialOffer sp = new SpecialOffer(hotelId,startDate,endDate,p);
            sp.setId(id);
            return sp;

        }catch (SQLException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void createEntity(PreparedStatement ps, SpecialOffer entity) {

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
