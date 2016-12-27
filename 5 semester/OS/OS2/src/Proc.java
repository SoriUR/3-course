/**
 * Created by Yura on 28.09.2016.
 */
public class Proc {
    private String name;
    private int AppearTime;
    private int PerfTime;
    private int WatingTime;
    private int TurnTime;

    public void IncWaitingTime(){
        WatingTime++;
    }

    public Integer getTurnTime(){
        return TurnTime;
    }

    public void UpdateTurnTime(){
        TurnTime+=WatingTime;
    }

    public Integer getWaitTime(){
        return WatingTime;
    }

    public String getName() {
        return name;
    }

    public int getAppearTime() {
        return AppearTime;
    }

    public int getPerfTime() {
        return PerfTime;
    }

    public void DecrPerfTime(){
        PerfTime--;
    }

    public Proc(int i,int a, int b){
        name="Proc"+String.valueOf(i);
        AppearTime = a;
        PerfTime = b;
        TurnTime = PerfTime;
    }
}
