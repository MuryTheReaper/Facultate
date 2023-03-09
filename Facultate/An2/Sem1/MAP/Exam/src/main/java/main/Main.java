package main;

import config.ApplicationContext;
import domain.Client;
import domain.validators.ClientValidator;
import domain.validators.HotelValidator;
import domain.validators.LocationValidator;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repository.database.ClientRepository;
import repository.database.HotelRepository;
import repository.database.LocationRepository;
import repository.database.SpecialOfferRepository;
import service.*;
import ui.ClientPageController;
import ui.HotelPageController;
import domain.validators.SpecialOfferValidator;

import java.util.List;

public class Main extends Application {

    public static void main(String[] args) {
        String[] strings = {"1","2"};
        args = strings;
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        MasterService service = createMasterServiceDB();
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/pages/hotelPage.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);
        HotelPageController ctrl = fxmlLoader.getController();
        ctrl.setService(service);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Hotels");
        primaryStage.show();

        List<String> clients = getParameters().getRaw();

        for(String c : clients){
            Client client = service.getClient(Long.parseLong(c));
            Stage stage = new Stage();
            FXMLLoader fxmlLoader1 = new FXMLLoader();
            fxmlLoader1.setLocation(getClass().getResource("/pages/clientPage.fxml"));
            Scene scene1 = new Scene(fxmlLoader1.load(), 600, 400);
            ClientPageController ctrl2 = fxmlLoader1.getController();
            ctrl2.setService(service);
            ctrl2.setClient(client);
            stage.setScene(scene1);
            stage.setTitle(client.getName());
            stage.show();


        }
    }


    public static MasterService createMasterServiceDB(){

        return new MasterService(
                new LocationService(
                        new LocationRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new LocationValidator())),
                new HotelService(
                        new HotelRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new HotelValidator())
                        ),
                new SpecialOfferService(
                        new SpecialOfferRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new SpecialOfferValidator())
                        ),
                new ClientService(
                        new ClientRepository(
                                ApplicationContext.getPROPERTIES().getProperty("databaseURL"),
                                ApplicationContext.getPROPERTIES().getProperty("databaseUser"),
                                ApplicationContext.getPROPERTIES().getProperty("databasePassword"),
                                new ClientValidator())
                        )
                );
    }
}
