package ui;

import domain.Hotel;
import domain.Location;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import service.LocationService;
import service.MasterService;

import java.io.IOException;
import java.util.List;
import java.util.function.Predicate;

public class HotelPageController {

    @FXML
    TableView<Hotel> hotelTable;

    @FXML
    TableColumn<Hotel, String> nameColm;

    @FXML
    TableColumn<Hotel, Integer> roomsColm;

    @FXML
    TableColumn<Hotel, Double> priceColm;

    @FXML
    TableColumn<Hotel, String> typeColm;

    @FXML
    ComboBox<Location> comboBox;

    private ObservableList<Location> locations = FXCollections.observableArrayList();
    private ObservableList<Hotel> hotels = FXCollections.observableArrayList();

    private MasterService service;


    @FXML
    public void initialize(){

        nameColm.setCellValueFactory(new PropertyValueFactory<Hotel, String>("hotelName"));
        roomsColm.setCellValueFactory(new PropertyValueFactory<Hotel, Integer>("noRooms"));
        priceColm.setCellValueFactory(new PropertyValueFactory<Hotel, Double>("pricePerNight"));
        typeColm.setCellValueFactory(new PropertyValueFactory<Hotel, String>("type"));

        hotelTable.setItems(hotels);
        comboBox.setItems(locations);
        comboBox.valueProperty().addListener(o -> comboBoxHandler());


    }

    public void setService(MasterService service){
        this.service = service;
        hotels.setAll((List<Hotel>) service.getAllHotels());
        locations.setAll((List<Location>) service.getAllLocations());

    }

    private void comboBoxHandler(){

        List<Hotel> hotellist = (List<Hotel>) service.getAllHotels();
        hotellist.removeIf(h -> !h.getLocationId().equals(comboBox.getValue().getId()));
        hotels.setAll(hotellist);
    }


    public void onMouseClicked() throws IOException {

        Stage stage = new Stage();
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/pages/offerPage.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);
        OfferPageController ctrl = fxmlLoader.getController();
        ctrl.setService(service);
        ctrl.setHotel(hotelTable.selectionModelProperty().getValue().getSelectedItem());
        stage.setScene(scene);
        stage.setTitle("Hotels");
        stage.show();

    }


}
