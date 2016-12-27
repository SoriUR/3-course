package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_AVIARY_STAFF", schema = "YURA_SBD", catalog = "")
public class L2AviaryStaffEntity {
    private byte id;
    private int staff_id;
    private int aviary_id;

    @Id
    @Column(name = "ID")
    public byte getId() {
        return id;
    }

    public void setId(byte id) {
        this.id = id;
    }

    @Basic
    @Column(name = "STAFF_ID")
    public int getStaff_id() {
        return staff_id;
    }

    public void setStaff_id(int staff_id) {
        this.staff_id = staff_id;
    }

    @Basic
    @Column(name = "AVIARY_ID")
    public int getAviary_id() {
        return aviary_id;
    }

    public void setAviary_id(int aviary_id) {
        this.aviary_id = aviary_id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2AviaryStaffEntity that = (L2AviaryStaffEntity) o;

        if (id != that.id) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return (int) id;
    }

    public L2AviaryStaffEntity(){}

    public L2AviaryStaffEntity(Boolean ask,int l) {
        this.id = (byte)l;
        Scanner sc = new Scanner(System.in);
        System.out.println("staff_id:");
        this.staff_id = sc.nextInt();
        System.out.println("aviary_id:");
        this.aviary_id = sc.nextInt();
    }
}
