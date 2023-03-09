package service;

import domain.Location;
import domain.SpecialOffer;
import repository.Repository;

import java.util.Collection;

public class SpecialOfferService extends BasicService<Double, SpecialOffer> {

    public SpecialOfferService(Repository<Double, SpecialOffer> repository) {
        super(repository);
    }

    @Override
    public Double getNextId() {
        Collection<SpecialOffer> all = (Collection<SpecialOffer>) findTrueAll();
        Double max = 0D;
        for (SpecialOffer entity : all) {
            if (entity.getId() > max )
                max = entity.getId();
        }
        return max+1;
    }
}
