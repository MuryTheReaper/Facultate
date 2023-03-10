package controller;

import domain.MessageTask;

import domain.validators.ValidationException;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import services.MessageTaskService;


import java.time.LocalDateTime;


public class EditMessageTaskController {
    @FXML
    private TextField textFieldId;
    @FXML
    private TextField textFieldDesc;
    @FXML
    private TextField textFieldFrom;
    @FXML
    private TextField textFieldTo;
    @FXML
    private TextArea textAreaMessage;
    @FXML
    private DatePicker datePickerDate;

    private MessageTaskService service;
    Stage dialogStage;
    MessageTask message;

    @FXML
    private void initialize() {
    }


    public void setService(MessageTaskService service,  Stage stage, MessageTask m) {
        this.service = service;
        this.dialogStage=stage;
        this.message=m;
        if (null != m) {
            setFields(m);
            textFieldId.setEditable(false);
        }
    }

    @FXML
    public void handleSave(){
        // TODO
        if(message == null)
            message = new MessageTask("", "", "", "", "", LocalDateTime.now());
        saveMessage(message);
        service.addMessageTaskTask(message);


    }

    private void updateMessage(MessageTask m)
    {
        // TODO
    }


    private void saveMessage(MessageTask m)
    {

        m.setId(textFieldId.getText());
        m.setDescription(textFieldDesc.getText());
        m.setFrom(textFieldFrom.getText());
        m.setTo(textFieldTo.getText());
        m.setMessage(textAreaMessage.getText());
        m.setDate(datePickerDate.getValue().atStartOfDay());




    }

    private void clearFields() {
        textFieldId.setText("");
        textFieldDesc.setText("");
        textFieldFrom.setText("");
        textFieldTo.setText("");
        textAreaMessage.setText("");
    }
    private void setFields(MessageTask s)
    {
        // TODO
    }

    @FXML
    public void handleCancel(){
        dialogStage.close();
    }
}
