package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_ZOO_PART", schema = "YURA_SBD", catalog = "")
public class L2ZooPartEntity {
    private byte id;
    private String name;

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

        L2ZooPartEntity that = (L2ZooPartEntity) o;

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

    public L2ZooPartEntity(){}

    public L2ZooPartEntity(Boolean ask,int l) {
        this.id = (byte)l;
        Scanner sc = new Scanner(System.in);
        System.out.println("name:");
        this.name = sc.next();
    }
}