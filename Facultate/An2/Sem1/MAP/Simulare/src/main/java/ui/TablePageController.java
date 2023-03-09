package ui;

import domain.Order;
import domain.Table;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ListView;
import repository.RepositoryException;
import service.MasterService;
import service.ServiceException;

import java.util.ArrayList;
import java.util.List;

public class TablePageController {


    private MasterService service;

    private Table table;

    private ObservableList<String> menuItems = FXCollections.observableArrayList();

    private ObservableList<Order> orders;

    @FXML
    ListView<String> menuList;

    @FXML
    Button placeOrderButton;

    public void setService(MasterService service){
        this.service = service;
        menuItems.addAll(service.getAllMenuItems());
        menuList.setItems(menuItems);
        menuList.getSelectionModel().setSelectionMode(javafx.scene.control.SelectionMode.MULTIPLE);
    }

    public void setTable(Table table){
        this.table = table;
    }

    @FXML
    public void initialize(){
        menuList.setItems(menuItems);
    }

    public void onPlaceOrderButtonClicked(){

        try {

            List<String> selectedItems = menuList.getSelectionModel().getSelectedItems();

            if (selectedItems.size() == 0)
                throw new UiException("No items selected!");

            List<Long> menuItemIds = new ArrayList<>();
            for (String item : selectedItems) {
                if (!item.matches(".*\\d.*"))
                    throw new UiException("Invalid item selected!");

                //remove all after fist digit
                item = item.replaceAll("\\d.*", "");
                //remove spaces from start
                item = item.replaceAll("^\\s+", "");
                //remove spaces from end
                item = item.replaceAll("\\s+$", "");


                Long id = service.getMenuItemId(item);
                menuItemIds.add(id);
            }

            service.addOrder(table.getId(), menuItemIds);

            orders.setAll((List<Order>) service.getAllOrders());

        } catch (ServiceException | RepositoryException | UiException e) {
            Alert warring = new Alert(Alert.AlertType.ERROR,
                    e.getMessage(), ButtonType.OK);
            warring.showAndWait();

            if(warring.getResult() == ButtonType.OK)
                warring.close();
        }
    }

    public void setOrders(ObservableList<Order> orders) {
        this.orders = orders;
    }


}
