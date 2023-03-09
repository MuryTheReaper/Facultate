package ui;

import domain.Client;
import domain.SpecialOffer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import service.MasterService;

import java.util.Date;

public class ClientPageController {

    @FXML
    TableView<SpecialOffer> offerTable;

    @FXML
    TableColumn<SpecialOffer, Date> startColm;

    @FXML
    TableColumn<SpecialOffer, Date> endColm;

    @FXML
    TableColumn<SpecialOffer, Double> nameColm;

    @FXML
    TableColumn<SpecialOffer, Double> locationColm;

    private MasterService service;

    private ObservableList<SpecialOffer> specialOffers = FXCollections.observableArrayList();

    private Client client;


    @FXML
    public void initialize(){

        startColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Date>("startDate"));
        endColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Date>("endDate"));
        nameColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Double>("hotelId"));
        nameColm.setCellValueFactory(new PropertyValueFactory<SpecialOffer, Double>("locationId"));

        offerTable.setItems(specialOffers);
    }

    public void setService(MasterService service) {
        this.service = service;

    }

    public void setClient(Client client) {
        this.client = client;
        specialOffers.setAll(service.getSOClient(client));
    }
}
