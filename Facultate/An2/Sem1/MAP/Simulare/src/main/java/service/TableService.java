package service;

import domain.Table;
import repository.Repository;

import java.util.Collection;

public class TableService extends BasicService<Long, Table> {

    public TableService(Repository repository) {
        super(repository);
    }

    @Override
    public Long getNextId() {
        Collection<Table> all = (Collection<Table>) findTrueAll();
        Long max = 0L;
        for (Table entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
}
