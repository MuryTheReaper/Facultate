package utils;

import java.time.format.DateTimeFormatter;

public class Constants {

    public static DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public static enum Status {
        PLACED, PREPARING, SERVED
    }
}
