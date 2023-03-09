module main.demo5 {
    requires javafx.controls;
    requires javafx.fxml;


    opens main.demo5 to javafx.fxml;
    exports main.demo5;
}