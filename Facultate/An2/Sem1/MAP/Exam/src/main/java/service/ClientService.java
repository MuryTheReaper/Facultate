package service;

import domain.Client;
import domain.Hotel;
import repository.Repository;

import java.util.Collection;

public class ClientService extends BasicService<Long, Client> {

    public ClientService(Repository<Long, Client> repository) {
        super(repository);
    }

    @Override
    public Long getNextId() {
        Collection<Client> all = (Collection<Client>) findTrueAll();
        Long max = 0L;
        for (Client entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
}
