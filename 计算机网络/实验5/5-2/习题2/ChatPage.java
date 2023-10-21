package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.net.*;

public class ChatPage extends JFrame implements ActionListener {
    private final JButton exit_button; // 退出按钮
    private final JButton send_button; // 发送按钮
    private final JButton clear_button; // 清除按钮
    private final JTextField IP; // IP 地址输入框
    private final JTextField port; // 端口号输入框
    private final JTextField send_message; // 发送消息输入框
    private final JTextArea textArea; // 显示聊天记录的文本框
    private final int s_port; // 发送端口号
    private final int r_port; // 接收端口号
    private final String sender; // 发送方用户名
    private final String receiver; // 接收方用户名
    private DatagramSocket socket; // DatagramSocket 对象



    public void actionPerformed(ActionEvent e){
        if(e.getSource()==exit_button){ // 点击了退出按钮
            System.exit(0);
        }
        if(e.getSource()==send_button){ // 点击了发送按钮
            try {
                send_message();
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
        }
        if(e.getSource()==clear_button){ // 点击了清除按钮
            textArea.setText("");
        }
    }

    public void send_message() throws UnknownHostException {
        String ip=IP.getText(); // 获取 IP 地址
        InetAddress address=InetAddress.getByName(ip); // 将 IP 地址转换为 InetAddress 对象
        byte[] buf=send_message.getText().getBytes(); // 获取要发送的消息
        DatagramPacket packet=new DatagramPacket(buf,buf.length,address,s_port); // 创建 DatagramPacket 对象
        textArea.append(sender+":"+send_message.getText()+"\n"); // 在文本框中显示消息
        try {
            socket.send(packet); // 发送消息
        } catch (IOException e) {
            e.printStackTrace();
        }
        send_message.setText(null); // 清空发送消息的输入框
    }
    public void get_message() throws IOException {
        try {
            socket=new DatagramSocket(r_port);
        }catch (SocketException e){
            e.printStackTrace();
        }
        byte[] buf=new byte[1024];
        final DatagramPacket packet=new DatagramPacket(buf,buf.length);
        Runnable runnable=new Runnable() {
            @Override
            public void run() {
                while (true){
                    try {
                        socket.receive(packet);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    String message=new String(packet.getData(),0,packet.getLength());
                    textArea.append(receiver+":"+message+"\n");
                }
            }
        };
       new Thread(runnable).start();
    }
    public ChatPage(int send_port,int receive_port,String sender,String receiver) throws IOException {
        this.sender=sender;  // 发送方名称
        this.receiver=receiver;  // 接收方名称
        this.s_port=send_port;  // 发送端口号
        this.r_port=receive_port;  // 接收端口号
        this.setTitle("Chat Page");  // 设置聊天页面的标题
        setBounds(100,100,500,400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        JPanel panel=new JPanel();
        panel.setLayout(new FlowLayout());
        add(panel,BorderLayout.NORTH);
        exit_button=new JButton("Exit");
        exit_button.setSize(50,20);
        send_button=new JButton("Send");
        send_button.setSize(50,20);
        clear_button=new JButton("Clear");
        clear_button.setSize(50,20);
        panel.add(exit_button);
        panel.add(send_button);
        panel.add(clear_button);
        textArea=new JTextArea();
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        JScrollPane scrollPane=new JScrollPane(textArea);  // 创建带滚动条的文本域
        add(scrollPane,BorderLayout.CENTER);  // 把文本域添加到聊天页面的中央
        JPanel panel1=new JPanel();  // 创建一个新的面板
        BorderLayout borderLayout=new BorderLayout();  // 创建边框布局
        borderLayout.setHgap(10);  // 设置水平间距为10
        panel1.setLayout(borderLayout);  // 设置面板的布局管理器为边框布局
        InetAddress address_1=InetAddress.getLocalHost();
        String Local_IP=address_1.getHostAddress();
        IP=new JTextField(Local_IP);
        port=new JTextField(sender);
        JTextField host=new JTextField(sender);
        panel1.add(host,BorderLayout.WEST);
        // 创建一个输入框来输入发送的消息
        send_message=new JTextField();
        panel1.add(send_message,BorderLayout.CENTER);
        add(panel1,BorderLayout.SOUTH);
        setVisible(true);
        get_message();
        send_button.addActionListener(this);
        exit_button.addActionListener(this);
        clear_button.addActionListener(this);
    }

    public static void main(String[] args) throws IOException {
        ChatPage Chat_A=new ChatPage(6000,6001,"User_A","User_B");
        Chat_A.setVisible(true);
        ChatPage Chat_B=new ChatPage(6001,6000,"User_B","User_A");
        Chat_B.setVisible(true);
    }

}
