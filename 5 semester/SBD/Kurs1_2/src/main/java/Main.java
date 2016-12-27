/**
 * Created by alexp on 20.12.16.
 */
import kur.*;
import org.hibernate.Session;

import javax.persistence.*;
import java.lang.reflect.Field;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    static EntityManager entityManager;

    static L2AnimalClassEntity AnimalClass;
    static L2AnimalEntity Animal;
    static L2AnimalTypeEntity AnimalType;
    static L2AviaryEntity Aviary;
    static L2AviaryTypeEntity AviatyType;
    static L2FoodEntity Food;
    static L2ImageEntity Image;
    static L2StaffEntity Staff;
    static L2StaffJobEntity StaffJob;
    static L2ZooPartEntity ZooPart;
    private static ArrayList<String> tables = new ArrayList<String>();
    private static ArrayList<String> commands = new ArrayList<String>();

    private static String hql;
    private static Scanner sc = new Scanner(System.in);

    public static void main(final String[] args) throws Exception {
        EntityManagerFactory school = Persistence.createEntityManagerFactory("school");
        entityManager = school.createEntityManager();
        addNames();

        while(true) {
            int command = getCommand();
            int table = getTable();
            if(table == 12) continue;
            switch (command){
                case 1:
                    createMethod(table);
                    break;
                case 2:
                    readMethod(table);
                    break;
                case 3:
                    updateMethod(table);
                    break;
                case 4:
                    deleteMethod(table);
                    break;
            }
        }
    }

    private static void createMethod(Integer n) throws IllegalAccessException {
        Object entity=null;
        byte maxId=0;
        hql = "SELECT f FROM L2"+tables.get(n)+"Entity f";
        TypedQuery<Object[]> query = entityManager.createQuery(hql,Object[].class);
        List<Object[]> results = query.getResultList();
        for(Object someObject: results)
            for (Field field : someObject.getClass().getDeclaredFields()) {
                field.setAccessible(true); // You might want to set modifier to public first.
                Object value = field.get(someObject);
                if(field.getName().equals("id"))
                    if(maxId< ((Byte) value))
                        maxId=((Byte) value);
            }
        int len = maxId;
        len++;
        switch (n) {
            case 1:
                entity = new L2AnimalClassEntity(true,len);
                break;
            case 2:
                entity = new L2AnimalEntity(true,len);
                break;
            case 3:
                entity = new L2AnimalTypeEntity(true,len);
                break;
            case 4:
                entity = new L2AviaryEntity(true,len);
                break;
            case 5:
                entity = new L2AviaryStaffEntity(true,len);
                break;
            case 6:
                entity = new L2AviaryTypeEntity(true,len);
                break;
            case 7:
                entity = new L2FoodEntity(true,len);
                break;
            case 8:
                System.out.println("");
                break;
            case 9:
                entity = new L2StaffEntity(true,len);
                break;
            case 10:
                entity = new L2StaffJobEntity(true,len);
                break;
            case 11:
                entity = new L2ZooPartEntity(true,len);
                break;

            default:
                entity = null;
        }
        if (entity != null) {
            entityManager.getTransaction().begin();
            entityManager.persist(entity);
            entityManager.getTransaction().commit();
        }
    }

    private static void readMethod(Integer n) throws IllegalAccessException {
        hql = "SELECT f FROM L2"+tables.get(n)+"Entity f";
        TypedQuery<Object[]> query = entityManager.createQuery(hql,Object[].class);
        List<Object[]> results = query.getResultList();
        for(Object someObject: results) {
            for (Field field : someObject.getClass().getDeclaredFields()) {
                field.setAccessible(true); // You might want to set modifier to public first.
                Object value = field.get(someObject);
                if (value != null) {
                    System.out.println(field.getName() + "=" + value);
                }
            }
            System.out.println();
        }
    }

    private static void updateMethod(Integer n) throws IllegalAccessException {
        Byte pk;
        System.out.println("Введите id");
        while(true) {
            try {
                pk = sc.nextByte();
            }catch(Exception e){
                System.out.println("Введите корректный id");
                continue;
            }
            break;
        }


        Object myObject = null;
        hql = "SELECT f FROM L2"+tables.get(n)+"Entity f";
        TypedQuery<Object[]> query = entityManager.createQuery(hql,Object[].class);
        List<Object[]> results = query.getResultList();
        for(Object someObject: results)
            for (Field field : someObject.getClass().getDeclaredFields()) {
                field.setAccessible(true); // You might want to set modifier to public first.
                Object value = field.get(someObject);
                if(field.getName().equals("id"))
                    if(value.equals(pk))
                        myObject=someObject;
            }

        if(myObject==null) {
            System.out.println("Нет такого id");
            return;
        }

        entityManager.getTransaction().begin();
        hql="UPDATE L2"+tables.get(n)+"Entity AS c SET ";
        for (Field field : myObject.getClass().getDeclaredFields()) {
            field.setAccessible(true);
            if(!field.getName().equals("id"))
                hql+=field.getName()+" = :"+field.getName()+field.getName()+", ";
        }
        hql=hql.substring(0,hql.length()-2);
        hql+=" WHERE c.id = :p";
        //Query query2 = entityManager.createQuery("UPDATE L2"+tables.get(n)+"Entity c SET c.name = :newname WHERE c.id = :p");
        Query query2 = entityManager.createQuery(hql);

        for (Field field : myObject.getClass().getDeclaredFields()) {
            field.setAccessible(true);
            if(!field.getName().equals("id")) {
                String type = field.getType().getSimpleName();
                System.out.println("Введите "+field.getName());
                if (type.equals("int"))
                    query2.setParameter(field.getName() + field.getName(), sc.nextInt());
                if (type.equals("String"))
                    query2.setParameter(field.getName() + field.getName(), sc.next());
            }
        }

        query2.setParameter("p",pk);
        int updateCount = query2.executeUpdate();
        System.out.println(updateCount);
        entityManager.getTransaction().commit();
    }
    private static void deleteMethod(Integer n){
        Byte pk;
        System.out.println("Введите primary key");
        while(true) {
            try {
                pk = sc.nextByte();
            }catch(Exception e){
                System.out.println("Введите корректный primary key");
                continue;
            }
            break;
        }

        Object entity;
        switch (n) {
            case 1:
                entity = entityManager.find(L2AnimalClassEntity.class, pk);
                break;
            case 2:
                entity = entityManager.find(L2AnimalEntity.class, pk);
                break;
            case 3:
                entity = entityManager.find(L2AnimalTypeEntity.class, pk);
                break;
            case 4:
                entity = entityManager.find(L2AviaryEntity.class, pk);
                break;
            case 5:
                entity = entityManager.find(L2AviaryStaffEntity.class, pk);
                break;
            case 6:
                entity = entityManager.find(L2AviaryTypeEntity.class, pk);
                break;
            case 7:
                entity = entityManager.find(L2FoodEntity.class, pk);
                break;
            case 8:
                entity = entityManager.find(L2ImageEntity.class, pk);
                break;
            case 9:
                entity = entityManager.find(L2StaffEntity.class, pk);
                break;
            case 10:
                entity = entityManager.find(L2StaffJobEntity.class, pk);
                break;
            case 11:
                entity = entityManager.find(L2ZooPartEntity.class, pk);
                break;
            default:
                entity = null;

        }

        if (entity != null) {
            entityManager.getTransaction().begin();
            entityManager.remove(entity);
            entityManager.getTransaction().commit();
        }

    }

    private static  void addNames(){
        tables.add("");
        tables.add("AnimalClass");
        tables.add("Animal");
        tables.add("AnimalType");
        tables.add("Aviary");
        tables.add("AviaryStaff");
        tables.add("AviaryType");
        tables.add("Food");
        tables.add("Image");
        tables.add("Staff");
        tables.add("StaffJob");
        tables.add("ZooPart");

        commands.add("");
        commands.add("Create");
        commands.add("Read");
        commands.add("Update");
        commands.add("Delete");
    }


    private static int getCommand() {
        System.out.println("Выберете команду:");
        for(int a=1;a<5;a++)
            System.out.println(a+". "+commands.get(a));
        int i=0;
        while(true) {
            try {
                i = sc.nextInt();
            }
            catch (Exception e){
                System.out.println("Введите корректный номер команды");
                continue;
            }
            if (i < 1 || i > 4) {
                System.out.println("Вы ввели неверный номер команды");
            } else {
                break;
            }
        }
        return i;
    }

    private static int getTable(){
        System.out.println("Выберете Таблицу:");
        for(int a=1;a<12;a++)
            System.out.println(a+". "+tables.get(a));
        System.out.println("12. Вернуться к выбору команды");
        int i=0;
        while(true) {
            try {
                i = sc.nextInt();
            }
            catch (Exception e){
                System.out.println("Введите корректный номер таблицы");
                continue;
            }
            if (i < 1 || i > 12) {
                System.out.println("Вы ввели неверный номер таблицы");
            } else {
                break;
            }
        }
        return i;
    }

}
