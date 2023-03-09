package domain.factory;

import domain.Entity;
import domain.Order;
import utils.Constants;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class EntityFactory<ID, E extends Entity<ID>> implements Factory<ID, E> {

    private static EntityFactory singleton = null;

    private EntityFactory() {
    }

    public synchronized static EntityFactory getInstance() {
        if (singleton == null) {
            singleton = new EntityFactory();
        }
        return singleton;
    }

    @Override
    public E createEntity(Class<E> strategy, List<String> attributes) {

        if (strategy == Order.class){
            //from string get all numbers in a list
            String str = attributes.get(2);
            List<String> strArr = List.of(str.split(" "));
            List<Long> numbers = new ArrayList<>();
            for (String s : strArr){
                numbers.add(Long.parseLong(s));
            }

            return (E) new Order(Long.parseLong(attributes.get(0)), numbers, LocalDateTime.parse(attributes.get(1), Constants.formatter));
        }

        return null;
    }
}
