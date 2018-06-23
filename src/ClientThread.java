import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
/**
 *   作用：一直接收服务端转发过来的信息 
 * */
public class ClientThread extends Thread {

    private Socket socket;
    public RSA rsa2 = new RSA();
    private List<User> list;
    private User user;
    public ClientThread(Socket socket, List<User> list) {
        this.socket = socket;
        this.list = list;
    }


    public void run() {
        try {
            InputStream inputStream = socket.getInputStream();
            InputStreamReader inputStreamReader = new InputStreamReader(
                    inputStream);
            BufferedReader br = new BufferedReader(inputStreamReader);
            String key = null;
            DES des2 = new DES();

            try {
                // 信息的格式：(login||logout||say||key),发送人,收发人,信息体

                while (true) {
                    String msg=br.readLine();
                    String[] str = msg.split(" ");
                    switch (str[0]) {
                        case "say":
                            String miwen = "";
                            for(int i = 2; i < str.length; i++){
                                miwen += str[i];
                            }
                            for(int i = 0; i < list.size(); i++){
                                if(list.get(i).getName().equals(str[1])){
                                    key = list.get(i).getKey();
                                }
                            }
                            miwen = des2.encrypt(miwen, key, "decrypt");
                            System.out.println(str[1] + ": "
                                    + miwen);
                            break;
                        case "key":
                            //System.out.println(str[3]);
                            int n = Integer.parseInt(str[3]);

                            int d = Integer.parseInt(str[2]);
                            String keyno = "";
                            for(int i = 4; i < str.length; i++){
                                int a = Integer.parseInt(str[i]);
                                char aa = rsa2.RSAjiemi(a, d, n);
                                keyno += aa;
                            }
                            User user = new User(str[1], str[2], str[3], keyno);
                            list.add(user);
                            break;

                        default:
                            break;
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }
}  