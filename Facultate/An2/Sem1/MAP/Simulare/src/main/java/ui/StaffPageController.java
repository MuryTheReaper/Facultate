package ui;

import domain.Order;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Callback;
import service.MasterService;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;

public class StaffPageController {

    @FXML
    TableView<Order> orderTable;

    @FXML
    TableColumn<Order, Long> tableColm;

    @FXML
    TableColumn<Order, LocalDateTime> dateColm;

    @FXML
    TableColumn<Order, String> itemsColm;

    private ObservableList<Order> orders;

    private MasterService service;

    public void setService(MasterService service){
        this.service = service;
    }

    @FXML
    public void initialize(){
        tableColm.setCellValueFactory(new PropertyValueFactory<Order, Long>("tableId"));
        dateColm.setCellValueFactory(new PropertyValueFactory<Order, LocalDateTime>("date"));
        itemsColm.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<Order, String>, ObservableValue<String>>() {
            @Override
            public ObservableValue<String> call(TableColumn.CellDataFeatures<Order, String> param) {

                    String items = service.getMenuItemsNames(param.getValue().getMenuItemIds());

                    return new javafx.beans.property.SimpleStringProperty(items);
            }
        });

        orderTable.setItems(orders);
    }


    public void setOrders(ObservableList<Order> orders) {
        this.orders = orders;
        orders.setAll((List<Order>) service.getAllOrders());
        orderTable.setItems(orders);
    }


}
