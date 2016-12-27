import java.util.*;

/**
 * Created by Yura on 27.09.2016.
 */
public class Main {
    private static int n = 22;
    private static int limit=2;
    private static int RRmax=0, SRTmax=0;
    private static ArrayList<Proc> rr = new ArrayList<>();
    private static ArrayList<Proc> srt = new ArrayList<>();
    private static Queue<Proc> q = new LinkedList<>();
    public static void main(String args[]){
        BuildMas();
        for (Proc p:srt)
            System.out.println(p.getName()+"|"+p.getAppearTime()+"|"+p.getPerfTime());
        SRT();
        RR();
        double RRavrTurn=0, SRTavrTurn=0;
        double RRavrWait=0, SRTavrWait=0;
        for(int i=0;i<n;i++) {
            RRavrTurn = rr.get(i).getTurnTime() + RRavrTurn;
            RRavrWait = rr.get(i).getWaitTime() + RRavrWait;
            SRTavrTurn = srt.get(i).getTurnTime() + SRTavrTurn;
            SRTavrWait = srt.get(i).getWaitTime() + SRTavrWait;
        }
        RRavrWait/=n;
        RRavrTurn/=n;
        SRTavrWait/=n;
        SRTavrTurn/=n;
        System.out.println("RR  Среднее время оборота:"+RRavrTurn+"  Среднее время ожидания:"+RRavrWait+"  Макс чередь" + RRmax);
        System.out.println("SRT Среднее время оборота:"+SRTavrTurn+" Среднее время ожидания:"+SRTavrWait+" Макс чередь" + SRTmax);
    }


    private static void SRT(){
        int i=0;
        Proc next;
        Proc current=null;
        int finished = 0;
        for(int timer=0;;timer++){
            if(i<n) {
                next = srt.get(i);

                if (timer == next.getAppearTime()) {
                    if (current == null)
                        current = next;
                    else if (next.getPerfTime() < current.getPerfTime()) {
                        q.add(current);
                        if(q.size()>SRTmax) SRTmax=q.size();
                        current = next;
                    } else
                        q.add(next);
                    i++;
                }


                if (current == null) continue;
            }

            current.DecrPerfTime();


            for(Proc p:q){
               p.IncWaitingTime();
            }

            if(current.getPerfTime()==0){
                finished++;
                if (finished==n) break;
                current = FindMin();
                q.remove(current);
            }
        }

        for(Proc p: srt){
            p.UpdateTurnTime();
        }
    }

    private static Proc FindMin(){
        if(q.isEmpty()) return null;
        Proc min = new Proc(-1,0,12);
        for(Proc p:q){
            if (p.getPerfTime()< min.getPerfTime())
                min = p;
        }
        return min;
    }

    private static void RR(){
        int num=0;
        int timer=-1;
        int inProg = 0;
        int finished = 0;
        Proc current=null;
        while(true) {
            timer++;

            if(num<n && timer==rr.get(num).getAppearTime()) {
                q.add(rr.get(num++));
                if(q.size()>RRmax) RRmax=q.size();
            }

            if(inProg==0)
                current = q.poll();

            if(current==null) {
                continue;
            }

            if(inProg!=limit) {
                current.DecrPerfTime();
                inProg++;
            }

            for(Proc p:q){
                p.IncWaitingTime();
            }

            if (current.getPerfTime() == 0){
                inProg=0;
                current=null;
                if(++finished==n) break;
            }

            if(inProg==limit) {
                inProg=0;
                q.add(current);
                current=null;
            }
        }

        for(Proc p: rr){
            p.UpdateTurnTime();
        }
    }

    private static void BuildMas(){
        rr.add(new Proc(0,0,9));
        rr.add(new Proc(1,7,8));
        rr.add(new Proc(2,11,11));
        rr.add(new Proc(3,16,9));
        rr.add(new Proc(4,24,4));
        rr.add(new Proc(5,30,10));
        rr.add(new Proc(6,35,8));
        rr.add(new Proc(7,40,11));
        rr.add(new Proc(8,46,7));
        rr.add(new Proc(9,54,7));
        rr.add(new Proc(10,60,3));
        rr.add(new Proc(11,68,9));
        rr.add(new Proc(12,74,4));
        rr.add(new Proc(13,80,11));
        rr.add(new Proc(14,88,9));
        rr.add(new Proc(15,98,8));
        rr.add(new Proc(16,108,9));
        rr.add(new Proc(17,114,5));
        rr.add(new Proc(18,123,7));
        rr.add(new Proc(19,128,9));
        rr.add(new Proc(20,133,5));
        rr.add(new Proc(21,141,10));

        srt.add(new Proc(0,0,9));
        srt.add(new Proc(1,7,8));
        srt.add(new Proc(2,11,11));
        srt.add(new Proc(3,16,9));
        srt.add(new Proc(4,24,4));
        srt.add(new Proc(5,30,10));
        srt.add(new Proc(6,35,8));
        srt.add(new Proc(7,40,11));
        srt.add(new Proc(8,46,7));
        srt.add(new Proc(9,54,7));
        srt.add(new Proc(10,60,3));
        srt.add(new Proc(11,68,9));
        srt.add(new Proc(12,74,4));
        srt.add(new Proc(13,80,11));
        srt.add(new Proc(14,88,9));
        srt.add(new Proc(15,98,8));
        srt.add(new Proc(16,108,9));
        srt.add(new Proc(17,114,5));
        srt.add(new Proc(18,123,7));
        srt.add(new Proc(19,128,9));
        srt.add(new Proc(20,133,5));
        srt.add(new Proc(21,141,10));
    }
}
