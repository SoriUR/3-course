import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

import static com.sun.deploy.trace.Trace.flush;

/**
 * Created by Yura on 28.10.2016.
 */
 public class main {
    public static void main(String args[]) throws InterruptedException {
        ArrayList<Integer> mas = new ArrayList<>();
        Scanner in = new Scanner(System.in);
        Semaphore MainSem = new Semaphore(0);
        Semaphore WorkSem = new Semaphore(0);
        Object obj = new Object();

        System.out.println("Размерность массива");
        int n = in.nextInt();
        System.out.println("Число K");
        int k = in.nextInt();
        for(int i=0;i<n;i++){
            mas.add((4*i+11)/5);
            System.out.print(mas.get(i)+" ");
        }
        System.out.println();

        Thread work = new Thread(new work(MainSem,WorkSem,mas,"Work thread"));
        Thread sum = new Thread(new Sum(mas,obj,k,"Sum thread"));

        work.start();

        int index=0;
        while(index!=(mas.size())) {
            MainSem.acquire();
            synchronized (obj) {
                System.out.print(mas.get(index) + " ");
            }
            MainSem.release();
            WorkSem.acquire();
            index++;
            if((index+1)==k)  sum.start();
        }
    }
}
