package stream;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class Stream {
    public static void main(String[] args) {
        List<String> stringList =
                Arrays.asList("adsd", "fsdf", "afesa", "fgh", "ab");

        String rez = stringList.stream()
                .filter(x -> x.startsWith("a"))
                .map(x -> x.toUpperCase())
                .reduce("", (x,y) -> x + y);

        System.out.println("A:\n" + rez);

        System.out.println("B:\n" );

        stringList.stream()
                .filter(x -> x.startsWith("a"))
                .map(x -> x.toUpperCase())
                .forEach(System.out::println);

        System.out.println("C:\n" );

        Optional<String> stringOptional = stringList.stream()
                .filter(x -> x.startsWith("a"))
                .map(x -> x.toUpperCase())
                .reduce((x,y) -> x + y);

        if(!stringOptional.isEmpty())
            System.out.println(stringOptional.get());
        stringOptional.ifPresent(x -> System.out.println(x));
    }
}
