package kur;

import javax.persistence.*;
import java.util.Arrays;

/**
 * Created by alexp on 20.12.16.
 */
@Entity
@Table(name = "L2_IMAGE", schema = "YURA_SBD", catalog = "")
public class L2ImageEntity {
    private byte id;
    private byte[] photo;

    @Id
    @Column(name = "ID")
    public byte getId() {
        return id;
    }

    public void setId(byte id) {
        this.id = id;
    }

    @Basic
    @Column(name = "PHOTO")
    public byte[] getPhoto() {
        return photo;
    }

    public void setPhoto(byte[] photo) {
        this.photo = photo;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        L2ImageEntity that = (L2ImageEntity) o;

        if (id != that.id) return false;
        if (!Arrays.equals(photo, that.photo)) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) id;
        result = 31 * result + Arrays.hashCode(photo);
        return result;
    }
}
