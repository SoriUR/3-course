package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_STAFF", schema = "YURA_SBD", catalog = "")
public class L2StaffEntity {
    private byte id;
    private String name;
    private int job;
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
    @Column(name = "NAME")
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Basic
    @Column(name = "JOB")
    public int getJob() {
        return job;
    }

    public void setJob(int job) {
        this.job = job;
    }

    @Basic
    @Column(name = "IMAGE")
    public int getImage() {
        return image;
    }

    public void setImage(int image) {
        this.image = image;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2StaffEntity that = (L2StaffEntity) o;

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

    public L2StaffEntity(){}

    public L2StaffEntity(Boolean ask,int l) {
        this.id = (byte)l;
        Scanner sc = new Scanner(System.in);
        System.out.println("name:");
        this.name = sc.next();
        System.out.println("job:");
        this.job = sc.nextInt();
        System.out.println("image:");
        this.image = sc.nextInt();
    }
}
