package repository.database;

import domain.Entity;
import domain.validators.Validator;
import domain.validators.ValidatorException;
import repository.Repository;
import repository.RepositoryException;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;

public abstract class AbstractDBRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {

    private final String url;

    private final String username;

    private final String password;

    private final Validator<E> validator;

    public AbstractDBRepository(String url, String username, String password, Validator<E> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    /**
     * Returns the entity from the given result set.
     * @param rs the result set.
     * @return the entity.
     */
    public abstract E extractEntity (ResultSet rs);

    /**
     * Creates a prepared statement from the given entity.
     * @param ps the prepared statement.
     * @param entity the entity.
     */
    public abstract void createEntity (PreparedStatement ps, E entity);

    /**
     * Creates a sql query for updating an entity.
     * @return the sql query as string.
     */
    public abstract String getUpdateQuery();

    /**
     * Creates a sql query for inserting an entity.
     * @return the sql query as string.
     */
    public abstract String getInsertQuery();


    @Override
    public E findOne(ID id) {

        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "SELECT * FROM \"" + getEntityClass().getSimpleName() +
                    "\" WHERE \"id\" = " + id + " AND \"isDeleted\" = false";
            PreparedStatement ps = connection.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();
            if(rs.next()) {
                return extractEntity(rs);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;

    }

    @Override
    public Iterable<E> findAll() {
        Collection<E> entities = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "SELECT * FROM \"" +
                    getEntityClass().getSimpleName()+
                    "\" WHERE \"isDeleted\" = false";
            PreparedStatement ps = connection.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                E entity = extractEntity(rs);
                entities.add(entity);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }

        return entities;
    }

    @Override
    public Iterable<E> findTrueAll() {

        Collection<E> entities = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "SELECT * FROM \"" + getEntityClass().getSimpleName()+"\"";
            PreparedStatement ps = connection.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                E entity = extractEntity(rs);
                entities.add(entity);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }

        return entities;
    }

    @Override
    public E save(E entity) throws RepositoryException, ValidatorException {

        if (entity == null) {
            throw new RepositoryException("Entity must not be null");
        }

        validator.validate(entity);

        if (entity.isDeleted()) {
            return update(entity);
        }

        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sqlInsert = getInsertQuery();
            PreparedStatement ps = connection.prepareStatement(sqlInsert);
            createEntity(ps, entity);
            ps.executeUpdate();

            return null;

        }catch (SQLException e){
            e.printStackTrace();
        }

        return entity;

    }

    @Override
    public E delete(ID id) throws RepositoryException {

        if(id == null) {
            throw new RepositoryException("Id must not be null");
        }

        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "UPDATE \"" + getEntityClass().getSimpleName() +
                    "\" SET \"isDeleted\" = true WHERE \"id\" = " + id;
            PreparedStatement ps = connection.prepareStatement(sql);
            ps.executeUpdate();

            return findOne(id);

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;

    }

    @Override
    public E update(E entity) {

        if (entity == null) {
            throw new RepositoryException("Entity must not be null");
        }

        validator.validate(entity);

        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = getUpdateQuery();
            PreparedStatement ps = connection.prepareStatement(sql);
            createEntity(ps, entity);
            ps.executeUpdate();

            return null;

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return entity;
    }

}

