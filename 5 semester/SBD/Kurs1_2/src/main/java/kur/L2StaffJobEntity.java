package kur;

import javax.persistence.*;
import java.util.Scanner;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_STAFF_JOB", schema = "YURA_SBD", catalog = "")
public class L2StaffJobEntity {
    private byte id;
    private String name;
    private int salary;

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
    @Column(name = "SALARY")
    public int getSalary() {
        return salary;
    }

    public void setSalary(int salary) {
        this.salary = salary;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2StaffJobEntity that = (L2StaffJobEntity) o;

        if (id != that.id) return false;
        if (salary != that.salary) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) id;
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (int) salary;
        return result;
    }

    public L2StaffJobEntity(){}

    public L2StaffJobEntity(Boolean ask,int l) {
        this.id = (byte)l;
        Scanner sc = new Scanner(System.in);
        System.out.println("name:");
        this.name = sc.next();
        System.out.println("salary:");
        this.salary = sc.nextInt();
    }
}
