package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_ANIMAL_TYPE", schema = "YURA_SBD", catalog = "")
public class L2AnimalTypeEntity {
    private byte id;
    private String name;
    private int Animal_class;

    @Id
    @Column(name = "ID")
    public byte getId() {
        return id;
    }

    public void setId(byte id) {
        this.id = id;
    }

    @Basic
    @Column(name = "NAME")
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2AnimalTypeEntity that = (L2AnimalTypeEntity) o;

        if (id != that.id) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) id;
        result = 31 * result + (name != null ? name.hashCode() : 0);
        return result;
    }

    public L2AnimalTypeEntity(){}

    public L2AnimalTypeEntity(Boolean ask,int l) {
        this.id = (byte)l;
        Scanner sc = new Scanner(System.in);
        System.out.println("Name:");
        this.name = sc.next();
        System.out.println("Animal_class:");
        this.Animal_class = sc.nextInt();
    }

    @Basic
    @Column(name = "ANIMAL_CLASS")
    public int getAnimal_class() {
        return Animal_class;
    }

    public void setAnimal_class(int animal_class) {
        Animal_class = animal_class;
    }
}
