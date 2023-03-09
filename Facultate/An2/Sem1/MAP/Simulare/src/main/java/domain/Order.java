package domain;

import utils.Constants;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Order extends Entity<Long>{

    private Long tableId;

    private List<Long> menuItemIds;

    private LocalDateTime date;

    private Constants.Status status;

    public Order(Long tableId, List<Long> menuItemIds, LocalDateTime date) {
        this.tableId = tableId;
        this.menuItemIds = new ArrayList<>();
        this.menuItemIds.addAll(menuItemIds);
        this.date = date;
        this.status = Constants.Status.PLACED;
    }

    public Order(Long id, Long tableId, List<Long> menuItemIds, LocalDateTime date) {
        this.setId(id);
        this.tableId = tableId;
        this.menuItemIds = menuItemIds;
        this.date = date;
        this.status = Constants.Status.PLACED;
    }

    public Long getTableId() {
        return tableId;
    }

    public void setTableId(Long tableId) {
        this.tableId = tableId;
    }

    public List<Long> getMenuItemIds() {
        return menuItemIds;
    }

    public void setMenuItemIds(List<Long> menuItemIds) {
        this.menuItemIds = menuItemIds;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Constants.Status getStatus() {
        return status;
    }

    public void setStatus(Constants.Status status) {
        this.status = status;
    }
}
