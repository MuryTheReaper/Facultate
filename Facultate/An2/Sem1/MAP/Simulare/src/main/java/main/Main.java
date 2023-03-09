package main;

import config.ApplicationContext;
import domain.Order;
import domain.Table;
import domain.validators.MenuValidator;
import domain.validators.OrderValidator;
import domain.validators.TableValidator;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import repository.database.MenuRepository;
import repository.database.OrderRepository;
import repository.database.TableRepository;
import service.MasterService;
import service.MenuService;
import service.OrderService;
import service.TableService;
import ui.StaffPageController;
import ui.TablePageController;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class Main extends Application {

    public static void main(String[] args) throws IOException {

        launch(args);
    }

    @Override
    public void start(Stage pstage) throws Exception{

        MasterService masterService = createMasterServiceDB();
        List<Table> tables = (List<Table>) masterService.getAllTables();
        ObservableList<Order> orders = FXCollections.observableArrayList();

        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/pages/staffPage.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);
        StaffPageController ctrl = fxmlLoader.getController();
        ctrl.setService(masterService);
        ctrl.setOrders(orders);
        pstage.setTitle("Staff");
        pstage.setScene(scene);
        pstage.show();

        for (Table table : tables){

            Stage stage = new Stage();
            fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/pages/tablePage.fxml"));
            scene = new Scene(fxmlLoader.load(), 600, 400);
            TablePageController tctrl = fxmlLoader.getController();
            tctrl.setTable(table);
            tctrl.setService(masterService);
            tctrl.setOrders(orders);
            stage.setTitle("Table " + table.getId());
            stage.setScene(scene);
            stage.show();

        }

    }

    public static MasterService createMasterServiceDB(){

        return new MasterService(
                new TableService(
                        new TableRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new TableValidator())),
                new MenuService(
                        new MenuRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new MenuValidator())
                        ),
                new OrderService(
                        new OrderRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new OrderValidator())
                        )
        );

    }
}
