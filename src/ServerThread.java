import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

/*
 *   服务器线程的作用主要是:
 *   1.接收来自客户端的信息
 *   2.将接收到的信息解析，并转发给目标客户端
 * */
public class ServerThread extends Thread {

    private User user;
    private List<User> list;

    public ServerThread(User user, List<User> list) {
        this.user = user;
        this.list = list;
    }

    public void run() {
        try {
            while (true) {
                // 信息的格式：(login||logout||say),发送人,收发人,信息体
                //不断地读取客户端发过来的信息
                String msg= user.getBr().readLine();
                String[] str = msg.split(" ");

                switch (str[0]) {
                    case "logout":
                        remove(user);// 移除用户
                        break;
                    case "say":
                        String from = user.getName();
                        msg = "";
                        for(int i = 2; i < str.length; i++){
                            msg += str[i];
                        }
                        msg = "say " + from + " " + msg;
                        sendToClient(str[1], msg); // 转发信息给特定的用户
                        break;
                    case "key":                //存储用户的公钥以及加密后的deskey
                        user.setD(str[1]);
                        user.setN(str[2]);
                        String keystr = "";
                        for(int i = 3; i < str.length; i++){
                            if( i != str.length - 1) {
                                keystr = keystr + str[i] + " ";
                            }
                            else keystr += str[i];
                        }
                        user.setKey(keystr);
                        break;
                        //System.out.println(user.getName() + " " + user.getD() + " " + user.getN() + " " + user.getKey());
                    case "request":          //请求命令则回传给用户相应的公钥以及deskey
                        String aim = user.getName();
                        String n = null;
                        String d = null;
                        String key = null;
                        int flag = 0;
                        for(int i = 0; i < list.size(); i++){
                            if(list.get(i).getName().equals(str[1])){
                                n = list.get(i).getN();
                                d = list.get(i).getD();
                                key = list.get(i).getKey();
                                flag = 1;
                            }
                        }
                        if(flag == 1) {
                            msg = "key" + " " + str[1] + " " + d + " " + n + " " + key;
                        }
                        else msg = "wrong request";
                        sendToClient(aim, msg);
                        break;


                    default:
                        break;
                }
            }
        } catch (Exception e) {
            System.out.println("异常");
        } finally {
            try {
                user.getBr().close();
                user.getSocket().close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void sendToClient(String username, String msg) {

        for (User user : list) {
            if (user.getName().equals(username)) {
                try {
                    PrintWriter pw =user.getPw();
                    pw.println(msg);
                    pw.flush();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private void remove(User user2) {
        list.remove(user2);
    }
}