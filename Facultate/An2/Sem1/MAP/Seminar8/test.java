import javax.swing.*;
import java.awt.*;

public class Main extends Application {
    @Override
    public void start(Stage stage) {
        GroupLayout.Group root = new GroupLayout.Group();
        Scene scene = new Scene(root, 500, 500, Color.PINK);
        stage.setTitle("Welcome to JavaFX!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);//se creazaun obiectde tip Application}}
    }
}