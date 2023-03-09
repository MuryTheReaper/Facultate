package controller;

import javafx.fxml.FXML;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import service.ServiceManager;

import java.io.IOException;


public class loginPage {

    @FXML
    TextField userTxt;

    @FXML
    Button loginButton;

    @FXML
    public void loginClicked() throws IOException {

        if(userTxt.getText().equals(""))
            return;

        Stage newStage = new Stage();
        FXMLLoader loader=new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/notaView.fxml"));
        AnchorPane root=loader.load();

        NotaController ctrl=loader.getController();
        ctrl.setService(new ServiceManager());
        ctrl.setUser("Salut, " + userTxt.getText() + "!");

        newStage.setScene(new Scene(root, 700, 500));
        newStage.setTitle("New World");
        newStage.show();

        ((Stage) (loginButton.getScene().getWindow())).close();

    }





}
