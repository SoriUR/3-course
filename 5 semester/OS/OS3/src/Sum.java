import java.util.ArrayList;
import java.util.Objects;

/**
 * Created by Yura on 02.11.2016.
 */
public class Sum implements Runnable {
    String name;
    ArrayList<Integer> mas;
    int sum=0;
    Object obj;
    int k;

    public Sum(ArrayList<Integer> mas, Object obj,Integer k, String name){
        this.k=k;
        this.obj=obj;
        this.mas=mas;
        this.name = name;
    }
    public void run(){
        synchronized (obj) {
            for(int i=0;i<k;i++){
                sum += mas.get(i);
            }
            System.out.println();
            System.out.println("Сумма равна " + sum);
        }
    }
}
