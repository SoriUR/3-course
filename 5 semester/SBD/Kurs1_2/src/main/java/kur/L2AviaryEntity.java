package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_AVIARY", schema = "YURA_SBD", catalog = "")
public class L2AviaryEntity {
    private byte id;
    private int type;
    private int zoo_part;

    @Id
    @Column(name = "ID")
    public byte getId() {
        return id;
    }

    public void setId(byte id) {
        this.id = id;
    }

    @Basic
    @Column(name = "TYPE")
    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    @Basic
    @Column(name = "ZOO_PART")
    public int getZoo_part() {
        return zoo_part;
    }

    public void setZoo_part(int zoo_part) {
        this.zoo_part = zoo_part;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2AviaryEntity that = (L2AviaryEntity) o;

        if (id != that.id) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return (int) id;
    }

    public L2AviaryEntity(){}

    public L2AviaryEntity(Boolean ask,int l) {
        Scanner sc = new Scanner(System.in);
        System.out.println("type:");
        this.type = sc.nextInt();
        System.out.println("zoo_part:");
        this.zoo_part = sc.nextInt();
    }
}
