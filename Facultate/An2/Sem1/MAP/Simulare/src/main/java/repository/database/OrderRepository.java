package repository.database;

import domain.Order;
import domain.validators.Validator;
import domain.validators.ValidatorException;
import repository.RepositoryException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class OrderRepository implements repository.Repository<Long, Order> {

    private final String url;
    private final String password;
    private final String username;

    private final Validator<Order> validator;


    public OrderRepository(String url, String username, String password, Validator<Order> validator) {
        this.url = url;
        this.password = password;
        this.username = username;
        this.validator = validator;

    }

    @Override
    public Order findOne(Long aLong) {
        return null;
    }

    public Iterable<Order> findAll() {
        Collection<Order> entities = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql =
                    "SELECT * FROM \"Order\" " +
                            "INNER JOIN \"OrderItems\" ON \"Order\".id = \"OrderItems\".\"orderId\" " +
                            "WHERE \"Order\".\"isDeleted\" = false";
            PreparedStatement ps = connection.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();

            rs.next();
            List<Long> menuItems = new ArrayList<>();
            long id = rs.getLong("id");
            long tableId = rs.getLong("tableId");
            long menuItemId = rs.getLong("menuItemId");
            LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();
            boolean isDeleted = rs.getBoolean("isDeleted");
            menuItems.add(menuItemId);


            while (rs.next()) {
                if (id == rs.getLong("id")) {
                    menuItems.add(rs.getLong("menuItemId"));
                } else {
                    Order entity = new Order(tableId, menuItems, date);
                    entity.setId(id);
                    entity.setDeleted(isDeleted);
                    entities.add(entity);
                    menuItems.clear();
                    id = rs.getLong("id");
                    tableId = rs.getLong("tableId");
                    menuItemId = rs.getLong("menuItemId");
                    date = rs.getTimestamp("date").toLocalDateTime();
                    isDeleted = rs.getBoolean("isDeleted");
                    menuItems.add(menuItemId);
                }
            }
            Order entity = new Order(tableId, menuItems, date);
            entity.setId(id);
            entity.setDeleted(isDeleted);
            entities.add(entity);

        }catch (SQLException e){
            e.printStackTrace();
        }

        return entities;
    }

    @Override
    public Iterable<Order> findTrueAll() {
        return null;
    }

    public Order save(Order entity) throws RepositoryException, ValidatorException{

        if (entity == null) {
            throw new RepositoryException("Entity must not be null");
        }

        validator.validate(entity);

        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "INSERT INTO \"Order\" (\"tableId\", date, \"isDeleted\", id, status) VALUES (?, ?, ?, ?, ?)";
            PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
            ps.setLong(1, entity.getTableId());
            ps.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            ps.setBoolean(3, entity.isDeleted());
            ps.setLong(4, entity.getId());
            ps.setString(5, entity.getStatus().toString());
            ps.executeUpdate();
            ResultSet rs = ps.getGeneratedKeys();
            rs.next();
            entity.setId(rs.getLong(1));
            for (Long menuItemId : entity.getMenuItemIds()) {
                sql = "INSERT INTO \"OrderItems\" (\"orderId\", \"menuItemId\") VALUES (?, ?)";
                ps = connection.prepareStatement(sql);
                ps.setLong(1, entity.getId());
                ps.setLong(2, menuItemId);
                ps.executeUpdate();
            }
    } catch (SQLException e) {
            e.printStackTrace();
        }
        return entity;
    }

    @Override
    public Order delete(Long aLong) throws RepositoryException {
        return null;
    }

    @Override
    public Order update(Order entity) {
        return null;
    }

    @Override
    public Class<Order> getEntityClass() {
        return Order.class;
    }

}
