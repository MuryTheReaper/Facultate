package repository.database;

import domain.Client;
import domain.Location;
import domain.validators.Validator;
import utils.Constants;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ClientRepository extends AbstractDBRepository<Long, Client> {

    public ClientRepository(String url, String username, String password, Validator<Client> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Class<Client> getEntityClass() {
        return Client.class;
    }

    @Override
    public Client extractEntity(ResultSet rs) {
        try {
            Long id = rs.getLong("id");
            String name = rs.getString("name");
            int fg = rs.getInt("fidelityGrade");
            int varsta = rs.getInt("varsta");
            String h = rs.getString("hobbies");
            Constants.Hobbies hobbies = null;
            if (h.equals("READING"))
                hobbies = Constants.Hobbies.READING;
            if (h.equals("MUSIC"))
                hobbies = Constants.Hobbies.MUSIC;
            Client client = new Client(name, fg, varsta,hobbies);
            client.setId(id);
            return client;

        }catch (SQLException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void createEntity(PreparedStatement ps, Client entity) {

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
