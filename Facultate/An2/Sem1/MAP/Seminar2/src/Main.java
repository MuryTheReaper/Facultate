import map.MyMap;
import model.Student;

import java.lang.reflect.Array;
import java.util.*;

public class Main {
    public static void main(String[] args) {

        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Alex", 4.5f);
        Student s4 = new Student("Bogdan", 5.0f);
        //System.out.println(s1.toString());

        HashSet<Student> hashSet = new HashSet<>();

        hashSet.addAll(Arrays.asList(s1,s2,s3));

        System.out.println("\nhashSet");
        System.out.println(hashSet);

        TreeSet<Student> treeSet = new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.getNume().compareTo(o2.getNume());
            }
        });

        treeSet.addAll(Arrays.asList(s1,s2,s3));

        System.out.println("\ntreeSet");
        System.out.println(treeSet);


        HashMap<String, Student> hashMap = new HashMap<>();
        hashMap.put(s1.getNume(), s1);
        hashMap.put(s2.getNume(), s2);
        hashMap.put(s3.getNume(), s3);

        System.out.println("\nhashMap");

        for (Map.Entry<String, Student> e : hashMap.entrySet()){
            System.out.println(e.getKey()+" "+e.getValue());
        }

        TreeMap<String, Student> treeMap = new TreeMap<>();
        treeMap.put(s1.getNume(), s1);
        treeMap.put(s2.getNume(), s2);
        treeMap.put(s3.getNume(), s3);

        System.out.println("\nTreeMap");

        for (Map.Entry<String, Student> e : treeMap.entrySet()){
            System.out.println(e.getKey()+" "+e.getValue());
        }

        MyMap map = new MyMap();
        map.add(s1);
        map.add(s2);
        map.add(s3);
        map.add(s4);
        System.out.println("\nMyMap");
        map.afisare();
    }
}