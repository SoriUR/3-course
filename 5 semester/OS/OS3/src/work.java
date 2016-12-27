import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.Delayed;
import java.util.concurrent.Semaphore;

/**
 * Created by Yura on 02.11.2016.
 */
public class work implements Runnable {
    Semaphore MainSem;
    Semaphore WorkSem;
    ArrayList<Integer>  list;
    String name;

    work(Semaphore MainSem,Semaphore WorkSem,ArrayList<Integer> list, String name){
        this.list=list;
        this.MainSem=MainSem;
        this.WorkSem=WorkSem;
        this.name= name;
    }

    public void run(){
        Scanner in = new Scanner(System.in);
        int time=0;
        WorkSem.release();
        try {
            WorkSem.acquire();
            System.out.println("Время ожидания");
            time = in.nextInt();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


        int botMarker=0;
        int watched = 0;
        int topMarker = 0;
        while(watched!=list.size()){
            int cur = list.get(topMarker);
            int indexOf = list.lastIndexOf(cur);
            if(topMarker!=indexOf){
                list.remove(topMarker);
                list.remove(indexOf-1);
                list.add(botMarker,cur);

                notifyMain(time);

                list.add(botMarker,cur);
                botMarker++;
                topMarker+=2;
                watched++;
            }
            else{
                list.add(cur);
                list.remove(topMarker);
            }
            watched++;
        }

        while(botMarker!=list.size()+1){
            notifyMain(time);
            botMarker++;
        }

    }
    void notifyMain(int time){
        MainSem.release();
        try {
            Thread.sleep(time*1000);
            MainSem.acquire();
            WorkSem.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
