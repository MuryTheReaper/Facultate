package service;

import domain.Location;
import repository.Repository;

import java.util.Collection;

public class LocationService extends BasicService<Double, Location> {

    public LocationService(Repository<Double, Location> repository) {
        super(repository);
    }

    @Override
    public Double getNextId() {
        Collection<Location> all = (Collection<Location>) findTrueAll();
        Double max = 0D;
        for (Location entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
}
