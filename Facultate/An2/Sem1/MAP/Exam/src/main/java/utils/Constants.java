package utils;

import java.time.format.DateTimeFormatter;

public class Constants {

    public static DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public static enum Type {
        FAMILY, TEENAGERS, OLDPEOPLE
    }

    public static enum Hobbies {
        READING, MUSIC, HIKING, WALKING, EXTREME_SPORTS
    }
}
