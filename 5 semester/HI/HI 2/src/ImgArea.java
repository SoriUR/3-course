import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import java.nio.Buffer;
import java.util.Map;

/**
 * Created by Yura on 20.11.2016.
 */
public class ImgArea extends JPanel {

    private BufferedImage image;
    private BufferedImage oldImage;
    private boolean changed=false;
    private boolean saved=false;

    public ImgArea(){
        this.setBackground(Color.WHITE);

        try {
            image = ImageIO.read(new File("src/img/img.bmp"));
            oldImage = ImageIO.read(new File("src/img/img.bmp"));
        } catch (IOException ex) {}

        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(changed)
                    repaint();
                else
                    ChangeBrightness();
            }
        });

    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        if(changed) {
            g.drawImage(oldImage, getWidth() / 2 - image.getWidth() / 2, getHeight() / 2 - image.getHeight() / 2, this);
            changed=false;
        }
        else {
            g.drawImage(image, getWidth() / 2 - image.getWidth() / 2, getHeight() / 2 - image.getHeight() / 2, this);
            changed=true;
        }
    }

    private void ChangeBrightness(){
        RescaleOp rescale = new RescaleOp(1.5f,20,null);
        image=rescale.filter(oldImage,null);
//        int[] argb = new int[image.getWidth()*image.getHeight()];
//        image.getRGB(0,0,image.getWidth(),image.getHeight(),argb,0,image.getWidth());
//        for (int i=0; i<argb.length;i++){
////            int r = (argb[i]>>16)&0xFF;
////            int g = (argb[i]>>8)&0xFF;
////            int b = argb[i]&0xFF;
////            argb[i]=(int)(0.2126 * 255  + 0.7152 * 255 + 0.0722 * 255);
//        }
//        image.setRGB(0,0,image.getWidth(),image.getHeight(),argb,0,image.getWidth());
        if(!saved){
            saved = true;
            try {
                ImageIO.write(image, "PNG", new File("src/img/new.bmp"));
            } catch (IOException e) {}
        }
        repaint();
    }

//        int[] pixels = new int[w*h*3];
//        raster.getPixels(0, 0, w, h, pixels);
//
//        for (int i=0;i<pixels.length; i+=3)
//        {
//            int r = pixels[i];
//            int g = pixels[i+1];
//            int b = pixels[i+2];
//
//
//            if (r>255) r=255;
//            if (g>255) g=255;
//            if (b>255) b=255;
//            if (r<0) r=0;
//            if (g<0) g=0;
//            if (b<0) b=0;
//
//
//            pixels[i] = r;
//            pixels[i+1]= g;
//            pixels[i+2] = b;
//        }
//        raster.setPixels(0, 0, w, h, pixels);
//    }
}
