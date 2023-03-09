package service;

import domain.Hotel;
import domain.Location;
import repository.Repository;

import java.util.Collection;

public class HotelService extends BasicService<Double, Hotel> {

    public HotelService(Repository<Double, Hotel> repository) {
        super(repository);
    }

    @Override
    public Double getNextId() {
        Collection<Hotel> all = (Collection<Hotel>) findTrueAll();
        Double max = 0D;
        for (Hotel entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
}
