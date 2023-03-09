package map;

import model.Student;

import java.util.*;

public class MyMap {

    private Map<Integer, List<Student>> studentMap;

    public MyMap(){
        studentMap = new TreeMap<>(new Comparator());
    }

    static class Comparator implements java.util.Comparator<Integer>{
        @Override
        public int compare(Integer o1, Integer o2) {
            return o2-o1;
        }
    }

    public void add(Student student){
        Integer mediaRotunjita = student.getMediaRotunjita();

        List<Student> list = studentMap.get(mediaRotunjita);

        if(list == null){
            list = new ArrayList<Student>();
            studentMap.put(mediaRotunjita, list);
        }
        list.add(student);
    }

    public void afisare(){
        for(Map.Entry<Integer, List<Student>> e : studentMap.entrySet()){
            System.out.println(e.getKey()+ " " + e.getValue());
        }
    }

    public Set<Map.Entry<Integer, List<Student>>> getEntries(){
        return studentMap.entrySet();
    }

}
