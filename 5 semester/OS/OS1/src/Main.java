import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * Created by Yura on 03.11.2016.
 */
public class Main {
    public static void main(String args[]) {
        String os_name1 = System.getProperty("os.name");
        String os_name2 = System.getenv( "OS");
        //String os_version1 = System.getProperty("os.version");
        String os_type1 = System.getProperty("os.arch");
        String os_type2 = System.getenv("PROCESSOR_ARCHITECTURE");
        String user_name1 = System.getProperty("user.name");
        String user_name2 = System.getenv("username");
        Integer proc_count1 = Runtime.getRuntime().availableProcessors();
        String proc_count2 = System.getenv("NUMBER_OF_PROCESSORS");
        String comp_name = System.getenv("computername");
        System.out.println(os_name1+"|"+os_name2);
        //System.out.println(os_version1);
        System.out.println(os_type1+"|"+os_type2);
        System.out.println(user_name1+"|"+user_name2);
        System.out.println(comp_name);
        System.out.println(proc_count1+"|"+proc_count2);
    }
}
