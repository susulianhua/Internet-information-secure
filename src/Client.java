import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.List;
import java.util.ArrayList;

/*
 *   client线程主要是负责：
 *   1.发送信息
 *   2.一直接收信息，并解析
 * */
public class Client {

    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 9999);
            //开启一个线程接收信息，并解析
            // 实例化一个list,用于保存所有的User
            List<User> list = new ArrayList<User>();
            ClientThread thread=new ClientThread(socket, list);
            thread.start();
            //主线程用来发送信息
            BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
            PrintWriter out=new PrintWriter(socket.getOutputStream());

            //第一次运行时产生公钥以及输入key
            System.out.println("请分别输入p, q, e, key");
            //两个加密算法初始化
            RSA rsa1 = new RSA();
            DES des = new DES();
            String clientkey = null;
            //产生公钥并发送给服务器端
            String password = br.readLine();
            String[] info = password.split(" ");
            String gongyao = "";
            if(info.length != 4 ){
                System.out.println("wrong in");
            }
            else {
                int p = Integer.parseInt(info[0]);
                int q = Integer.parseInt(info[1]);
                int e = Integer.parseInt(info[2]);
                int N = p * q;
                int L = rsa1.qiuL(p - 1, q - 1);
                int D = rsa1.qiuD(e, L);
                clientkey = info[3];
                //System.out.println(info[0] + info[1] + " " + info[2] + " " + info[3]);
                for(int i = 0; i < info[3].length(); i++){
                    int cc = info[3].charAt(i);
                    int jiamigongyao = rsa1.RSAjiami(cc, e, N);
                    String jiamichar = String.valueOf(jiamigongyao);
                    if(i != info[3].length() - 1) {
                        gongyao = gongyao + jiamichar + " ";
                    }
                    else gongyao += jiamichar;
                }
                gongyao = "key" + " " + String.valueOf(D) + " " + String.valueOf(N) + " " + gongyao;


            }
            out.println(gongyao);
            out.flush();
            while(true)
            {

                String s = br.readLine();
                String ss[] = s.split(" ");
                s = ss[0] + " " + ss[1];
                String mmm = "";
                if( ss.length > 2){
                    for(int i = 2; i < ss.length; i++){
                        while (ss[i].length() % 8 != 0){
                            ss[i] += "0";
                        }
                        mmm = des.encrypt(ss[i], clientkey, "encrypt");
                        s = s + " "+ mmm;
                    }
                }
                out.println(s);
                //         out.write(s+"\n");
                out.flush();
            }
        }catch(Exception e){
            System.out.println("服务器异常");
        }
    }
}