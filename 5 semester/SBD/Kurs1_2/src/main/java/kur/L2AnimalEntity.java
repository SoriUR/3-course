package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_ANIMAL", schema = "YURA_SBD", catalog = "")
public class L2AnimalEntity {
    private byte id;
    private int type;
    private int aviary;
    private int image;

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
    @Column(name = "AVIARY")
    public int getAviary() {
        return aviary;
    }

    public void setAviary(int aviary) {
        this.aviary = aviary;
    }

    @Basic
    @Column(name = "IMAGE")
    public int getImage() {
        return image;
    }

    public void setImage(int image) { this.image = image;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2AnimalEntity that = (L2AnimalEntity) o;

        if (id != that.id) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return (int) id;
    }

    public L2AnimalEntity(){}

    public L2AnimalEntity(Boolean ask,int l) {
        this.id = (byte)l;
        Scanner sc = new Scanner(System.in);
        System.out.println("type:");
        this.type = sc.nextInt();
        System.out.println("aviary:");
        this.aviary = sc.nextInt();
        System.out.println("image:");
        this.image = sc.nextInt();
    }
}
