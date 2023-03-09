package service;

import domain.MenuItem;
import domain.Order;
import repository.Repository;

import java.util.Collection;

public class OrderService extends BasicService<Long, Order>{

    public OrderService(Repository<Long, Order> repository) {
        super(repository);
    }
    @Override
    public Long getNextId() {
        Collection<Order> all = (Collection<Order>) findAll();
        Long max = 0L;
        for (Order entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
    
}
