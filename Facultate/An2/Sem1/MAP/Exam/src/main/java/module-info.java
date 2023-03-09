module main{
    requires javafx.controls;
    requires javafx.fxml;

    requires java.sql;

    opens main to javafx.fxml, javafx.graphics;
    exports main to javafx.fxml, javafx.graphics;
    exports ui to javafx.fxml;
    opens ui to javafx.fxml;
    opens domain to javafx.base;
    opens domain.validators to javafx.base;
}