package service;

import domain.MenuItem;
import domain.Order;
import domain.Table;
import javafx.collections.ObservableList;
import utils.Constants;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class MasterService {

    private final TableService tableService;
    private final MenuService menuService;

    private final OrderService orderService;

    public MasterService(TableService tableService, MenuService menuService, OrderService orderService) {
        this.tableService = tableService;
        this.menuService = menuService;
        this.orderService = orderService;
    }

    public Iterable<Table> getAllTables() {
        return tableService.findAll();
    }

    public List<String> getAllMenuItems() {
        List<MenuItem> items = (List<MenuItem>) menuService.findAll();

        List<String> types = items.stream()
                .map(MenuItem::getCategory)
                .distinct()
                .toList();

        List<String> result = new ArrayList<>();
        for (String type : types) {
            result.add(type);
            for (MenuItem item : items) {
                if (item.getCategory().equals(type))
                    result.add("    " + item.getItem() + " " + item.getPrice() + " " + item.getCurrency());
            }
        }

        return result;
    }

    public String getMenuItemsNames(List<Long> menuItems) {
        StringBuilder result = new StringBuilder();
        for (Long menuItem : menuItems) {
            result.append(menuService.findOne(menuItem).getItem()).append(", ");
        }
        result.deleteCharAt(result.length() - 2);
        return result.toString();
    }


    public Iterable<Order> getAllOrders() {
        return orderService.findAll();
    }

    public Long getMenuItemId(String menuItem) {

        List<MenuItem> items = (List<MenuItem>) menuService.findAll();

        for (MenuItem item : items) {
            if (item.getItem().equals(menuItem))
                return item.getId();
        }

        return null;

    }

    public void addOrder(Long tableId, List<Long> menuItems) {

        String date = LocalDateTime.now().format(Constants.formatter);
        List<String> attributes = new ArrayList<>();
        attributes.add(tableId.toString());
        attributes.add(date);
        //construct string
        StringBuilder sb = new StringBuilder();
        for (Long menuItem : menuItems) {
            sb.append(menuItem).append(" ");
        }
        attributes.add(sb.toString());
        orderService.save(attributes);
    }
}
