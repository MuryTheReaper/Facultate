package ui;

import domain.Hotel;
import domain.Location;
import domain.SpecialOffer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import service.MasterService;

import java.util.Date;
import java.util.List;

public class OfferPageController {

    @FXML
    TableView<SpecialOffer> offerTable;

    @FXML
    TableColumn<SpecialOffer, Date> startColm;

    @FXML
    TableColumn<SpecialOffer, Date> endColm;

    @FXML
    TableColumn<SpecialOffer, Integer> percentColm;

    @FXML
    DatePicker startPicker;

    @FXML
    DatePicker endPicker;

    private MasterService service;

    private Hotel hotel;

    private ObservableList<SpecialOffer> specialOffers = FXCollections.observableArrayList();


    @FXML
    public void initialize(){

        startColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Date>("startDate"));
        endColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Date>("endDate"));
        percentColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Integer>("percents"));

        offerTable.setItems(specialOffers);

        startPicker.valueProperty().addListener(o -> dateHandler());
        endPicker.valueProperty().addListener(o -> dateHandler());


    }

    public void setService(MasterService service){
        this.service = service;
    }

    public void setHotel(Hotel hotel) {
        this.hotel = hotel;
    }

    private void dateHandler(){

        if(startPicker.getValue()!=null && endPicker.getValue()!= null){
            List<SpecialOffer> sp = (List<SpecialOffer>) service.getHotelOffersByDate(hotel.getId(), java.sql.Date.valueOf(startPicker.getValue()), java.sql.Date.valueOf(endPicker.getValue()));
            specialOffers.setAll(sp);
        }
    }


}
