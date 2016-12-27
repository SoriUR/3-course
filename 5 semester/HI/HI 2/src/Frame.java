/**
 * Created by Yura on 21.11.2016.
 */
import javax.swing.*;
import java.awt.*;

public class Frame extends JFrame {
    public Frame() {
        JFrame f = new JFrame("HI1");

        f.setSize(1500,1500);
        f.setLocationRelativeTo(null);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setResizable(false);
        f.setLayout(new BorderLayout());
        ImgArea ia = new ImgArea();
        f.add(ia,BorderLayout.CENTER);
        f.setVisible(true);
        return;
    }
}
