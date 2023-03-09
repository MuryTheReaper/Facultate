package service;

import domain.MenuItem;
import domain.Table;
import repository.Repository;

import java.util.Collection;

public class MenuService extends BasicService<Long, MenuItem> {

    public MenuService(Repository<Long, MenuItem> repository) {
        super(repository);
    }

    @Override
    public Long getNextId() {
        Collection<MenuItem> all = (Collection<MenuItem>) findTrueAll();
        Long max = 0L;
        for (MenuItem entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
}
